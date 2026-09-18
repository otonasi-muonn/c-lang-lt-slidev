---
theme: default
title: AI時代に、なぜ今さらC言語なのか
info: |
  ハックツコミュ「自分の推し技術について語りたいよねの会」15分セッション用 Slidev 資料。
class: text-center
highlighter: shiki
lineNumbers: false
drawings:
  persist: false
transition: slide-left
mdc: true
colorSchema: dark
favicon: /favicon.svg
fonts:
  sans: Noto Sans JP
  mono: JetBrains Mono
---

# AI時代に、なぜ今さらC言語なのか

<div class="mt-6 text-xl opacity-80">
「候補から最初にCを消さないでほしい」
</div>

<div class="mt-16 text-sm opacity-60">
ハックツコミュ / 推し技術LT / 15min
</div>

---
layout: center
class: text-center
---

# 最初に殴っておく

<div class="grid grid-cols-2 gap-4 mt-8 text-left">
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">古い</div>
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">危ない</div>
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">書きやすくはない</div>
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">常に最速でもない</div>
</div>

<div class="mt-8 text-2xl">
それでも、Cはまだ面白い。
</div>

---
layout: center
---

# 今日の主張

<div class="text-3xl leading-relaxed mt-10">
Cは「古い低級言語」ではなく、<br>
<span class="text-green-300">コンピュータの境界面に立てる言語</span>。
</div>

<div class="mt-10 opacity-70">
OS / 組み込み / 共有ライブラリ / WASM / プロトコル / パフォーマンス
</div>

---

# Cを選ぶ理由は「速いから」だけじゃない

<TechSelection />

---
layout: center
---

# 身近な入口：USB

<div class="text-2xl leading-relaxed">
USBを挿しただけで動く。<br>
でも裏側では「お前は誰？何ができる？」を聞いている。
</div>

<div class="mt-8 rounded-xl bg-white/10 p-5 font-mono text-sm">
GET_DESCRIPTOR → Device Descriptor → Configuration → Interface → Endpoint
</div>

<div class="mt-8 opacity-70">
USBを語りたいわけではなく、Cで見ると「バイト列が構造を持つ」感じが見える。
</div>

---

# ただのバイト列が、構造体になる

```c {all|1-4|6-13|15-18}
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdUSB;

    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;

    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
} UsbDeviceDescriptor;
```

<div class="mt-6 text-xl">
Cは「データの実体」にかなり近いところで話せる。
</div>

---

# 型は、ただの名前じゃない

<BitWidthDemo />

---
layout: center
---

# C++の下位互換？

<div class="text-2xl leading-relaxed">
Cは「C++から機能を減らした言語」ではない。<br>
CにはCの都合、Cの設計、Cの進化がある。
</div>

<div class="mt-8 grid grid-cols-3 gap-4 text-center">
  <div class="rounded-xl bg-white/10 p-4"><code>restrict</code></div>
  <div class="rounded-xl bg-white/10 p-4"><code>_Generic</code></div>
  <div class="rounded-xl bg-white/10 p-4">designated initializer</div>
</div>

---

# AI時代だからこそのC

<div class="grid grid-cols-2 gap-6 mt-8">
<div>

## AIに書かせる

```c
char *copy(const char *s) {
    char buf[256];
    strcpy(buf, s);
    return buf;
}
```

</div>
<div>

## 人間が見るべきもの

- そのメモリはいつまで生きる？
- 境界チェックはある？
- 未定義動作は踏んでない？
- ABI / FFIで壊れない？

</div>
</div>

<div class="mt-8 text-xl">
AIがコードを書くほど、「実際に何が起きるか」を読む力が効いてくる。
</div>

---
layout: center
---

# WebでもCは触れる

<div class="text-2xl leading-relaxed">
今はCをWASMにして、ブラウザで動かす選択肢もある。<br>
Cは「遠い低レイヤ」だけのものではない。
</div>

<div class="mt-8 rounded-xl bg-white/10 p-5 font-mono text-sm">
C → LLVM → WebAssembly → Browser
</div>

<div class="mt-8 opacity-70">
本格デモを入れるなら、ここを独立ページに逃がす。
</div>

---
layout: center
class: text-center
---

# まとめ

<div class="text-3xl leading-relaxed">
Cは万能ではない。<br>
でも、候補から最初に消すには惜しい。
</div>

<div class="mt-10 text-xl opacity-80">
速さ / 互換性 / 境界面 / 小ささ / 低レイヤ理解
</div>

---
layout: center
class: text-center
---

# 技術選定で、最初からCを消さないでほしい

<div class="mt-8 text-xl opacity-70">
Thank you!
</div>

