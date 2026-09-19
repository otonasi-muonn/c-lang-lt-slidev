<template>
  <div class="evid">
    <div v-for="item in items" :key="item.claim" class="evid-row">
      <div class="evid-claim">{{ item.claim }}</div>
      <div class="evid-fact" v-html="item.fact"></div>
      <div class="evid-body" v-html="item.body"></div>
    </div>
  </div>
</template>

<script setup lang="ts">
// Each claim carries the thing from this talk that backs it, so the middle
// column reads as evidence at a glance rather than as more prose. Every fact
// here was on screen earlier: the decoded VID, the demo's data path, the size
// of the module that was actually fetched, and the build it came from.
const items = [
  {
    claim: "バイト列を型にする",
    fact: '6D 04 → idVendor = <span class="wide">0x046D</span>',
    body: "USBの18バイトを、<br>構造体のフィールドとして読める。",
  },
  {
    claim: "境界をまたげる",
    fact: "JS → linear memory → C",
    body: "デバイス、OS、他言語、Webの間に<br>小さな共通コアを置ける。",
  },
  {
    claim: "小さく動かせる",
    fact: "usb_descriptor.wasm = 769 B",
    body: "大きなランタイムに頼らず、<br>実行環境の制約に合わせられる。",
  },
  {
    claim: "WASMで運べる",
    fact: "usb_descriptor.c → .wasm",
    body: "Cのコアをブラウザで動かし、<br>ネイティブ資産とWebをつなげる。",
  },
];
</script>
