<template>
  <div class="bw">
    <pre class="src">int a = -1;
unsigned int b = 1;

printf("%d\n", a &lt; b);</pre>

    <div class="answer">
      <button class="btn" :class="{ on: show }" @click="show = !show">
        {{ show ? "隠す" : "どうなる？" }}
      </button>

      <div v-if="show" class="lines">
        <div>
          同じランクなので、<code>a</code> は必ず
          <code>unsigned int</code> に変換される
        </div>
        <div>
          <code>a &lt; b</code> は必ず <code class="sig">0</code>
        </div>
      </div>
      <p v-else class="note">
        Cでは「値」だけでなく、符号・幅・変換規則が結果に出てくる。
      </p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
const show = ref(false);
</script>

<style scoped>
.bw {
  display: grid;
  grid-template-columns: 0.9fr 1.1fr;
  column-gap: 40px;
  align-items: start;
  margin-top: 10px;
}
.bw .src {
  font-size: 19px;
  line-height: 1.85;
}
.answer {
  min-height: 150px;
}
.lines {
  display: grid;
  row-gap: 14px;
  margin-top: 24px;
  font-size: 19px;
  line-height: 1.55;
  color: var(--ink);
}
.answer .note {
  margin-top: 20px;
}
</style>
