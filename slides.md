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
canvasWidth: 900
favicon: /favicon.svg
fonts:
  sans: Noto Sans JP
  mono: JetBrains Mono
---

# AI時代に、なぜ今さらC言語なのか

<div class="mt-6 text-xl opacity-80">
「候補から最初にCを消さないでほしい」
</div>

<div class="mt-16 text-base opacity-60">
ハックツコミュ / 推し技術LT / 15min
</div>

<!--
想定: 30秒
役割: 名乗りと結論を先に置き、USBから技術選定までを一本で話すと宣言する。
-->

---
layout: center
class: text-center
---

# 古い・危ない・書きやすくない・最速でもない

<div class="grid grid-cols-2 gap-4 mt-8 text-left">
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">古い</div>
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">危ない</div>
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">書きやすくはない</div>
  <div class="rounded-xl border border-red-400/30 p-5 bg-red-500/10">常に最速でもない</div>
</div>

<div class="mt-8 text-2xl">
それでも、Cはまだ面白い。<br>
<span class="text-green-300">コンピュータの境界面に立てるから。</span>
</div>

<!--
想定: 45秒
役割: Cを万能視せず弱点を認めた上で、今日の主張を一枚に統合する。
-->

---
layout: center
---

# USBを挿すと何が起きているか

<!-- SLOT:USB-ACCURACY -->

<div class="grid grid-cols-4 gap-3 mt-10 text-center">
  <div class="rounded-xl border border-white/10 bg-white/5 p-4"><div class="opacity-60">1</div>接続</div>
  <div class="rounded-xl border border-white/10 bg-white/5 p-4"><div class="opacity-60">2</div>リセット</div>
  <div class="rounded-xl border border-green-300/40 bg-green-300/10 p-4"><div class="opacity-60">3</div>記述子を読む</div>
  <div class="rounded-xl border border-white/10 bg-white/5 p-4"><div class="opacity-60">4</div>設定する</div>
</div>

<div class="mt-10 text-2xl leading-relaxed">
PCは「お前は誰で、何ができる？」を<br>小さなバイト列に聞いている。
</div>

<!--
想定: 60秒
役割: USB enumeration を入口に、物理デバイスとの会話がバイト列で始まることを示す。詳細は USB 正確版スロットで差し替える。
-->

---
layout: center
class: text-center
---

# その答えは、18バイト

<div class="mt-10 rounded-xl bg-black/60 border border-white/10 p-6 font-mono text-base leading-relaxed text-left">
12 01 00 02 00 00 00 40<br>
6A 0B 46 53 00 01 01 02<br>
03 01
</div>

<div class="mt-10 text-2xl">
この時点では、ただの 18 バイト。
</div>

<div class="mt-5 opacity-70">
意味を与えるのは、次の一手。
</div>

<!--
想定: 45秒
役割: 生の hex を先に見せ、意味のないバイト列への違和感をつくる。値と解説は USB 正確版スロットで差し替える。
-->

---

# バイト列が構造体になる

<pre class="mt-5 rounded-xl bg-black/60 border border-white/10 p-5 text-base leading-relaxed"><code>typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass, bDeviceSubClass;
  uint8_t  bDeviceProtocol, bMaxPacketSize0;
  uint16_t idVendor, idProduct, bcdDevice;
  uint8_t  iManufacturer, iProduct, iSerialNumber;
  uint8_t  bNumConfigurations;
} UsbDeviceDescriptor;</code></pre>

<div class="mt-7 text-xl">
同じ 18 バイトを、フィールド名と型で読める。
</div>

<!--
想定: 75秒
役割: プロトコル上のバイト列を C の構造体として読む接続を見せる。完全な定義・属性は USB 正確版スロットで差し替える。
-->

---
layout: center
---

# <code>sizeof</code> != <code>bLength</code>

<div class="grid grid-cols-2 gap-6 mt-10">
  <div class="rounded-xl border border-green-300/30 bg-green-300/10 p-6">
    <div class="text-xl font-bold"><code>bLength</code></div>
    <div class="mt-4 opacity-80">プロトコルが送ってきた<br>「この記述子は何バイトか」</div>
  </div>
  <div class="rounded-xl border border-yellow-300/30 bg-yellow-300/10 p-6">
    <div class="text-xl font-bold"><code>sizeof</code></div>
    <div class="mt-4 opacity-80">この環境のコンパイラが決めた<br>「構造体の置き方」</div>
  </div>
</div>

<div class="mt-10 text-2xl">
同じ「サイズ」でも、見ている境界が違う。
</div>

<!--
想定: 90秒
役割: wire format と C のメモリ表現を区別し、Cで境界や実体が表に出る瞬間をつくる。技術詳細は USB 正確版スロットで差し替える。
-->

---
layout: center
---

# LIVE DEMO: C → WASM

<div class="mt-6 text-2xl leading-relaxed">
さっきのバイト列を、ブラウザの中で<br>
<span class="text-green-300">C がそのまま読む。</span>
</div>

<!-- SLOT:WASM-DEMO -->

<div class="mt-10 rounded-xl border border-green-300/30 bg-green-300/10 p-6 text-left">
<div class="font-mono text-base">C → WebAssembly → Browser</div>
<div class="mt-4 opacity-80">ここで 18 バイトを入力し、C の読み方と境界をライブで追う。</div>
</div>

<!--
想定: 165秒
役割: USB のバイト列を読む C を WASM としてブラウザ上で実演し、前半の抽象を体験に変える。UsbDescriptorDemo の挿入位置は WASM デモスロット。
-->

---

# Cを選ぶ理由は「速いから」だけじゃない

<!-- SLOT:TECH-SELECTION -->

<TechSelection />

<!--
想定: 60秒
役割: デモで見た境界面・データ表現の強みを、技術選定で効く条件として整理する。
-->

---

# AI時代だからこそのC

<div class="grid grid-cols-2 gap-6 mt-8">
<div>

## AIに書かせる

<pre class="rounded-xl bg-black/60 border border-white/10 p-5 text-base leading-relaxed text-left"><code>char *copy(const char *s) {
  char buf[256];
  strcpy(buf, s);
  return buf;
}</code></pre>

</div>
<div>

## 人間が見るべきもの

- そのメモリはいつまで生きる？
- 境界チェックはある？
- 未定義動作は踏んでない？
- ABI / FFI で壊れない？

</div>
</div>

<div class="mt-8 text-xl">
AIがコードを書くほど、「実際に何が起きるか」を読む力が効いてくる。
</div>

<!--
想定: 75秒
役割: AI生成コードを題材に、Cの実体を読む視点がレビューや境界設計で生きるとタイトルを回収する。
-->

---
layout: center
class: text-center
---

# まとめ

<div class="text-3xl leading-relaxed mt-10">
Cは万能ではない。<br>
でも、候補から最初に消すには惜しい。
</div>

<div class="mt-10 text-xl opacity-80">
速さ / 互換性 / 境界面 / 小ささ / 低レイヤ理解
</div>

<!--
想定: 45秒
役割: Cを選ぶ条件を再掲し、万能ではないという前提を保ったまま結論へ収束させる。
-->

---
layout: center
class: text-center
---

# 技術選定で、最初からCを候補外にしないでほしい

<div class="mt-10 text-2xl opacity-80">
USB の 18 バイトから、ブラウザの WASM まで。<br>
境界が重要な場面では、C にも席がある。
</div>

<div class="mt-12 text-xl opacity-70">
Thank you!
</div>

<!--
想定: 30秒
役割: USBからC、WASM、技術選定までの一本線を最後のメッセージとして閉じる。
-->

---
layout: center
---

# Appendix: 型は、ただの名前じゃない

<BitWidthDemo />

<!--
想定: 本編時間外
役割: signed / unsigned の変換規則を、質問があった場合に補足する。
-->

---
layout: center
---

# Appendix: C++の下位互換？

<div class="text-2xl leading-relaxed">
Cは「C++から機能を減らした言語」ではない。<br>
CにはCの都合、Cの設計、Cの進化がある。
</div>

<div class="mt-8 grid grid-cols-3 gap-4 text-center">
  <div class="rounded-xl bg-white/10 p-4"><code>restrict</code></div>
  <div class="rounded-xl bg-white/10 p-4"><code>_Generic</code></div>
  <div class="rounded-xl bg-white/10 p-4">designated initializer</div>
</div>

<!--
想定: 本編時間外
役割: CとC++の関係について質問があった場合の補足に限定する。
-->
