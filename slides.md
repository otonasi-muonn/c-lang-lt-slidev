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
layout: two-cols
---

# USBを挿すと何が起きているか

::left::

## enumeration（時系列）

<div class="text-sm leading-relaxed space-y-2 mt-3">
  <div>接続検出 → バスリセット<br><span class="opacity-65">Default / address 0 / EP0 のみ</span></div>
  <div><code>GET_DESCRIPTOR(Device, 8)</code><br><span class="opacity-65">offset 7 の <code>bMaxPacketSize0</code> を知る</span></div>
  <div class="opacity-65">（必要なら再リセット：ホスト実装依存）</div>
  <div><code>SET_ADDRESS(n)</code><br><span class="opacity-65">新 address は Status ステージ完了後に有効</span></div>
  <div><code>GET_DESCRIPTOR(Device, 18)</code></div>
  <div><code>GET_DESCRIPTOR(Configuration, 9)</code><br><span class="opacity-65"><code>wTotalLength</code> を読む</span></div>
  <div><code>GET_DESCRIPTOR(Configuration, wTotalLength)</code><br><span class="opacity-65">連結された descriptor 群を一括取得</span></div>
  <div><code>SET_CONFIGURATION(bConfigurationValue)</code></div>
</div>

::right::

## descriptor（階層）

<pre class="text-sm leading-relaxed mt-3"><code>Device (18B)
└─ Configuration (9B) × bNumConfigurations
   └─ Interface (9B) × bNumInterfaces
      ├─ Endpoint (7B) × bNumEndpoints
      └─ クラス固有 (HID / CDC …)</code></pre>

<div class="mt-4 text-sm leading-relaxed opacity-80">
String Descriptor は木の外。各 <code>i*</code> index から横参照する。<br>
EP0 には Endpoint Descriptor がない。だから <code>bMaxPacketSize0</code> は Device 側にある。
</div>

<div class="mt-5 rounded-xl bg-yellow-300/10 border border-yellow-300/30 p-3 text-sm">
<code>GET_DESCRIPTOR</code> はリクエスト種別。木の頂点ではない。
</div>

<!--
想定: 60秒
役割: 左は起きた順、右は返ってきたデータの形。混ぜると GET_DESCRIPTOR が親に見えてしまう。
Configuration 以下は順番に別々に取るのではなく、長さを読んでから一つの連結ブロブとして取る。
-->

---
layout: center
class: text-center
---

# その答えは、18バイト

<div class="mt-10 rounded-xl bg-black/60 border border-white/10 p-6 font-mono text-xl leading-relaxed text-left">
12 01 00 02 00 00 00 08<br>
6D 04 2B C5 00 12 01 02<br>
00 01
</div>

<div class="mt-8 text-2xl">
この時点では、ただの 18 バイト。
</div>

<div class="mt-4 opacity-70">
意味を与えるのは、次の一手。
</div>

<div class="mt-6 text-sm opacity-60">
実機の生ダンプではなく、実在する VID / PID で組んだ説明用の例。
</div>

<!--
想定: 45秒
役割: 生の hex を先に見せ、意味のないバイト列への違和感をつくる。この18バイトは後段のデモでそのまま解析する。
-->

---

# バイト列が構造体になる

<pre class="mt-5 rounded-xl bg-black/60 border border-white/10 p-5 text-base leading-relaxed"><code>typedef struct {
  uint8_t  bLength;             <span class="opacity-50">// offset 0</span>
  uint8_t  bDescriptorType;     <span class="opacity-50">// 1</span>
  uint16_t bcdUSB;              <span class="opacity-50">// 2</span>
  uint8_t  bDeviceClass;        <span class="opacity-50">// 4</span>
  uint8_t  bDeviceSubClass;     <span class="opacity-50">// 5</span>
  uint8_t  bDeviceProtocol;     <span class="opacity-50">// 6</span>
  uint8_t  bMaxPacketSize0;     <span class="opacity-50">// 7</span>
  uint16_t idVendor;            <span class="opacity-50">// 8</span>
  uint16_t idProduct;           <span class="opacity-50">// 10</span>
  uint16_t bcdDevice;           <span class="opacity-50">// 12</span>
  uint8_t  iManufacturer;       <span class="opacity-50">// 14</span>
  uint8_t  iProduct;            <span class="opacity-50">// 15</span>
  uint8_t  iSerialNumber;       <span class="opacity-50">// 16</span>
  uint8_t  bNumConfigurations;  <span class="opacity-50">// 17</span>
} UsbDeviceDescriptor;          <span class="opacity-50">// wire format: 18 bytes</span></code></pre>

<div class="mt-5 text-base opacity-80">
<code>iManufacturer</code> / <code>iProduct</code> / <code>iSerialNumber</code> は String Descriptor への index。0 は「文字列なし」。
末尾の <code>bNumConfigurations</code> が、Configuration が複数あり得る入口になる。
</div>

<!--
想定: 75秒
役割: 18バイトを18バイトとして読む。末尾4バイトは飾りではない。
文字列は index で横に飛び、Configuration は複数持てる。
-->

---

# <code>bLength</code> を信じろ。<code>sizeof</code> を信じるな。

<table class="mt-6 w-full text-left text-base">
  <thead><tr class="border-b border-white/20"><th class="pb-2">Descriptor</th><th class="pb-2">wire 上の <code>bLength</code></th><th class="pb-2">よくある ABI での <code>sizeof</code></th></tr></thead>
  <tbody>
    <tr><td class="py-1">Device</td><td>18</td><td class="text-green-300">18 — たまたま一致</td></tr>
    <tr><td class="py-1">Configuration</td><td>9</td><td class="text-red-300">10 — 末尾 padding 1</td></tr>
    <tr><td class="py-1">Interface</td><td>9</td><td class="text-green-300">9 — たまたま一致</td></tr>
    <tr><td class="py-1">Endpoint</td><td>7</td><td class="text-red-300">8 — 末尾 padding 1</td></tr>
  </tbody>
</table>

<div class="mt-6 text-xl">
Configuration は <code>wTotalLength</code> bytes の連結ブロブ。<br>
<code>p += sizeof(*desc)</code> で 1 バイトずれると、以降が全部壊れる。
</div>

<div class="mt-4 text-sm opacity-60">
C 規格はこの <code>sizeof</code> を保証しない。典型 ABI の実演であって wire format の定義ではない。
</div>

<!--
想定: 90秒
役割: Device で18と出るのは正解ではなく偶然。Endpoint は7が8になる。
同じUSBの descriptor なのに、合うものと合わないものが混ざる。
だからポインタを進める基準は C の都合ではなく wire 上の bLength。
-->

---

# LIVE DEMO: C → WASM

<UsbDescriptorDemo />

<!--
想定: 165秒
役割: 18バイトをブラウザの linear memory に書き、C/WASM がそれを読む。
進行: (1) 解析成功で VID/PID (2) bLength 改竄で -2 (3) 8バイトで -1 (4) Big-endian で 0x6D04。
ポインタ値はただのメモリオフセット。import object は空 = JSグルーもWASI依存もない。
失敗時: 自動で JS フォールバックに落ちるのでそのまま進行してよい。
-->

---

# Cを選ぶ理由は「速いから」だけじゃない

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
---

# 次に、この条件を見たら C を思い出す

<div class="grid grid-cols-2 gap-4 mt-8 text-left text-xl">
  <div class="rounded-xl border border-white/10 bg-white/5 p-5">デバイス / OS とつながる</div>
  <div class="rounded-xl border border-white/10 bg-white/5 p-5">言語をまたぐ共通コアを置く</div>
  <div class="rounded-xl border border-white/10 bg-white/5 p-5">ランタイムを薄くして小さく動かす</div>
  <div class="rounded-xl border border-white/10 bg-white/5 p-5">既存の C 資産を Web へ運ぶ</div>
</div>

<div class="mt-10 text-xl opacity-80">
このどれにも当てはまらないなら、C を選ばなくてよい。
</div>

<!--
想定: 45秒
役割: 「Cは万能ではない」を保ったまま、次の技術選定で思い出すトリガーを4つに絞って渡す。
最後の1行で、Cを常に選ぶべきという主張にならないよう明示的に逆側を置く。
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
