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
想定: 35秒
1枚の move: なし。18バイトを黙って置いておくだけ。

口頭:
「普段ハッカソンで何か作るなら、僕もまず TypeScript を使います。
　今日は、それでも C が消えない理由を3つだけ見ていきます。」

ここで C を持ち上げない。TypeScript を貶さない。
下のバイト列には触れない。気づく人だけ気づけばいい。
-->

---
class: bleed mid
---

# Cの面白さは、この3つ

<div class="road" style="margin-top: 16px">
<div class="road-n">1</div><div class="road-w">見える</div><div class="road-x">12 01 00 02 …</div>
<div class="road-n">2</div><div class="road-w">持っていける</div><div class="road-x">.c → .wasm → browser</div>
<div class="road-n">3</div><div class="road-w">つながる</div><div class="road-x">TypeScript / Python → C</div>
</div>

<!--
想定: 30秒
1枚の move: 「Cって古い言語」→「今日追う軸は3つ」

これがこのLTの唯一のロードマップ。ここで説明しない。3つの語だけ置いて進む。
右の列は、それぞれの章で実際に画面に出るもの。先に見せておくと回収が効く。

最後のスライドでこの3語がもう一度出る。
-->

---
class: bleed mid
---

<div class="chap">見える</div>

# USBを挿すと、これが飛んでくる

<div class="bytes hero" style="margin-top: 26px">
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

<p class="lede" style="margin-top: 34px">PCが「君は誰？」と聞いたときの、デバイスからの返事。<br><span class="dim">18 バイト。今この瞬間も、PCの中で起きていること。</span></p>

<p class="note" style="margin-top: 18px">実機の生ダンプではなく、実在する VID / PID で組んだ説明用の例。</p>

<!--
想定: 45秒
1枚の move: 「バイト列って概念の話でしょ」→「実際にこれが飛んでいる」

口頭:
USBを挿すと、PCは必ず最初に「お前は何者だ」と聞く。その返事がこれ。18バイト。
正式には Device Descriptor と言います。

USB のプロトコルの説明はここでしない。取得手順は Appendix。
今日 USB は主役ではなく、「本物のバイト列」を見せるためのケーススタディ。
-->

---
class: bleed mid
---

# この18個のうち、2つだけ見ます

<div class="bytes hero" style="margin-top: 22px">
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
<span class="off">2B</span>
<span class="off">C5</span>
<span class="off">00</span>
<span class="off">12</span>
<span class="off">01</span>
<span class="off">02</span>
<span class="off">00</span>
<span class="off">01</span>
</div>

<div class="spans" style="margin-top: 8px">
<i class="on" style="grid-column: 9 / span 2"></i>
</div>

<div class="zoom">
<div class="zoom-val">6D 04</div>
<div class="zoom-name">idVendor</div>
</div>

<p class="lede" style="margin-top: 30px; text-align: center">この2バイトは、いくつでしょう？</p>

<!--
想定: 30秒
1枚の move: 「18個ぜんぶ？」→「2個だけでいい」

口頭:
18バイトは欄に分かれていて、どこが何かは決まっている。全部で14個の欄。
今日はそのうち1つ、8番目から2バイトの欄だけ。名前は idVendor。

ここで答えを言わない。次の1枚で開く。
14個の全一覧は Appendix。
-->

---
class: bleed mid
---

<div class="swap">

<div class="swap-k">wire に届いた順</div>
<div class="swap-row"><span>6D</span><span>04</span></div>

<div class="swap-cross" v-click><svg width="238" height="42" viewBox="0 0 238 42" fill="none" aria-hidden="true"><path d="M49 3 L189 39" stroke="#78818f" stroke-width="1.5"/><path d="M189 3 L49 39" stroke="#78818f" stroke-width="1.5"/></svg></div>

<div v-click>
<div class="swap-k" style="margin-top: 4px">先に届いた方が下の桁</div>
<div class="swap-row"><span>04</span><span>6D</span></div>
</div>

<div class="swap-val" v-click style="margin-top: 14px">0x046D</div>

<div class="swap-mean" v-click>Logitech</div>

</div>

<p class="note" v-click style="margin-top: 20px; text-align: center">見えている順と、値としての向きが違う。これを little-endian と呼ぶ。</p>

<!--
想定: 60秒
1枚の move: 「6D 04 という2バイト」→「0x046D」→「Logitech」

口頭:
素直に読むと 0x6D04 に見える。でも違う。
線の上では小さい桁から先に流れてくるので、6D が下の桁、04 が上の桁。値は 0x046D。
この番号は Logitech に割り当てられている。
── 意味のない数字に見えたバイト列から、メーカー名が出てきた。

見出しを置いていない。絵そのものが主役。
用語 (little-endian) は絵のあと、最後のクリックで出す。

聞かれたら: big-endian の機器でそのまま読むと 0x6D04。デモの4番目のボタンで再現できる。
なお WASM 自体は little-endian。あのボタンは「別の解釈で読んだら」の実演であって、
WASM が big-endian という意味ではない。
-->

---

# 同じ2バイトを、TypeScriptで読むと

<div class="vs" style="margin-top: 24px">

<div class="vs-k">TypeScript / JavaScript</div>
<div class="vs-k">C</div>

<div class="vs-code">view.getUint16(8, true)</div>
<div class="vs-code">(uint16_t)p[8] | ((uint16_t)p[9] &lt;&lt; 8)</div>

<div class="vs-same">
<span class="lab">どちらも</span>
<span class="val">0x046D</span>
</div>

</div>

<p class="punch" style="margin-top: 34px">これだけなら、TypeScript の方が楽。<br><span class="dim">でも C だと、2バイトがどう1つの値になるかがコードに出てくる。</span></p>

<!--
想定: 65秒
1枚の move: 「Cにしかできない」→「できることは同じ。見えるものが違う」

口頭:
同じことを TypeScript でやると1行で済みます。DataView に getUint16 があって、
第2引数の true が「リトルエンディアンで読む」。これだけなら TS の方が楽です。
Cだと、2バイトをどう1つの値に組み立てるかが自分のコードに出てくる。
どっちが優れているという話ではなくて、抽象度が違う、見えるものが違う。

絶対に言わないこと:
- 「TypeScript ではできない」 ── できます。画面にも「どちらも 0x046D」と出している。
- 速度の比較 ── 今日の主題ではない。

C側のキャストは 16-bit int 環境での符号付きシフトを避けるためのもので、
これも「見える」の一部。聞かれたら説明する。
-->

---

# Cのメモリに置くと、長さが変わることがある

<h2>USB の別のブロック。線の上では 7 バイト。</h2>

<div class="pad" style="margin-top: 22px">

<div class="pad-k">線の上</div>
<div class="cellrow big"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div>
<div class="pad-n">7</div>

<div class="pad-k" v-click="1">Cのメモリ</div>
<div class="cellrow big" v-click="1"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div>
<div class="pad-n sig" v-click="1">8</div>

</div>

<p class="punch" v-click="1" style="margin-top: 32px">線の上の並びと、メモリ上の並びは同じとは限らない。<br><span class="dim">こういう機械側の都合が、Cだと隠れない。</span></p>

<!--
想定: 55秒
1枚の move: 「データの長さは1つ」→「線の上とメモリ上で違うことがある」

口頭:
これは7バイトのブロック。Cの構造体にすると8バイトになります。
荷物そのものは7個でも、棚に置くと棚側の都合で隙間が1つできる。padding と言います。
便利な言語はこれを見せないでくれる。Cは見せてくる。欠点でもあるけど、
「機械が実際に何をしているか」が見えるということでもある。

padding の講義にしない。伝えるのは「線の上とメモリ上は同じとは限らない」の1つだけ。
限界: padding は必ず末尾でも必ず1バイトでもない。ABI 依存。
正式名称は Endpoint Descriptor。4種類の比較と C 規格の但し書きは Appendix。
次のブロックへ進む基準は線の上の長さ。ただし信頼できない入力ではその長さ自体も検証する。
-->

---

# 近いということは、危険も近い

<div class="life" style="margin-top: 24px">
<div class="life-code">char *copy(const char *s) {</div>
<div class="life-span" style="grid-row: 2 / 5">buf が<br>使える範囲</div>
<div class="life-code">  char buf[256];</div>
<div class="life-code">  strcpy(buf, s);</div>
<div class="life-code"><span class="sig">  return buf;</span></div>
<div class="life-code">}</div>
<div class="life-end">関数を出た時点で、この範囲は終わっている</div>
</div>

<p class="punch" style="margin-top: 36px">返ってくるのは、もう使えない場所を指すポインタ。<br><span class="dim">AIはCのコードを書ける。でもメモリと寿命の意味は消えない。</span></p>

<!--
想定: 75秒
1枚の move: 「関数が値を返した」→「返ってきたのは、もう終わった場所の住所」

口頭:
buf は関数の中だけの入れ物。関数を出ると、その範囲は終わる。
なのに return しているのは、その入れ物の住所だけ。
ホテルの部屋番号を教えてもらったようなもので、番号は正しいけどチェックアウト済み。
これを lifetime、寿命と言います。

クイズにしない。最初から全部見せて、絵で理解させる。

AIの回収:
AIはCのコードを書けます。でもCが扱っているメモリ・寿命・境界の意味が
それで消えてなくなるわけではない。どの抽象度で問題を見るかは残る。
「AIがあるからCが不要」とも「AI時代だからCが最強」とも言わない。

analogy の限界: メモリが消去されるわけではない。使う権利がなくなるだけ。
だから運悪く「動いてしまう」ことがあるのが厄介。
-->

---

<div class="chap">持っていける</div>

# その C を、別の場所へ持っていく

<div class="chain" style="margin-top: 26px">

<div class="chain-node">usb_descriptor.c</div>
<div class="chain-arrow">↓<span class="how">clang --target=wasm32</span></div>
<div class="chain-node">usb_descriptor.wasm<span class="sz">769 B</span></div>
<div class="chain-arrow">↓<span class="how">fetch + WebAssembly.instantiate</span></div>
<div class="chain-node">ブラウザ</div>

</div>

<p class="punch" style="margin-top: 32px">書き直さない。同じCのコードのまま運ぶ。</p>

<!--
想定: 35秒
1枚の move: 「Cはネイティブの言語」→「同じコードを別の実行環境へ運べる」

口頭:
さっきまで見ていたCのコードを、そのまま WebAssembly にコンパイルします。
769バイト。これをブラウザが読み込む。書き直しはしていません。

WASM の内部の講義にしない。3ステップだけ。
769 B は実測値 (public/wasm/usb_descriptor.wasm)。
ビルドは -nostdlib -ffreestanding。標準ライブラリもWASIも使っていない。
-->

---

<div class="k">LIVE</div>

<h1 class="compact">さっきの C が、いまブラウザで動いている</h1>

<UsbDescriptorDemo />

<!--
想定: 140秒
1枚の move: 「WASMにした、という話」→「いま目の前で動いている」

進行:
(1) 「正常に解析」だけ押す。さっき手で読んだ 0x046D が、Cから返ってくる。
    最初の理解はこれだけでいい。ここで一度止まる。
(2) 時間があれば遊ぶ: bLength を 0x14 に → -2 でCが止める。
(3) 8バイトしか渡さない → -1。
(4) Big-endian として読む → 0x6D04。同じ18バイトでも読み方で別物になる。
    これは「別の解釈で読んだら」の実演。WASM 自体は little-endian。

左の in / call / out はポインタ。最初は空。押して初めて出る。
最初から読み上げない。(2) 以降で「Cが直接メモリを触っている」話をするときに指す。

import object は空。JSグルーもWASI依存もない。
失敗時は自動でJSフォールバックに落ち、バッジが「JS フォールバック」に変わる。
そのまま進行してよい。表示と実際に動いているengineは必ず一致する。
-->

---

<div class="chap">つながる</div>

# Cは「他の言語から使われる側」にもいる

<div class="stack" style="margin-top: 22px">

<div class="stack-row"><span>TypeScript</span><span>Python</span><span>Rust</span></div>
<div class="stack-how">↓<br>FFI / バインディング / ネイティブモジュール</div>
<div class="stack-abi">C ABI</div>
<div class="stack-how">↓</div>
<div class="stack-row lib"><span>SQLite</span><span>zlib</span><span>FFmpeg</span></div>

</div>

<p class="punch" style="margin-top: 28px">Cを書かなくても、その下にCがいる。</p>

<!--
想定: 60秒
1枚の move: 「Cは書く人の話」→「使っている側にも必ずいる」

口頭:
SQLite も zlib も FFmpeg も、中身はCです。
TypeScript から使うときは、間にネイティブモジュールやバインディングが入る。
Python なら ctypes や C拡張。直接C ABIを呼んでいるわけではありません。
でも境界の向こう側はCで、そこの都合 ── 型の幅、メモリの持ち主、寿命 ──
は結局こちらまで効いてくる。

正確性: 言語が常に直接C ABIを叩くわけではない。画面にも中間層を明示している。
SQLite / zlib / FFmpeg はいずれもC実装。名前はこれ以上増やさない。
-->

---

# だから、こういう時にCを思い出す

<div class="k" style="padding-top: 0.6em">if</div>

<div class="recall">
<div class="recall-w">見える</div><div class="recall-s">機械に近づきたい</div><div class="recall-t">OS / device / protocol</div>
<div class="recall-w">持っていける</div><div class="recall-s">小さいコアを別の環境へ</div><div class="recall-t">native / WASM / 制約のある実行環境</div>
<div class="recall-w">つながる</div><div class="recall-s">既存のC資産を使いたい</div><div class="recall-t">library / ABI / SDK</div>
</div>

<div class="k" style="padding-top: 54px">else</div>

<p class="lede branch">当てはまらないなら、<br>TypeScript でも Rust でも、ふつうに他の選択肢でいい。</p>

<!--
想定: 60秒
1枚の move: 「面白いのは分かった」→「で、自分はいつ思い出せばいいのか」

左の3語は冒頭のロードマップと同じ。ここで回収する。

口頭:
何でもCでやれとは言いません。逆です。
このどれにも当てはまらないなら、ふつうに他の選択肢でいい。
でも当てはまるときに、「古いから」で最初に消さないでほしい。

想定質問「それ Rust でよくないですか」への20秒回答:
多くの場合 Rust はよい答え。ただし既存の C ABI・既存資産・ツールチェーンが
C しかない環境では C が現実解になる。そこを「古いから」で塗りつぶさないでほしい、
というのが今日の主張。
-->

---
class: bleed spread
---

<div>

<h1 class="say">技術選定で、<br>最初からCを候補外にしないでほしい</h1>

<div class="three" style="margin-top: 28px"><span>見える</span><span>持っていける</span><span>つながる</span></div>

<p class="note" style="margin-top: 24px; font-size: 17px">Thank you!</p>

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
想定: 35秒
1枚の move: 3つの軸と、最初に置いた18バイトが、意味を持って戻ってくる。

冒頭と同じ18バイト。今度は8〜11番目に色がついている。
そこだけ読めるようになった、という絵で閉じる。
-->

---

<div class="k">USB 2.0</div>

<h1 class="compact">Appendix: 18バイトを受け取るまでの全工程</h1>

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
本編時間外。「どうやって取るの？」と聞かれたときだけ開く。

左は起きた順、右は返ってきたデータの形。混ぜると GET_DESCRIPTOR が親に見えてしまう。
Configuration 以下は順番に別々に取るのではなく、長さを読んでから一つの連結ブロブとして取る。

先頭8バイトを読んでから再リセットする流れは代表的なホスト実装であって、
全ホストへ強制される手順ではない (USB 2.0 §9.1.2 は複数の初期化順を許す)。

聞かれたら: bNumInterfaces は interface 番号の数であって Interface Descriptor の
総数ではない。alternate setting の分だけ Interface Descriptor は増える。
-->

---

<h1 class="compact">Appendix: 18バイトの全フィールド</h1>

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
<div class="dline"><span class="dline-hex wide">6D 04</span><span class="dline-src">  uint16_t idVendor;</span><span class="dline-val wide">0x046D<span class="jp">　Logitech</span></span></div>
<div class="k cl">10</div>
<div class="dline"><span class="dline-hex wide">2B C5</span><span class="dline-src">  uint16_t idProduct;</span><span class="dline-val wide">0xC52B<span class="jp">　Unifying Receiver</span></span></div>
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
本編時間外。「残りの欄は何？」と聞かれたときだけ開く。

この構造体はフィールド一覧を説明するためのものであって、
受信バッファをこの型にキャストして読む実装例ではない。理由は次の Appendix。
デモの C も、この型にキャストせず1バイトずつ組み立てている。
-->

---

<div class="k">ABI</div>

<h1 class="compact">Appendix: wire の長さと <code>sizeof</code></h1>

<div class="abi" style="margin-top: 8px">
<div class="abi-name">Device</div><div class="abi-lab">wire</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">18</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">18</div><div class="abi-note ">たまたま一致</div>
<div class="abi-gap"></div>
<div class="abi-name">Configuration</div><div class="abi-lab">wire</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div><div class="abi-num">10</div><div class="abi-note sig">末尾 padding 1</div>
<div class="abi-gap"></div>
<div class="abi-name">Interface</div><div class="abi-lab">wire</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div class="abi-note ">たまたま一致</div>
<div class="abi-gap"></div>
<div class="abi-name">Endpoint</div><div class="abi-lab">wire</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">7</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div><div class="abi-num">8</div><div class="abi-note sig">末尾 padding 1</div>
</div>

<p class="punch" style="margin-top: 22px; font-size: 20px">進む基準は wire 上の長さ。<br><span class="dim">ただし信頼できない入力では、その長さ自体も検証する。</span></p>

<p class="note" style="margin-top: 14px">C 規格はこの <code>sizeof</code> を保証しない。典型 ABI の実演であって wire format の定義ではない。</p>

<!--
本編時間外。

Device で18と出るのは正解ではなく偶然。Endpoint は7が8になる。

「bLength を信じろ」は言い過ぎで、untrusted input では bLength 自体が攻撃者の
制御下にある。実際の走査ループは次のように両方を見る:

  while (remain >= 2) {
    uint8_t n = p[0];
    if (n < 2 || n > remain) break;   // ← bLength 自体の検証
    p += n; remain -= n;
  }

生バイト列を (Desc *) にキャストしない理由: エンディアン、アライメント、padding、
effective type。packed は非標準で、未アラインの member access 問題も残る。
byte から明示的に組み立てるか、同等に境界・endian・alignment を処理する実装を使う。
-->

---
class: mid
---

<div class="k">§6.3.1.8</div>

<h1 class="compact">Appendix: 型は、ただの名前じゃない</h1>

<BitWidthDemo />

<!--
本編時間外。signed / unsigned の変換規則を、質問があった場合に補足する。
-->

---
class: bleed mid
---

<h1 class="say">Cは「C++から機能を減らした言語」<br>ではない。</h1>

<p class="lede">CにはCの都合、Cの設計、Cの進化がある。</p>

<p class="punch mono" style="margin-top: 40px"><span class="faint">C99 </span>restrict<span class="faint">　　C11 </span>_Generic<span class="faint">　　C99 </span>designated initializer</p>

<!--
本編時間外。CとC++の関係について質問があった場合の補足に限定する。
-->
