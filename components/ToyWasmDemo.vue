<template>
  <section class="toy">
    <div>
      <pre
        class="toy-src"
      ><code><span class="toy-attr">__attribute__((export_name(<span
          class="wide"
        >"double_it"</span>)))</span>
<span class="dim">int</span> double_it(<span class="dim">int</span> n) {
  <span class="dim">return</span> n * <span class="wide">2</span>;
}</code></pre>
      <p class="toy-file">wasm/double_it.c　→　double_it.wasm　77 B</p>
      <p class="toy-note">
        1行目が、JavaScript側から呼べる名前を出しておく指定。
      </p>
    </div>

    <div class="toy-run">
      <div class="toy-line">
        <input
          class="toy-in"
          type="number"
          v-model.number="input"
          aria-label="double_it に渡す値"
          @keyup.enter="run"
        />
        <button class="btn lead" :disabled="engine !== 'ready'" @click="run">
          Cで実行
        </button>
        <span class="toy-arrow" :class="{ on: result !== null }">→</span>
        <strong class="toy-out" :class="{ on: result !== null }">{{
          result === null ? "?" : result
        }}</strong>
      </div>

      <span class="engine" :class="engineClass" role="status">{{
        engineLabel
      }}</span>

      <div class="toy-path" :class="{ on: result !== null }" aria-live="polite">
        <span>JavaScript</span>
        <i>↓</i>
        <span>WebAssembly module</span>
        <i>↓</i>
        <span class="lit">double_it() <small>C</small></span>
        <i>↓</i>
        <span class="val">{{ result === null ? "—" : result }}</span>
      </div>
    </div>
  </section>
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from "vue";

type Engine = "loading" | "ready" | "error";

// The toy has no fallback on purpose. Its entire claim is that the number on
// screen came out of a C function, so a JavaScript answer here would be a lie
// dressed as a demo. When the module will not load, the button goes dead and
// the badge says so; the C source and the call path still carry the slide.
const props = withDefaults(defineProps<{ wasmUrl?: string }>(), {
  wasmUrl: () => `${import.meta.env.BASE_URL}wasm/double_it.wasm`,
});

const engine = ref<Engine>("loading");
const failure = ref("");
const wasm = ref<((n: number) => number) | null>(null);
const input = ref(21);
const result = ref<number | null>(null);

const engineLabel = computed(() => {
  if (engine.value === "ready")
    return result.value === null ? "WASM 準備完了" : "WASM で実行";
  if (engine.value === "error")
    return `WASM を読み込めませんでした${failure.value}`;
  return "WASM をロード中";
});

const engineClass = computed(() => ({
  "engine-wasm": engine.value === "ready",
  "engine-error": engine.value === "error",
}));

function run() {
  const call = wasm.value;
  if (!call) return;
  // int in, int out: the module has no linear memory to share and no imports.
  result.value = call(Math.trunc(Number(input.value) || 0));
}

onMounted(async () => {
  try {
    const response = await fetch(props.wasmUrl);
    if (!response.ok)
      throw new Error(`${response.status} ${response.statusText}`);
    const { instance } = await WebAssembly.instantiate(
      await response.arrayBuffer(),
      {},
    );
    const exported = instance.exports.double_it;
    if (typeof exported !== "function")
      throw new Error("double_it is not exported");
    wasm.value = exported as (n: number) => number;
    engine.value = "ready";
  } catch (error) {
    failure.value = error instanceof Error ? `（${error.message}）` : "";
    engine.value = "error";
  }
});
</script>

<style scoped>
.toy {
  display: grid;
  grid-template-columns: 0.92fr 1.08fr;
  column-gap: 52px;
  align-items: start;
  margin-top: 30px;
  font-family: var(--sans);
}

.toy-src {
  font-family: var(--mono);
  font-size: 23px;
  font-weight: 500;
  line-height: 1.8;
  margin: 0;
  color: var(--ink);
}
.toy-attr {
  display: block;
  font-size: 13px;
  line-height: 1.9;
  color: var(--ink-3);
}
.toy-file {
  margin: 18px 0 0;
  max-width: none;
  font: 500 13px var(--mono);
  color: var(--ink-3);
}
.toy-note {
  margin: 6px 0 0;
  max-width: none;
  font-size: 14px;
  color: var(--ink-2);
}

.toy-run {
  display: grid;
  row-gap: 20px;
  justify-items: start;
}

.toy-line {
  display: flex;
  align-items: center;
  gap: 20px;
}

/* An input with no box: the value sits on a hairline, the way the bytes sit on
   the ruler elsewhere in this deck. */
.toy-in {
  width: 112px;
  padding: 2px 0 6px;
  font: 500 46px var(--mono);
  color: var(--ink);
  text-align: center;
  background: none;
  border: none;
  border-bottom: 1px solid var(--rule-lit);
  border-radius: 0;
  outline: none;
}
.toy-in:focus-visible {
  border-bottom-color: var(--wide);
}
.toy-in::-webkit-outer-spin-button,
.toy-in::-webkit-inner-spin-button {
  appearance: none;
  margin: 0;
}

.toy .btn.lead {
  font-size: 17px;
  padding: 11px 18px;
  border-color: var(--sig);
  color: var(--sig);
}
.toy .btn.lead:disabled {
  border-color: var(--rule);
  color: var(--ink-3);
  cursor: default;
}

.toy-arrow {
  font-size: 26px;
  color: var(--rule-lit);
  transition: color 160ms ease;
}
.toy-arrow.on {
  color: var(--ink-3);
}

.toy-out {
  font: 500 62px var(--mono);
  line-height: 1;
  color: var(--ink-3);
  transition: color 160ms ease;
}
.toy-out.on {
  color: var(--sig);
}

.engine {
  font-size: 14px;
  color: var(--ink-2);
}
.engine-error {
  color: var(--err);
}

/* The path is the point of the slide, so it is legible from the start and only
   its answer lights up: the audience reads it once, then watches it resolve. */
.toy-path {
  display: grid;
  grid-template-columns: max-content;
  row-gap: 4px;
  margin-top: 6px;
  font: 500 15px/1.4 var(--mono);
  color: var(--ink-3);
  opacity: 0.45;
  transition: opacity 200ms ease;
}
.toy-path.on {
  opacity: 1;
}
.toy-path i {
  font-style: normal;
  line-height: 1.2;
  color: var(--rule-lit);
}
.toy-path .lit {
  color: var(--ink);
}
.toy-path .lit small {
  font-size: 11px;
  color: var(--ink-3);
}
.toy-path .val {
  color: var(--ink-3);
}
.toy-path.on .val {
  color: var(--sig);
}

.btn:focus-visible {
  outline: 2px solid var(--wide);
  outline-offset: 4px;
}
</style>
