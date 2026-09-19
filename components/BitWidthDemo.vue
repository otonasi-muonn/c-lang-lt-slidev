<template>
  <div class="grid grid-cols-[1.1fr_0.9fr] gap-6 mt-4 items-start">
    <div>
      <pre
        class="rounded-xl bg-black/60 p-5 text-base leading-relaxed"
      ><code>int a = -1;
unsigned int b = 1;

printf("%d\n", a &lt; b);</code></pre>
      <button
        class="mt-4 rounded-lg bg-green-400/20 border border-green-300/40 px-4 py-2 hover:bg-green-400/30"
        @click="show = !show"
      >
        {{ show ? '隠す' : 'どうなる？' }}
      </button>
    </div>

    <div class="rounded-xl border border-white/10 bg-white/5 p-5 min-h-72">
      <div class="text-lg font-bold">ポイント</div>
      <div class="mt-3 opacity-80 leading-relaxed">
        Cでは「値」だけでなく、符号・幅・変換規則が結果に出てくる。
      </div>
      <div v-if="show" class="mt-5 space-y-3">
        <div
          class="rounded-lg bg-yellow-300/10 border border-yellow-300/30 p-3"
        >
          同じランクなので、<code>a</code> は必ず unsigned int に変換される
        </div>
        <div class="rounded-lg bg-red-300/10 border border-red-300/30 p-3">
          <code>a &lt; b</code> は必ず <code>0</code>
        </div>
        <div class="rounded-lg bg-green-300/10 border border-green-300/30 p-3">
          ここが「コンピュータの実体が見える」おもしろさ
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
const show = ref(false)
</script>
