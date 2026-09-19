<template>
  <section class="demo">
    <!-- What JS put on the wire. The row never wraps: 18 bytes are 18 bytes. -->
    <div class="bytes">
      <span
        v-for="(byte, index) in paddedBytes"
        :key="`${runId}-${index}`"
        :class="byteClass(index)"
        >{{ byte === null ? "··" : hex(byte, 2) }}</span
      >
    </div>
    <div class="ruler">
      <span v-for="i in 18" :key="i" :class="tickClass(i - 1)">{{
        tickLabel(i - 1)
      }}</span>
    </div>

    <!-- The call, with the pointers C actually handed back. -->
    <div class="call">
      <div class="k cl">len={{ requestedLength }}</div>
      <div class="cl">
        <span class="s" :class="returnClass"
          >{{ calledFunction }}<span class="t"> → </span
          >{{ returnCode === null ? "?" : returnCode }}</span
        >
        <span class="g"
          >buf={{ bufferAddress }}<span class="t">&nbsp;&nbsp;</span>out={{
            outputAddress
          }}</span
        >
      </div>
    </div>

    <div class="controls">
      <button
        v-for="mode in modes"
        :key="mode.id"
        class="btn"
        :class="{ on: activeMode === mode.id }"
        @click="runDemo(mode.id)"
      >
        {{ mode.label }}
      </button>
      <span class="engine" :class="engineClass">{{ engineLabel }}</span>
    </div>

    <!-- Result. One block, fixed height, so the slide never reflows. -->
    <div class="result">
      <template v-if="returnCode === 18 && output">
        <div v-for="field in wideFields" :key="field.name" class="rline">
          <span class="rname">{{ field.name }}</span>
          <span class="rraw">{{ rawOf(field) }}</span>
          <span class="rarrow">→</span>
          <span class="rval" :class="isBigEndian ? 'sig' : 'wide'">{{
            formatField(field, output[field.outputIndex])
          }}</span>
          <span class="rnote">{{
            isBigEndian ? "逆に読むと別物" : field.note
          }}</span>
        </div>
        <div class="rrest">
          <span v-for="field in restFields" :key="field.name"
            >{{ field.name }}<span class="t">=</span
            >{{ formatField(field, output[field.outputIndex]) }}</span
          >
        </div>
      </template>
      <template v-else-if="returnCode !== null">
        <div class="rfail">
          <span class="err mono">return {{ returnCode }}</span>
          <span class="err">{{ resultMessage }}</span>
        </div>
        <p class="note">C の境界チェックが、不正な入力を戻り値で止めた。</p>
      </template>
      <template v-else>
        <p class="note">ボタンを押すと、JS が生バイトを書き、C が読む。</p>
      </template>
    </div>

    <p class="status" aria-live="polite">{{ runSummary }}</p>
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
  { id: "normal", label: "正常に解析" },
  { id: "bad-length", label: "bLength を 0x14 にする" },
  { id: "short", label: "8 bytes だけ渡す" },
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

const wideFields = fields.filter(
  (field) => field.offset === 8 || field.offset === 10,
);
const restFields = fields.filter((field) =>
  [0, 1, 2, 9, 13].includes(field.outputIndex),
);

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
const bufferAddress = ref("—");
const outputAddress = ref("—");
const calledFunction = ref("usb_parse_device_descriptor(len)");
const activeMode = ref<DemoMode | null>(null);
const runId = ref(0);

const isBigEndian = computed(() =>
  calledFunction.value.startsWith("usb_parse_as_big_endian"),
);

// 18 cells always, so the row and the ruler stay aligned when C is handed
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
  if (reported.value === "wasm") return "WASM 実行中";
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
  if (returnCode.value === -1) return "len < 18";
  if (returnCode.value === -2) return "bLength != 18";
  if (returnCode.value === -3) return "bDescriptorType != 0x01";
  return "解析できなかった";
});

const runSummary = computed(() => {
  if (ranWith.value === "js") {
    return `WASM で実行できず、純 JS の同等ロジックで表示中${fallbackReason.value}`;
  }
  if (returnCode.value === null)
    return "JS が生バイトを linear memory へ書き、C がそれを読んで結果を書き戻す。";
  if (returnCode.value === 18) {
    return isBigEndian.value
      ? "同じ 18 バイト。読み方を変えただけで、別のデバイスになる。"
      : "JS → linear memory → C/WASM → Uint16Array。JS グルーも WASI 依存もない。";
  }
  return "戻り値だけで止まっている。壊れたバイト列は構造体にならない。";
});

function hex(value: number, width: number) {
  return value.toString(16).toUpperCase().padStart(width, "0");
}

function formatField(field: Field, value: number) {
  return `0x${hex(value, field.width)}`;
}

function rawOf(field: Field) {
  const bytes = inputBytes.value;
  if (field.width === 2) return hex(bytes[field.offset], 2);
  return `${hex(bytes[field.offset], 2)} ${hex(bytes[field.offset + 1], 2)}`;
}

function byteClass(index: number) {
  if (index >= inputBytes.value.length) return "off";
  if (returnCode.value === 18 && index >= 8 && index <= 11)
    return isBigEndian.value ? "sig" : "wide";
  if (activeMode.value === "bad-length" && index === 0) return "sig";
  return "";
}

function tickLabel(index: number) {
  return index === 0 || index === 8 || index === 10 || index === 17
    ? String(index)
    : "";
}

function tickClass(index: number) {
  // A byte C was never handed carries no field marking.
  if (index >= inputBytes.value.length) return "";
  if (index >= 8 && index <= 11)
    return returnCode.value === 18 && isBigEndian.value ? "tsig" : "twide";
  return tickLabel(index) ? "t" : "";
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
    const values =
      code === 18
        ? Array.from(new Uint16Array(ex.memory.buffer, outputPointer, 14))
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
      bufferAddress.value = "—";
      outputAddress.value = "—";
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

.call {
  display: grid;
  grid-template-columns: var(--rail) 1fr;
  column-gap: var(--rail-gap);
  margin-top: 30px;
  margin-left: calc(-1 * (var(--rail) + var(--rail-gap)));
}
.call .cl {
  font-size: 15px;
  grid-template-columns: 340px 1fr;
}
.call .cl .s.ok {
  color: var(--ink);
}
.call .cl .s.err {
  color: var(--err);
}
.call .cl .g {
  color: var(--ink-3);
}

.controls {
  display: flex;
  align-items: center;
  gap: 8px;
  margin-top: 26px;
}
.engine {
  margin-left: auto;
  font-family: var(--mono);
  font-size: 12px;
  font-weight: 500;
  letter-spacing: 0.03em;
  color: var(--ink-3);
}
.engine-wasm {
  color: var(--ink-2);
}
.engine-fallback {
  color: var(--sig);
}

/* Fixed height: the slide must not reflow when a result appears mid-talk. */
.result {
  margin-top: 22px;
  min-height: 98px;
}

.rline {
  display: grid;
  grid-template-columns: 158px 62px 16px 86px 1fr;
  align-items: baseline;
  column-gap: 12px;
  font-family: var(--mono);
  font-size: 19px;
  font-weight: 500;
  line-height: 1.62;
}
.rname {
  color: var(--ink-2);
  font-size: 15px;
}
.rraw {
  color: var(--ink);
}
.rarrow {
  color: var(--ink-3);
  font-size: 13px;
}
.rnote {
  font-family: var(--sans);
  font-size: 13px;
  font-weight: 400;
  color: var(--ink-3);
}

.rrest {
  display: flex;
  flex-wrap: wrap;
  column-gap: 22px;
  margin-top: 10px;
  font-family: var(--mono);
  font-size: 13px;
  font-weight: 500;
  color: var(--ink-2);
}
.rrest .t {
  color: var(--ink-3);
  opacity: 0.6;
}

.rfail {
  display: flex;
  align-items: baseline;
  gap: 16px;
  font-size: 22px;
  font-weight: 700;
  line-height: 1.5;
}

.status {
  max-width: none;
  margin-top: 20px;
  font-size: 13px;
  line-height: 1.6;
  color: var(--ink-3);
}
</style>
