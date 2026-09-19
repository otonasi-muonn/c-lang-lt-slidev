---
theme: default
title: AI時代に、なぜ今さらC言語なのか
info: |
  ハックツコミュ「自分の推し技術について語りたいよねの会」15分セッション用 Slidev 資料。
class: bleed spread
highlighter: shiki
lineNumbers: false
drawings:
  persist: false
transition: slide-left
mdc: true
layout: default
colorSchema: dark
canvasWidth: 900
favicon: /favicon.svg
fonts:
  sans: Noto Sans JP
  mono: JetBrains Mono
---


<div>

<h1 class="say">AI時代に、<br>なぜ今さらC言語なのか</h1>

<p class="lede">「候補から最初にCを消さないでほしい」</p>

</div>

<div>

<div class="bytes small faint">
<span>12</span>
<span>01</span>
<span>00</span>
<span>02</span>
<span>00</span>
<span>00</span>
<span>00</span>
<span>08</span>
<span>6D</span>
<span>04</span>
<span>2B</span>
<span>C5</span>
<span>00</span>
<span>12</span>
<span>01</span>
<span>02</span>
<span>00</span>
<span>01</span>
</div>

<p class="note" style="margin-top: 22px">ハックツコミュ「推し技術LT」15min</p>

</div>

<!--
想定: 30秒
役割: 名乗りと結論を先に置き、USBから技術選定までを一本で話すと宣言する。
-->

---
class: bleed mid
---

<p class="note" style="font-size: 20px; line-height: 1.6">古い。危ない。書きやすくはない。常に最速でもない。</p>

<h1 class="say" style="margin-top: 26px; margin-bottom: 0">それでも、Cはまだ面白い。<br>コンピュータの境界面に立てるから。</h1>

<!--
想定: 45秒
役割: Cを万能視せず弱点を認めた上で、今日の主張を一枚に統合する。
-->

---

<div class="k">USB 2.0</div>

<h1 class="compact">USBを挿すと、何が起きているか</h1>

<div class="cols">
<div>

<h2>enumeration（時系列）<span class="faint">　host ▶ ◀ device</span></h2>

<div class="exch">
<div class="exch-n">1</div>
<div class="exch-out"></div>
<div><div class="exch-req">接続検出 → バスリセット</div><div class="exch-foot"><span class="exch-sub">Default / address 0 / EP0 のみ</span></div></div>
<div class="exch-n">2</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">GET_DESCRIPTOR(Device, 8)</div><div class="exch-foot"><span class="exch-sub">offset 7 の <code>bMaxPacketSize0</code> を知る<br>（必要なら再リセット：ホスト実装依存）</span><span class="exch-ret ">◀ 8 B</span></div></div>
<div class="exch-n">3</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">SET_ADDRESS(n)</div><div class="exch-foot"><span class="exch-sub">新 address は Status ステージ完了後に有効</span></div></div>
<div class="exch-n">4</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">GET_DESCRIPTOR(Device, 18)</div><div class="exch-foot"><span class="exch-sub"></span><span class="exch-ret sig">◀ 18 B</span></div></div>
<div class="exch-n">5</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">GET_DESCRIPTOR(Configuration, 9)</div><div class="exch-foot"><span class="exch-sub"><code>wTotalLength</code> を読む</span><span class="exch-ret ">◀ 9 B</span></div></div>
<div class="exch-n">6</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">GET_DESCRIPTOR(Configuration, wTotalLength)</div><div class="exch-foot"><span class="exch-sub">連結された descriptor 群を一括取得</span><span class="exch-ret ">◀ wTotalLength B</span></div></div>
<div class="exch-n">7</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">SET_CONFIGURATION(bConfigurationValue)</div></div>
</div>

</div>
<div>

<h2>descriptor（階層）<span class="faint">　棒の長さ = bLength</span></h2>

<div class="nest">
<div class="nest-name" style="padding-left: 0px">Device</div>
<div class="nest-len"><span class="nest-bar" style="width: 90px"></span>18B</div>
<div class="nest-name" style="padding-left: 14px">Configuration</div>
<div class="nest-len"><span class="nest-bar" style="width: 45px"></span>9B</div>
<div class="nest-mul" style="padding-left: 14px">× bNumConfigurations</div>
<div class="nest-name" style="padding-left: 28px">Interface</div>
<div class="nest-len"><span class="nest-bar" style="width: 45px"></span>9B</div>
<div class="nest-mul" style="padding-left: 28px">× bNumInterfaces</div>
<div class="nest-name" style="padding-left: 42px">Endpoint</div>
<div class="nest-len"><span class="nest-bar" style="width: 35px"></span>7B</div>
<div class="nest-mul" style="padding-left: 42px">× bNumEndpoints</div>
<div class="nest-name" style="padding-left: 42px">クラス固有</div>
<div class="nest-len faint">HID / CDC … <span class="nest-mul">長さは可変</span></div>
</div>

<div class="qs fine" style="margin-top: 20px">
<div>String Descriptor は木の外。各 <code>i*</code> index から横参照する。</div>
<div>EP0 には Endpoint Descriptor がない。だから <code>bMaxPacketSize0</code> は Device 側にある。</div>
</div>

</div>
</div>

<p class="punch" style="margin-top: 18px; font-size: 18px"><code>GET_DESCRIPTOR</code> はリクエスト種別。木の頂点ではない。</p>

<!--
想定: 60秒
役割: 左は起きた順、右は返ってきたデータの形。混ぜると GET_DESCRIPTOR が親に見えてしまう。
Configuration 以下は順番に別々に取るのではなく、長さを読んでから一つの連結ブロブとして取る。

ペース: このスライドは 75 秒でハードキャップ。語るのは 接続検出 →
GET_DESCRIPTOR(Device, 8) → SET_ADDRESS → Configuration 2段階取得 の4点だけ。
再リセットと Status ステージの但し書きは読み上げず画面に置くだけにする。

聞かれたら: bNumInterfaces は interface 番号の数であって Interface Descriptor の総数ではない。
alternate setting の分だけ Interface Descriptor は増える。
-->

---
class: bleed mid
---

# その答えは、18バイト

<div class="bytes hero" style="margin-top: 30px">
<span>12</span>
<span>01</span>
<span>00</span>
<span>02</span>
<span>00</span>
<span>00</span>
<span>00</span>
<span>08</span>
<span>6D</span>
<span>04</span>
<span>2B</span>
<span>C5</span>
<span>00</span>
<span>12</span>
<span>01</span>
<span>02</span>
<span>00</span>
<span>01</span>
</div>

<div class="ruler hero">
<span class="t">0</span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class="t">8</span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class="t">17</span>
</div>

<p class="lede" style="margin-top: 40px">この時点では、ただの 18 バイト。<br><span class="dim">意味を与えるのは、次の一手。</span></p>

<p class="note" style="margin-top: 26px">実機の生ダンプではなく、実在する VID / PID で組んだ説明用の例。</p>

<!--
想定: 45秒
役割: 生の hex を先に見せ、意味のないバイト列への違和感をつくる。この18バイトは後段のデモでそのまま解析する。
-->

---

# バイト列が構造体になる

<div class="k">offset</div>

<div class="dump-head"><span>wire bytes</span><span>C declaration</span><span>value</span></div>

<div class="k cl"></div>
<div class="dline"><span class="dline-hex "></span><span class="dline-src">typedef struct {</span><span class="dline-val "></span></div>
<div class="k cl">0</div>
<div class="dline"><span class="dline-hex ">12</span><span class="dline-src">  uint8_t  bLength;</span><span class="dline-val "></span></div>
<div class="k cl">1</div>
<div class="dline"><span class="dline-hex ">01</span><span class="dline-src">  uint8_t  bDescriptorType;</span><span class="dline-val "></span></div>
<div class="k cl">2</div>
<div class="dline"><span class="dline-hex wide">00 02</span><span class="dline-src">  uint16_t bcdUSB;</span><span class="dline-val wide">0x0200</span></div>
<div class="k cl">4</div>
<div class="dline"><span class="dline-hex ">00</span><span class="dline-src">  uint8_t  bDeviceClass;</span><span class="dline-val "></span></div>
<div class="k cl">5</div>
<div class="dline"><span class="dline-hex ">00</span><span class="dline-src">  uint8_t  bDeviceSubClass;</span><span class="dline-val "></span></div>
<div class="k cl">6</div>
<div class="dline"><span class="dline-hex ">00</span><span class="dline-src">  uint8_t  bDeviceProtocol;</span><span class="dline-val "></span></div>
<div class="k cl">7</div>
<div class="dline"><span class="dline-hex ">08</span><span class="dline-src">  uint8_t  bMaxPacketSize0;</span><span class="dline-val "></span></div>
<div class="k cl">8</div>
<div class="dline"><span class="dline-hex wide">6D 04</span><span class="dline-src">  uint16_t idVendor;</span><span class="dline-val wide">0x046D<span class="jp">　wire は little-endian</span></span></div>
<div class="k cl">10</div>
<div class="dline"><span class="dline-hex wide">2B C5</span><span class="dline-src">  uint16_t idProduct;</span><span class="dline-val wide">0xC52B</span></div>
<div class="k cl">12</div>
<div class="dline"><span class="dline-hex wide">00 12</span><span class="dline-src">  uint16_t bcdDevice;</span><span class="dline-val wide">0x1200</span></div>
<div class="k cl">14</div>
<div class="dline"><span class="dline-hex ">01</span><span class="dline-src">  uint8_t  iManufacturer;</span><span class="dline-val "><span class="jp">String Descriptor への index</span></span></div>
<div class="k cl">15</div>
<div class="dline"><span class="dline-hex ">02</span><span class="dline-src">  uint8_t  iProduct;</span><span class="dline-val "></span></div>
<div class="k cl">16</div>
<div class="dline"><span class="dline-hex ">00</span><span class="dline-src">  uint8_t  iSerialNumber;</span><span class="dline-val "></span></div>
<div class="k cl">17</div>
<div class="dline"><span class="dline-hex ">01</span><span class="dline-src">  uint8_t  bNumConfigurations;</span><span class="dline-val "><span class="jp">Configuration は複数あり得る</span></span></div>
<div class="k cl end">18</div>
<div class="dline"><span class="dline-hex "></span><span class="dline-src">} UsbDeviceDescriptor;</span><span class="dline-val "></span></div>

<!--
想定: 75秒
役割: 18バイトを18バイトとして読む。末尾4バイトは飾りではない。
文字列は index で横に飛び、Configuration は複数持てる。
-->

---

<div class="k">ABI</div>

# <code>bLength</code> を信じろ。<code>sizeof</code> を信じるな。

<div class="abi" style="margin-top: 8px">
<div class="abi-name">Device</div><div class="abi-lab">bLength</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">18</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">18</div><div class="abi-note ">たまたま一致</div>
<div class="abi-gap"></div>
<div class="abi-name">Configuration</div><div class="abi-lab">bLength</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div><div class="abi-num">10</div><div class="abi-note sig">末尾 padding 1</div>
<div class="abi-gap"></div>
<div class="abi-name">Interface</div><div class="abi-lab">bLength</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div class="abi-note ">たまたま一致</div>
<div class="abi-gap"></div>
<div class="abi-name">Endpoint</div><div class="abi-lab">bLength</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">7</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div><div class="abi-num">8</div><div class="abi-note sig">末尾 padding 1</div>
</div>

<p class="punch" style="margin-top: 22px; font-size: 20px">Configuration は <code>wTotalLength</code> bytes の連結ブロブ。<br><code>p += sizeof(*desc)</code> で 1 バイトずれると、以降が全部壊れる。</p>

<p class="note" style="margin-top: 14px">C 規格はこの <code>sizeof</code> を保証しない。典型 ABI の実演であって wire format の定義ではない。</p>

<!--
想定: 90秒
役割: Device で18と出るのは正解ではなく偶然。Endpoint は7が8になる。
同じUSBの descriptor なのに、合うものと合わないものが混ざる。
だからポインタを進める基準は C の都合ではなく wire 上の bLength。
-->

---

<div class="k">LIVE</div>

<h1 class="compact">C が、ブラウザで 18 バイトを読む</h1>

<UsbDescriptorDemo />

<!--
想定: 165秒
役割: 18バイトをブラウザの linear memory に書き、C/WASM がそれを読む。
進行: (1) 解析成功で VID/PID (2) bLength 改竄で -2 (3) 8バイトで -1 (4) Big-endian で 0x6D04。
(4)が山場: 同じ18バイトなのに意味が変わる。LE を自分で書くか、CPU とコンパイラの都合に
任せるかが境界面。さっき出した「6D 04 は 0x046D」をここで回収する。
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

<div class="cols" style="grid-template-columns: 1.02fr 0.98fr">
<div>

<h2>AIに書かせる</h2>

<div class="life">
<div class="life-code">char *copy(const char *s) {</div>
<div class="life-span" style="grid-row: 2 / 5">buf</div>
<div class="life-code">  char buf[256];</div>
<div class="life-code">  strcpy(buf, s);</div>
<div class="life-code"><span class="sig">  return buf;</span></div>
<div class="life-code">}</div>
<div class="life-end">関数を出た時点で無効</div>

</div>

</div>
<div>

<h2>人間が見るべきもの</h2>

<div class="qs" style="row-gap: 20px; font-size: 19px">
<div>そのメモリはいつまで生きる？</div>
<div>境界チェックはある？</div>
<div>未定義動作は踏んでない？</div>
<div>ABI / FFI で壊れない？</div>
</div>

</div>
</div>

<p class="punch" style="margin-top: 44px; font-size: 25px">AIがコードを書くほど、「実際に何が起きるか」を読む力が効いてくる。</p>

<!--
想定: 75秒
役割: AI生成コードを題材に、Cの実体を読む視点がレビューや境界設計で生きるとタイトルを回収する。
-->

---
class: mid
---

# 次に、この条件を見たら C を思い出す

<div class="k" style="padding-top: 0.5em">if</div>

<div class="stanza">
<div>デバイス / OS とつながる</div>
<div>言語をまたぐ共通コアを置く</div>
<div>ランタイムを薄くして小さく動かす</div>
<div>既存の C 資産を Web へ運ぶ</div>
</div>

<div class="k" style="padding-top: 72px">else</div>

<p class="lede branch">このどれにも当てはまらないなら、<br>C を選ばなくてよい。</p>

<!--
想定: 45秒
役割: 「Cは万能ではない」を保ったまま、次の技術選定で思い出すトリガーを4つに絞って渡す。
最後の1行で、Cを常に選ぶべきという主張にならないよう明示的に逆側を置く。

想定質問「それ Rust でよくないですか」への20秒回答:
多くの場合 Rust はよい答え。ただし既存の C ABI・既存資産・ツールチェーンが C しかない環境では
C が現実解になる。そこを「古いから」で塗りつぶさないでほしい、というのが今日の主張。
-->

---
class: bleed spread
---

<div>

<h1 class="say">技術選定で、<br>最初からCを候補外にしないでほしい</h1>

<p class="lede" style="margin-top: 26px">USB の 18 バイトから、ブラウザの WASM まで。<br><span class="dim">境界が重要な場面では、C にも席がある。</span></p>

<p class="note" style="margin-top: 26px; font-size: 17px">Thank you!</p>

</div>

<div>

<div class="bytes small">
<span class="off">12</span>
<span class="off">01</span>
<span class="off">00</span>
<span class="off">02</span>
<span class="off">00</span>
<span class="off">00</span>
<span class="off">00</span>
<span class="off">08</span>
<span class="wide">6D</span>
<span class="wide">04</span>
<span class="wide">2B</span>
<span class="wide">C5</span>
<span class="off">00</span>
<span class="off">12</span>
<span class="off">01</span>
<span class="off">02</span>
<span class="off">00</span>
<span class="off">01</span>
</div>

<div class="ruler ">
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class="twide"></span>
<span class="twide"></span>
<span class="twide"></span>
<span class="twide"></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
<span class=""></span>
</div>

<p class="note mono" style="margin-top: 20px">https://otonasi-muonn.github.io/c-lang-lt-slidev/</p>

</div>

<!--
想定: 30秒
役割: USBからC、WASM、技術選定までの一本線を最後のメッセージとして閉じる。
-->

---
class: mid
---

<div class="k">§6.3.1.8</div>

<h1 class="compact">Appendix: 型は、ただの名前じゃない</h1>

<BitWidthDemo />

<!--
想定: 本編時間外
役割: signed / unsigned の変換規則を、質問があった場合に補足する。
-->

---
class: bleed mid
---

<h1 class="say">Cは「C++から機能を減らした言語」<br>ではない。</h1>

<p class="lede">CにはCの都合、Cの設計、Cの進化がある。</p>

<p class="punch mono" style="margin-top: 40px"><span class="faint">C99 </span>restrict<span class="faint">　　C11 </span>_Generic<span class="faint">　　C99 </span>designated initializer</p>

<!--
想定: 本編時間外
役割: CとC++の関係について質問があった場合の補足に限定する。
-->
