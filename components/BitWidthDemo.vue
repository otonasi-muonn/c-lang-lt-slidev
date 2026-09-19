<template>
  <div class="bw">
    <div>
      <pre class="src">
int a = -1;
unsigned int b = 1;

printf("%d\n", a &lt; b);</pre>

      <button class="btn" :class="{ on: show }" @click="show = !show">
        {{ show ? "隠す" : "どうなる？" }}
      </button>
    </div>

    <div class="answer">
      <p class="note">
        Cでは「値」だけでなく、符号・幅・変換規則が結果に出てくる。
      </p>

      <div v-if="show" class="lines">
        <div>
          同じランクなので、<code>a</code> は必ず<br />
          <code>unsigned int</code> に変換される
        </div>
        <div><code>a &lt; b</code> は必ず <code class="sig">0</code></div>
      </div>
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
  grid-template-columns: 0.86fr 1.14fr;
  column-gap: 44px;
  align-items: start;
  margin-top: 14px;
}
.bw .src {
  font-size: 19px;
  line-height: 1.85;
}
.bw .btn {
  margin-top: 26px;
}
/* Reserve the answer's height so revealing it does not shift the slide. */
.answer {
  min-height: 182px;
}
.lines {
  display: grid;
  row-gap: 16px;
  margin-top: 26px;
  font-size: 19px;
  line-height: 1.55;
  color: var(--ink);
}
</style>
