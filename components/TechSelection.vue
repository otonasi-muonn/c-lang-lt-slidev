<template>
  <div class="grid grid-cols-2 gap-4 mt-6">
    <div v-for="item in items" :key="item.title" class="rounded-xl border border-white/10 bg-white/5 p-5">
      <div class="text-xl font-bold" :class="item.accent">{{ item.title }}</div>
      <div class="mt-2 opacity-75 leading-relaxed">{{ item.body }}</div>
    </div>
  </div>
</template>

<script setup lang="ts">
const items = [
  {
    title: 'バイト列を型にする',
    body: 'USBの18バイトを、構造体のフィールドとして読める。',
    accent: 'text-green-300',
  },
  {
    title: '境界をまたげる',
    body: 'デバイス、OS、他言語、Webの間に小さな共通コアを置ける。',
    accent: 'text-blue-300',
  },
  {
    title: '小さく動かせる',
    body: '大きなランタイムに頼らず、実行環境の制約に合わせられる。',
    accent: 'text-yellow-300',
  },
  {
    title: 'WASMで運べる',
    body: 'Cのコアをブラウザで動かし、ネイティブ資産とWebをつなげる。',
    accent: 'text-purple-300',
  },
]
</script>
