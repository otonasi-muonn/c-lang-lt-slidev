<template>
  <section class="mt-4 text-left text-base leading-relaxed">
    <div class="flex flex-wrap items-baseline justify-between gap-3">
      <div>
        <div class="text-2xl font-bold">18 bytes を C/WASM へ渡す</div>
        <div class="mt-1 opacity-70">
          実在 VID/PID を使った構成例。実機の生ダンプではない。
        </div>
      </div>
      <div
        class="rounded-full border px-3 py-1 font-mono text-sm"
        :class="
          engine === 'wasm'
            ? 'border-green-300/50 bg-green-300/10 text-green-200'
            : 'border-yellow-300/50 bg-yellow-300/10 text-yellow-100'
        "
      >
        {{ engineLabel }}
      </div>
    </div>

    <div
      v-if="engine === 'fallback'"
      class="mt-3 rounded-lg border border-yellow-300/30 bg-yellow-300/10 px-3 py-2 text-sm text-yellow-50"
      role="status"
    >
      WASM のロードまたは実行に失敗。純JSで同じ結果を表示中。{{
        fallbackReason
      }}
    </div>

    <div
      class="mt-4 grid grid-cols-[1fr_auto_1fr_auto_1fr] items-stretch gap-2 text-center text-sm"
    >
      <div class="rounded-lg border border-blue-300/30 bg-blue-300/10 p-3">
        <div class="font-bold text-blue-100">1. JS</div>
        <code class="mt-1 block text-base">Uint8Array(18)</code>
      </div>
      <div class="self-center text-xl opacity-60">→</div>
      <div class="rounded-lg border border-yellow-300/30 bg-yellow-300/10 p-3">
        <div class="font-bold text-yellow-100">2. linear memory</div>
        <code class="mt-1 block text-base">{{ bufferAddress }}</code>
      </div>
      <div class="self-center text-xl opacity-60">→</div>
      <div class="rounded-lg border border-green-300/30 bg-green-300/10 p-3">
        <div class="font-bold text-green-100">3. C function</div>
        <code class="mt-1 block text-base">{{ calledFunction }}</code>
      </div>
    </div>

    <div class="mt-4 rounded-xl border border-white/15 bg-black/30 p-4">
      <div
        class="flex flex-wrap gap-2 font-mono text-xl"
        aria-label="USB Device Descriptor の入力バイト列"
      >
        <span
          v-for="(byte, index) in inputBytes"
          :key="`${runId}-${index}`"
          class="rounded px-1.5 py-0.5"
          :class="byteClass(index)"
          :title="`byte ${index}`"
          >{{ hex(byte, 2) }}</span
        >
      </div>
      <div
        class="mt-2 flex flex-wrap gap-x-5 gap-y-1 font-mono text-sm opacity-65"
      >
        <span
          ><code>len = {{ requestedLength }}</code></span
        >
        <span
          ><code>buf = {{ bufferAddress }}</code></span
        >
        <span
          ><code>out = {{ outputAddress }}</code></span
        >
        <span
          ><code
            >return {{ returnCode === null ? "—" : returnCode }}</code
          ></span
        >
      </div>
    </div>

    <div
      class="mt-4 flex flex-wrap gap-2"
      aria-label="USB descriptor デモの操作"
    >
      <button
        class="demo-button border-green-300/50 bg-green-300/15 hover:bg-green-300/25"
        @click="runDemo('normal')"
      >
        正常に解析
      </button>
      <button
        class="demo-button border-red-300/50 bg-red-300/10 hover:bg-red-300/20"
        @click="runDemo('bad-length')"
      >
        bLength を 0x14 にする
      </button>
      <button
        class="demo-button border-orange-300/50 bg-orange-300/10 hover:bg-orange-300/20"
        @click="runDemo('short')"
      >
        8 bytes だけ渡す
      </button>
      <button
        class="demo-button border-blue-300/50 bg-blue-300/10 hover:bg-blue-300/20"
        @click="runDemo('big-endian')"
      >
        Big-endian として読む
      </button>
    </div>

    <template v-if="returnCode === 18 && output">
      <div class="mt-4 grid grid-cols-2 gap-3">
        <div
          v-for="field in highlightedFields"
          :key="field.name"
          class="rounded-xl border border-green-300/30 bg-green-300/10 p-3 font-mono text-base"
        >
          <div class="opacity-65">{{ field.bytes }} → {{ field.name }}</div>
          <strong class="text-xl text-green-200">{{
            formatField(field, output[field.outputIndex])
          }}</strong>
          <span
            v-if="!isBigEndian"
            class="ml-2 font-sans text-sm opacity-70"
            >{{ field.note }}</span
          >
          <span v-else class="ml-2 font-sans text-sm text-red-200 opacity-80"
            >逆に読むと別物</span
          >
        </div>
      </div>
      <div class="mt-3 grid grid-cols-3 gap-x-3 gap-y-1 font-mono text-base">
        <div v-for="field in displayedFields" :key="field.name" class="min-w-0">
          <span class="opacity-55">{{ field.bytes }}</span>
          <code class="ml-1">{{ field.name }}</code>
          <span class="mx-1 opacity-45">=</span>
          <strong :class="field.emphasis ? 'text-green-200' : ''">{{
            formatField(field, output[field.outputIndex])
          }}</strong>
        </div>
      </div>
    </template>
    <div
      v-else
      class="mt-4 grid grid-cols-[auto_1fr] gap-x-3 gap-y-1 rounded-xl border border-white/10 bg-white/5 p-4 font-mono text-base"
    >
      <template v-if="returnCode !== null">
        <span class="text-red-200">C の戻り値</span>
        <strong class="text-red-200"
          ><code>{{ returnCode }}</code> — {{ resultMessage }}</strong
        >
      </template>
      <template v-else>
        <span class="opacity-60">結果</span>
        <span class="opacity-60">ボタンを押して C/WASM を呼ぶ</span>
      </template>
    </div>

    <div class="mt-3 text-sm opacity-65" aria-live="polite">
      {{ runSummary }}
    </div>
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
  bytes: string;
  name: string;
  outputIndex: number;
  width: 2 | 4;
  emphasis?: boolean;
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

const fields: Field[] = [
  { bytes: "[0]", name: "bLength", outputIndex: 0, width: 2 },
  { bytes: "[1]", name: "bDescriptorType", outputIndex: 1, width: 2 },
  { bytes: "[2–3]", name: "bcdUSB", outputIndex: 2, width: 4 },
  { bytes: "[4]", name: "bDeviceClass", outputIndex: 3, width: 2 },
  { bytes: "[5]", name: "bDeviceSubClass", outputIndex: 4, width: 2 },
  { bytes: "[6]", name: "bDeviceProtocol", outputIndex: 5, width: 2 },
  { bytes: "[7]", name: "bMaxPacketSize0", outputIndex: 6, width: 2 },
  {
    bytes: "[8–9]",
    name: "idVendor",
    outputIndex: 7,
    width: 4,
    emphasis: true,
    note: "Logitech",
  },
  {
    bytes: "[10–11]",
    name: "idProduct",
    outputIndex: 8,
    width: 4,
    emphasis: true,
    note: "Unifying Receiver",
  },
  { bytes: "[12–13]", name: "bcdDevice", outputIndex: 9, width: 4 },
  { bytes: "[14]", name: "iManufacturer", outputIndex: 10, width: 2 },
  { bytes: "[15]", name: "iProduct", outputIndex: 11, width: 2 },
  { bytes: "[16]", name: "iSerialNumber", outputIndex: 12, width: 2 },
  { bytes: "[17]", name: "bNumConfigurations", outputIndex: 13, width: 2 },
];

const highlightedFields = fields.filter((field) => field.emphasis);
const displayedFields = fields.filter((field) =>
  [0, 1, 2, 9, 13].includes(field.outputIndex),
);

const engine = ref<Engine>("loading");
const wasm = ref<UsbWasmExports | null>(null);
const fallbackReason = ref("");
const inputBytes = ref<number[]>(Array.from(descriptor));
const requestedLength = ref(18);
const returnCode = ref<number | null>(null);
const output = ref<number[] | null>(null);
const bufferAddress = ref("ロード中");
const outputAddress = ref("ロード中");
const calledFunction = ref("待機中");
const runId = ref(0);

const isBigEndian = computed(
  () => calledFunction.value === "usb_parse_as_big_endian()",
);

const engineLabel = computed(() => {
  if (engine.value === "wasm") return "WASM 実行中";
  if (engine.value === "fallback") return "JS フォールバック";
  return "WASM をロード中";
});

const resultMessage = computed(() => {
  if (returnCode.value === -1) return "len < 18";
  if (returnCode.value === -2) return "bLength != 18";
  if (returnCode.value === -3) return "bDescriptorType != 0x01";
  return "解析できなかった";
});

const runSummary = computed(() => {
  if (returnCode.value === null)
    return "JS が生バイトを書き、C が linear memory を読んで結果を書く。";
  if (returnCode.value === 18) {
    return engine.value === "wasm"
      ? "JS → linear memory → C/WASM → Uint16Array。グルーもWASI依存もない。"
      : "JS の同等ロジックで結果を表示中。発表はこのまま続けられる。";
  }
  return "C の境界チェックが不正な入力を戻り値で止めた。";
});

function hex(value: number, width: number) {
  return value.toString(16).toUpperCase().padStart(width, "0");
}

function formatField(field: Field, value: number) {
  return `0x${hex(value, field.width)}`;
}

function byteClass(index: number) {
  if (index === 8 || index === 9 || index === 10 || index === 11)
    return "bg-green-300/25 text-green-100";
  if (index === 2 || index === 3 || index === 12 || index === 13)
    return "bg-blue-300/20 text-blue-100";
  return "bg-white/10";
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

function runDemo(mode: DemoMode) {
  const request = requestFor(mode);
  inputBytes.value = Array.from(request.bytes);
  requestedLength.value = request.length;
  output.value = null;
  returnCode.value = null;
  calledFunction.value = request.bigEndian
    ? "usb_parse_as_big_endian()"
    : "usb_parse_device_descriptor()";
  runId.value += 1;

  if (engine.value !== "wasm" || !wasm.value) {
    bufferAddress.value = "JS fallback";
    outputAddress.value = "JS fallback";
    applyResult(
      parseWithJavaScript(request.bytes, request.length, request.bigEndian),
    );
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
    applyResult({ returnCode: code, output: values });
  } catch (error) {
    wasm.value = null;
    engine.value = "fallback";
    fallbackReason.value = error instanceof Error ? ` (${error.message})` : "";
    bufferAddress.value = "JS fallback";
    outputAddress.value = "JS fallback";
    applyResult(
      parseWithJavaScript(request.bytes, request.length, request.bigEndian),
    );
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
    bufferAddress.value = "未実行";
    outputAddress.value = "未実行";
  } catch (error) {
    engine.value = "fallback";
    fallbackReason.value = error instanceof Error ? ` (${error.message})` : "";
    runDemo("normal");
  }
}

onMounted(loadWasm);
</script>

<style scoped>
.demo-button {
  border-width: 1px;
  border-radius: 0.5rem;
  padding: 0.5rem 0.75rem;
  font-size: 1rem;
  line-height: 1.5rem;
  transition: background-color 150ms ease;
}

.demo-button:disabled {
  cursor: wait;
  opacity: 0.5;
}
</style>
