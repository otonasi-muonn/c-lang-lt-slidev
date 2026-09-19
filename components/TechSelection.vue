<template>
  <div class="selection">
    <div v-for="item in items" :key="item.title" class="row">
      <div class="claim">{{ item.title }}</div>
      <div class="detail">{{ item.body }}</div>
    </div>
  </div>
</template>

<script setup lang="ts">
const items = [
  {
    title: "バイト列を型にする",
    body: "USBの18バイトを、構造体のフィールドとして読める。",
  },
  {
    title: "境界をまたげる",
    body: "デバイス、OS、他言語、Webの間に小さな共通コアを置ける。",
  },
  {
    title: "小さく動かせる",
    body: "大きなランタイムに頼らず、実行環境の制約に合わせられる。",
  },
  {
    title: "WASMで運べる",
    body: "Cのコアをブラウザで動かし、ネイティブ資産とWebをつなげる。",
  },
];
</script>

<style scoped>
/* One hairline per claim, running the full measure: the rule separates
   claims, it does not wrap each one in a box. */
.selection {
  margin-top: 8px;
}
.row {
  display: grid;
  grid-template-columns: 218px 1fr;
  column-gap: 26px;
  align-items: baseline;
  padding: 28px 0;
  border-top: 1px solid var(--rule);
}
.row:first-child {
  border-top: none;
  padding-top: 6px;
}
.row .claim {
  font-size: 20px;
  font-weight: 700;
  letter-spacing: -0.01em;
  color: var(--ink);
}
.row .detail {
  font-size: 17px;
  line-height: 1.66;
  color: var(--ink-2);
}
</style>
