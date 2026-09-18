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
    title: '境界面に強い',
    body: 'OS、ハードウェア、FFI、プロトコルなど、抽象化の境目に立ちやすい。',
    accent: 'text-green-300',
  },
  {
    title: '小さく持てる',
    body: 'ランタイム前提が薄く、埋め込みや既存資産との接続に向く場面がある。',
    accent: 'text-blue-300',
  },
  {
    title: 'データの形が見える',
    body: 'ビット幅、アライメント、メモリ配置がプログラムの意味として表に出る。',
    accent: 'text-yellow-300',
  },
  {
    title: '理解が資産になる',
    body: 'Cそのものを書かなくても、他言語の裏側やAI生成コードを読む力につながる。',
    accent: 'text-purple-300',
  },
]
</script>
