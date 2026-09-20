<template>
  <section class="demo">
    <div>
      <!-- Input bytes in linear memory, not a live USB capture. -->
      <div class="bytes">
        <span
          v-for="(byte, index) in paddedBytes"
          :key="`${runId}-${index}`"
          :class="byteClass(index)"
          >{{ byte === null ? "··" : hex(byte, 2) }}</span
        >
      </div>
    </div>

    <div class="controls">
      <button
        class="btn lead"
        :class="{ on: activeMode === null || activeMode === 'normal' }"
        @click="runDemo('normal')"
      >
        正常に解析
      </button>
      <span class="engine" :class="engineClass" role="status">{{
        engineLabel
      }}</span>
    </div>

    <div class="result" aria-live="polite">
      <template v-if="returnCode === 18 && output">
        <div class="hero-result">
          <span class="hero-raw">6D 04</span><span class="result-arrow">→</span>
          <strong class="hero-value" :class="isBigEndian ? 'sig' : 'wide'"
            >0x{{ hex(output[7], 4) }}</strong
          >
          <span class="hero-vendor">{{
            isBigEndian ? "別の解釈" : "Logitech"
          }}</span>
        </div>
      </template>
      <template v-else-if="returnCode !== null">
        <div class="rfail">
          <span class="err mono">return {{ returnCode }}</span>
          <span>{{ resultMessage }}</span>
        </div>
      </template>
      <template v-else>
        <div class="hero-result waiting">
          <span class="hero-raw">6D 04</span><span class="result-arrow">→</span>
          <strong class="hero-value">?</strong
          ><span class="hero-vendor">ボタンを押して読む</span>
        </div>
      </template>
    </div>

    <p class="status" aria-live="polite">{{ runSummary }}</p>

    <details class="extra" name="demo-details">
      <summary>追加で試す</summary>
      <div class="extra-controls">
        <button
          v-for="mode in modes"
          :key="mode.id"
          class="btn"
          :class="{ on: activeMode === mode.id }"
          @click="runDemo(mode.id)"
        >
          {{ mode.label }}
        </button>
      </div>
      <p class="detail-note">
        Big-endian は同じバイト列の別解釈。WASM 自体は little-endian。
      </p>
    </details>
    <details class="extra debug" name="demo-details">
      <summary>メモリと全フィールド</summary>
      <div class="debug-call" :class="returnClass">
        {{ calledFunction }} → {{ returnCode ?? "?" }}
      </div>
      <div class="addresses">
        input: {{ bufferAddress || "—" }} · len={{ requestedLength }} · output:
        {{ outputAddress || "—" }}
      </div>
      <div v-if="output" class="all-fields">
        <div v-for="field in fields" :key="field.name">
          <span>{{ field.name }}</span
          ><b>{{ formatField(field, output[field.outputIndex]) }}</b>
        </div>
      </div>
      <p v-else class="detail-note">解析成功後に、14フィールドを表示します。</p>
    </details>
  </section>
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from "vue";

type Engine = "loading" | "wasm" | "fallback";
type DemoMode = "normal" | "bad-length" | "short" | "big-endian";

type UsbWasmExports = {
  memory: WebAssembly.Memory;
  usb_buf_ptr: () => number;
  usb_out_ptr: () => number;
  usb_parse_device_descriptor: (length: number) => number;
  usb_parse_as_big_endian: (length: number) => number;
};

type Field = {
  offset: number;
  name: string;
  outputIndex: number;
  width: 2 | 4;
  note?: string;
};

type ParseResult = {
  returnCode: number;
  output: number[] | null;
};

const descriptor = Uint8Array.from([
  0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x6d, 0x04, 0x2b, 0xc5, 0x00,
  0x12, 0x01, 0x02, 0x00, 0x01,
]);

const props = withDefaults(defineProps<{ wasmUrl?: string }>(), {
  wasmUrl: () => `${import.meta.env.BASE_URL}wasm/usb_descriptor.wasm`,
});

const modes: { id: DemoMode; label: string }[] = [
  { id: "bad-length", label: "bLength を 0x14 にする" },
  { id: "short", label: "8バイトだけ渡す" },
  { id: "big-endian", label: "Big-endian として読む" },
];

const fields: Field[] = [
  { offset: 0, name: "bLength", outputIndex: 0, width: 2 },
  { offset: 1, name: "bDescriptorType", outputIndex: 1, width: 2 },
  { offset: 2, name: "bcdUSB", outputIndex: 2, width: 4 },
  { offset: 4, name: "bDeviceClass", outputIndex: 3, width: 2 },
  { offset: 5, name: "bDeviceSubClass", outputIndex: 4, width: 2 },
  { offset: 6, name: "bDeviceProtocol", outputIndex: 5, width: 2 },
  { offset: 7, name: "bMaxPacketSize0", outputIndex: 6, width: 2 },
  {
    offset: 8,
    name: "idVendor",
    outputIndex: 7,
    width: 4,
    note: "Logitech",
  },
  {
    offset: 10,
    name: "idProduct",
    outputIndex: 8,
    width: 4,
    note: "Unifying Receiver",
  },
  { offset: 12, name: "bcdDevice", outputIndex: 9, width: 4 },
  { offset: 14, name: "iManufacturer", outputIndex: 10, width: 2 },
  { offset: 15, name: "iProduct", outputIndex: 11, width: 2 },
  { offset: 16, name: "iSerialNumber", outputIndex: 12, width: 2 },
  { offset: 17, name: "bNumConfigurations", outputIndex: 13, width: 2 },
];

const engine = ref<Engine>("loading");
// engine is the capability (is there a usable WASM instance?); ranWith is what
// actually produced the result on screen. The badge reports ranWith once
// anything has run, so it can never claim WASM for a JavaScript answer -- and
// a click that lands during loading does not condemn the rest of the talk to
// the fallback label.
const ranWith = ref<"wasm" | "js" | null>(null);
const wasm = ref<UsbWasmExports | null>(null);
const fallbackReason = ref("");
const inputBytes = ref<number[]>(Array.from(descriptor));
const requestedLength = ref(18);
const returnCode = ref<number | null>(null);
const output = ref<number[] | null>(null);
const bufferAddress = ref("");
const outputAddress = ref("");
const calledFunction = ref("usb_parse_device_descriptor(len)");
const activeMode = ref<DemoMode | null>(null);
const runId = ref(0);

const isBigEndian = computed(() =>
  calledFunction.value.startsWith("usb_parse_as_big_endian"),
);

// 18 cells always, so the input keeps its shape when C is handed
// a short buffer: the missing bytes read as absent, not as zero.
const paddedBytes = computed<(number | null)[]>(() => {
  const cells: (number | null)[] = Array.from(inputBytes.value);
  while (cells.length < 18) cells.push(null);
  return cells.slice(0, 18);
});

const reported = computed<Engine>(() => {
  if (ranWith.value === "wasm") return "wasm";
  if (ranWith.value === "js") return "fallback";
  return engine.value;
});

const engineLabel = computed(() => {
  if (reported.value === "wasm")
    return ranWith.value === "wasm" ? "WASM で実行" : "WASM 準備完了";
  if (reported.value === "fallback") return "JS フォールバック";
  return "WASM をロード中";
});

const engineClass = computed(() => ({
  "engine-wasm": reported.value === "wasm",
  "engine-fallback": reported.value === "fallback",
}));

const returnClass = computed(() => {
  if (returnCode.value === null) return "";
  return returnCode.value === 18 ? "ok" : "err";
});

const resultMessage = computed(() => {
  if (returnCode.value === -1) return "入力が短い：8バイト / 必要な長さ 18";
  if (returnCode.value === -2) return "bLength が不正：20 / 期待する長さ 18";
  if (returnCode.value === -3) return "Device Descriptor ではない";
  return "解析できなかった";
});

const runSummary = computed(() => {
  if (ranWith.value === "js") {
    return engine.value === "wasm"
      ? "この結果は JS。WASM の準備ができたので、次の実行から C を使います。"
      : `この結果は JS の同等処理です${fallbackReason.value}`;
  }
  if (returnCode.value === null)
    return "JS がバイト列を渡し、C/WASM の解析結果を受け取ります。";
  if (returnCode.value === 18) {
    return isBigEndian.value
      ? "同じバイト列を big-endian として解釈した値です。"
      : "この値は、C からコンパイルした WASM が返しました。";
  }
  return "C/WASM が入力を検証し、解析を止めました。";
});

function hex(value: number, width: number) {
  return value.toString(16).toUpperCase().padStart(width, "0");
}

function formatField(field: Field, value: number) {
  return `0x${hex(value, field.width)}`;
}

function byteClass(index: number) {
  if (index >= inputBytes.value.length) return "off";
  if (index >= 8 && index <= 9) return isBigEndian.value ? "sig" : "wide";
  if (activeMode.value === "bad-length" && index === 0) return "sig";
  return "";
}

function littleEndian16(bytes: Uint8Array, offset: number) {
  return bytes[offset] | (bytes[offset + 1] << 8);
}

function bigEndian16(bytes: Uint8Array, offset: number) {
  return (bytes[offset] << 8) | bytes[offset + 1];
}

function parseWithJavaScript(
  bytes: Uint8Array,
  length: number,
  bigEndian: boolean,
): ParseResult {
  if (length < 18) return { returnCode: -1, output: null };
  if (bytes[0] !== 18) return { returnCode: -2, output: null };
  if (bytes[1] !== 0x01) return { returnCode: -3, output: null };

  const read16 = bigEndian ? bigEndian16 : littleEndian16;
  return {
    returnCode: 18,
    output: [
      bytes[0],
      bytes[1],
      read16(bytes, 2),
      bytes[4],
      bytes[5],
      bytes[6],
      bytes[7],
      read16(bytes, 8),
      read16(bytes, 10),
      read16(bytes, 12),
      bytes[14],
      bytes[15],
      bytes[16],
      bytes[17],
    ],
  };
}

function isUsbWasmExports(value: unknown): value is UsbWasmExports {
  const exports = value as Partial<UsbWasmExports>;
  return (
    exports.memory instanceof WebAssembly.Memory &&
    typeof exports.usb_buf_ptr === "function" &&
    typeof exports.usb_out_ptr === "function" &&
    typeof exports.usb_parse_device_descriptor === "function" &&
    typeof exports.usb_parse_as_big_endian === "function"
  );
}

function requestFor(mode: DemoMode) {
  const bytes = Uint8Array.from(descriptor);
  if (mode === "bad-length") bytes[0] = 0x14;
  if (mode === "short")
    return { bytes: bytes.slice(0, 8), length: 8, bigEndian: false };
  return { bytes, length: 18, bigEndian: mode === "big-endian" };
}

function applyResult(result: ParseResult) {
  returnCode.value = result.returnCode;
  output.value = result.output;
}

// The engine badge must never claim WASM for a run JavaScript performed.
// Anything that is not a live WASM instance is reported as the fallback,
// including a click that lands while the module is still loading.
function runWithJavaScript(request: ReturnType<typeof requestFor>) {
  ranWith.value = "js";
  bufferAddress.value = "JS";
  outputAddress.value = "JS";
  applyResult(
    parseWithJavaScript(request.bytes, request.length, request.bigEndian),
  );
}

function runDemo(mode: DemoMode) {
  const request = requestFor(mode);
  inputBytes.value = Array.from(request.bytes);
  requestedLength.value = request.length;
  output.value = null;
  returnCode.value = null;
  activeMode.value = mode;
  calledFunction.value = request.bigEndian
    ? "usb_parse_as_big_endian(len)"
    : "usb_parse_device_descriptor(len)";
  runId.value += 1;

  if (engine.value !== "wasm" || !wasm.value) {
    if (engine.value === "loading") {
      fallbackReason.value = "（WASM のロード完了前に実行）";
    }
    runWithJavaScript(request);
    return;
  }

  try {
    const ex = wasm.value;
    const bufferPointer = ex.usb_buf_ptr();
    const outputPointer = ex.usb_out_ptr();
    bufferAddress.value = `0x${hex(bufferPointer, 4)}`;
    outputAddress.value = `0x${hex(outputPointer, 4)}`;
    new Uint8Array(ex.memory.buffer, bufferPointer, request.bytes.length).set(
      request.bytes,
    );
    const parser = request.bigEndian
      ? ex.usb_parse_as_big_endian
      : ex.usb_parse_device_descriptor;
    const code = parser(request.length);
    const outputView = new DataView(ex.memory.buffer, outputPointer, 28);
    const values =
      code === 18
        ? Array.from({ length: 14 }, (_, i) =>
            outputView.getUint16(i * 2, true),
          )
        : null;
    ranWith.value = "wasm";
    fallbackReason.value = "";
    applyResult({ returnCode: code, output: values });
  } catch (error) {
    wasm.value = null;
    engine.value = "fallback";
    fallbackReason.value = error instanceof Error ? `（${error.message}）` : "";
    runWithJavaScript(request);
  }
}

async function loadWasm() {
  try {
    const response = await fetch(props.wasmUrl);
    if (!response.ok)
      throw new Error(`${response.status} ${response.statusText}`);
    const bytes = await response.arrayBuffer();
    const { instance } = await WebAssembly.instantiate(bytes, {});
    if (!isUsbWasmExports(instance.exports))
      throw new Error("required WASM exports are missing");
    wasm.value = instance.exports;
    engine.value = "wasm";
    // A click that landed during loading was answered by JavaScript and still
    // says so; the next run will flip the badge back to WASM on its own.
    if (ranWith.value === null) {
      bufferAddress.value = "";
      outputAddress.value = "";
    }
  } catch (error) {
    fallbackReason.value = error instanceof Error ? `（${error.message}）` : "";
    engine.value = "fallback";
    runDemo("normal");
  }
}

onMounted(loadWasm);
</script>

<style scoped>
.demo {
  font-family: var(--sans);
}
.demo > div:first-child {
  margin: 4px 0 10px;
}
.demo .bytes {
  font-size: 26px;
}
.controls {
  display: flex;
  align-items: center;
  gap: 20px;
}
.controls .lead {
  font-size: 18px;
  padding: 11px 18px;
}
.engine {
  font-size: 15px;
  color: var(--ink-2);
}
.engine-fallback {
  color: var(--sig);
}
.result {
  min-height: 76px;
  display: flex;
  align-items: center;
}
.hero-result {
  display: flex;
  align-items: baseline;
  gap: 24px;
}
.hero-raw {
  font: 500 30px var(--mono);
}
.result-arrow {
  font-size: 25px;
  color: var(--ink-3);
}
.hero-value {
  font: 500 48px var(--mono);
}
.hero-vendor {
  font-size: 29px;
  font-weight: 700;
  color: var(--sig);
}
.waiting .hero-value,
.waiting .hero-vendor {
  color: var(--ink-3);
}
.waiting .hero-vendor {
  font-size: 20px;
  font-weight: 400;
}
.rfail {
  display: flex;
  gap: 24px;
  align-items: baseline;
  font-size: 21px;
}
.rfail .mono {
  font-size: 29px;
}
.demo:has(.debug[open]) .result {
  min-height: 0;
}
.demo:has(.debug[open]) .hero-raw {
  font-size: 22px;
}
.demo:has(.debug[open]) .hero-value {
  font-size: 32px;
}
.demo:has(.debug[open]) .hero-vendor {
  font-size: 21px;
}
.demo .status {
  min-height: 24px;
  margin: 0 0 6px;
  max-width: none;
  color: var(--ink-2);
  font-size: 15px;
  line-height: 1.5;
}
.extra {
  border-top: 1px solid var(--rule);
  padding: 5px 0;
}
.extra summary {
  width: fit-content;
  cursor: pointer;
  color: var(--ink-2);
  font-size: 14px;
}
.extra[open] summary {
  color: var(--ink);
}
.extra-controls {
  display: flex;
  gap: 12px;
  margin: 10px 0 6px;
}
.demo .detail-note {
  font-size: 13px;
  color: var(--ink-2);
  margin: 6px 0 0;
  max-width: none;
}
.debug-call {
  font: 500 14px var(--mono);
  margin-top: 7px;
}
.addresses {
  font: 500 12px var(--mono);
  color: var(--ink-2);
  margin: 4px 0 8px;
}
.all-fields {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 4px 20px;
  font: 500 12px var(--mono);
}
.all-fields > div {
  display: flex;
  justify-content: space-between;
  gap: 8px;
}
.all-fields span {
  color: var(--ink-2);
}
.all-fields b {
  font-weight: 500;
}
.btn:focus-visible,
summary:focus-visible {
  outline: 2px solid var(--wide);
  outline-offset: 4px;
}
</style>
