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
duration: 15min
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

<p class="lede">普段のハッカソンなら、僕もまずTypeScript。</p>

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
1枚の move: いつもの技術選定から、Cへの好奇心を開く。

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
<div class="road-w">見える</div><div class="road-x"><span class="wide">6D 04</span> → 0x046D</div>
<div class="road-w">持っていける</div><div class="road-x">.c → .wasm → browser</div>
<div class="road-w">つながる</div><div class="road-x">your code → binding → C</div>
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

# コンピュータは、こんなbytesをやり取りする

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

<p class="lede" style="margin-top: 30px">USB Device Descriptor <span class="dim">— 18 bytes の返事</span></p>

<p class="note" style="margin-top: 18px">実機の生ダンプではなく、実在する VID / PID で組んだ説明用の例。</p>

<!--
想定: 45秒
1枚の move: 「バイト列って概念の話でしょ」→「実際にこれが飛んでいる」

口頭:
USBを接続したあとのやり取りで、PCはデバイスの情報を取得します。
自己紹介のような18バイトの返事。正式には Device Descriptor と言います。
画面の列は実機から採取したダンプではなく、実在するIDで組んだ説明用の例です。
文字としては2桁ずつですが、一組で1バイト。こういう形で意味を渡している。

USB のプロトコルの説明はここでしない。取得手順は Appendix。
今日 USB は主役ではなく、「本物のバイト列」を見せるためのケーススタディ。
-->

---
class: bleed mid
---

# たった2 bytes、何が分かる？

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
<div class="zoom-val wide">6D 04</div>
<div class="zoom-name">メーカーを表す欄 · offset 8–9</div>
</div>

<!--
想定: 30秒
1枚の move: 「18個ぜんぶ？」→「2個だけでいい」

口頭:
全部を読まなくて大丈夫です。今日はメーカーを表す2バイトだけ。
先頭を0として offset 8 と9、名前は idVendor です。
この2つの数字から、知っている名前が出てきます。

ここで答えを言わない。次の1枚で開く。
14個の全一覧は Appendix。
-->

---
class: bleed mid
clicks: 1
---

<div class="decode">
<div class="decode-input"><span>6D</span><span>04</span><small>下位 byte</small><small>上位 byte</small></div>
<svg class="decode-cross" width="260" height="44" viewBox="0 0 260 44" fill="none" aria-hidden="true"><path d="M55 2 L205 42 M205 2 L55 42" stroke="#58c4f0" stroke-width="2"/></svg>
<div class="decode-value">0x046D</div>
<div class="decode-caption">下位 byte から並ぶ — little-endian</div>
<div class="decode-payoff" v-click="1"><span>↓</span><strong>Logitech</strong></div>
</div>

<!--
想定: 60秒
1枚の move: 「6D 04 という2バイト」→「0x046D」→「Logitech」

口頭:
素直に読むと 0x6D04 に見える。でも違う。
このフィールドは下位バイトから並ぶので、6D が下の桁、04 が上の桁。値は 0x046D。
バッファを書き換える図ではなく、同じ2バイトを数値として読む図です。
[click] この番号は Logitech の vendor ID。
── 意味のない数字に見えたバイト列から、メーカー名が出てきた。

見出しを置いていない。絵そのものが主役。
解読は最初から見せ、メーカー名だけ1クリックで明かす。
出典: https://raw.githubusercontent.com/torvalds/linux/master/drivers/hid/hid-ids.h

聞かれたら: 同じ2バイトを big-endian として解釈すると 0x6D04。デモの追加操作で確認できる。
なお WASM 自体は little-endian。あのボタンは「別の解釈で読んだら」の実演であって、
WASM が big-endian という意味ではない。
-->

---
class: bleed mid
---

# これだけなら、TypeScriptの方が楽

<div class="vs" style="margin-top: 24px">
<div>
<div class="vs-k">TypeScript / JavaScript</div>
<pre class="vs-code"><code>view.getUint16(<span class="wide">8</span>, <span class="sig">true</span>)</code></pre>
<div class="vs-hint">「little-endianで読む」を指定</div>
</div>
<div>
<div class="vs-k">C</div>
<pre class="vs-code"><code>(uint16_t)p[<span class="wide">8</span>]
  | ((uint16_t)p[<span class="wide">9</span>] <span class="sig">&lt;&lt; 8</span>)</code></pre>
<div class="vs-hint">2 bytes の組み立てが見える</div>
</div>
<div class="vs-same"><span class="lab">同じ入力 → どちらも</span><span class="val">0x046D</span></div>
</div>

<p class="punch" style="margin-top: 28px">できることは同じ。見える抽象度が違う。</p>

<!--
想定: 75秒
1枚の move: 「Cにしかできない」→「できることは同じ。見えるものが違う」

口頭:
TypeScript / JavaScript の DataView には getUint16 があって、
第2引数の true が「リトルエンディアンで読む」。これだけなら TS の方が楽です。
Cだと、2バイトをどう1つの値に組み立てるかが自分のコードに出てくる。
どっちが優れているという話ではなくて、抽象度が違う、見えるものが違う。

絶対に言わないこと:
- 「TypeScript ではできない」 ── できます。画面にも「どちらも 0x046D」と出している。
- 速度の比較 ── 今日の主題ではない。

C側のキャストは 16-bit int 環境での符号付きシフトを避けるためのもので、
これも「見える」の一部。聞かれたら説明する。
前提: p は uint8_t*。view と p は同じ18バイトの先頭を指し、読み取り範囲は検証済み。
TSでもビット演算は書けるし、Cでも関数やライブラリに隠せる。言語固有の能力差ではない。
このCの式はデモの le16(&g_buf[8]) と同じ組み立て。raw struct cast はしていない。
DataView仕様: https://tc39.es/ecma262/multipage/structured-data.html#sec-dataview.prototype.getuint16
-->

---
class: bleed mid
---

# 同じデータでも、並びは同じとは限らない

<div class="pad" style="margin-top: 22px">

<div class="pad-k">wire</div>
<div class="cellrow big"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div>
<div class="pad-n">7 <small>bytes</small></div>

<div class="pad-k" v-click="1">C memory</div>
<div class="cellrow big" v-click="1"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad" aria-label="padding">＋</span></div>
<div class="pad-n sig" v-click="1">8 <small>bytes</small></div>

</div>

<p class="punch" v-click="1" style="margin-top: 32px">機械側の都合で、隙間が入る。</p>
<p class="note" style="margin-top: 18px">USB Endpoint Descriptor と、対応する構造体の例。サイズ・padding は ABI に依存。</p>

<!--
想定: 65秒
1枚の move: 「データの長さは1つ」→「線の上とメモリ上で違うことがある」

口頭:
これは7バイトのブロック。同じフィールドをCの構造体に置くと、このABIでは8バイトになります。
荷物そのものは7個でも、棚に置くと棚側の都合で隙間が1つできる。padding と言います。
普段は意識せずに済むことが、Cでは表に出てきやすい。欠点でもあるけど、
「機械が実際に何をしているか」が見えるということでもある。

padding の講義にしない。伝えるのは「線の上とメモリ上は同じとは限らない」の1つだけ。
限界: padding は必ず末尾でも必ず1バイトでもない。ABI 依存。
正式名称は Endpoint Descriptor。4種類の比較と C 規格の但し書きは Appendix。
次のブロックへ進む基準は線の上の長さ。ただし信頼できない入力ではその長さ自体も検証する。
-->

---
class: bleed mid
---

# 近いということは、危険も近い

<div class="lifetime">
<pre class="lifetime-code"><code><span class="dim">char *</span>message(void) {
  char buf[] = <span class="wide">"C"</span>;
  <span class="err">return buf;</span>
}</code></pre>
<div class="lifetime-flow">
<div><span class="life-label">関数の中</span><span class="life-memory">buf <b>C</b><b>\0</b></span></div>
<div class="life-exit">↓ 関数を終了</div>
<div><span class="life-label err">buf の寿命が終了</span><span class="life-memory expired">buf <b>C</b><b>\0</b></span></div>
<div class="life-pointer">戻したポインタ <span class="err">→ 有効な参照先がない</span></div>
</div>
</div>

<p class="punch" style="margin-top: 30px">AIがコードを書いても、<br>メモリ・寿命・境界の意味は残る。</p>

<!--
想定: 90秒
1枚の move: 「関数が値を返した」→「返ってきたのは、もう終わった場所の住所」

口頭:
buf は関数の中だけの入れ物。関数を出ると、その範囲は終わる。
なのに return しているのは、その入れ物の住所だけ。
ホテルの部屋番号を返しても、チェックアウト後はその部屋を使えない、というイメージ。
これを lifetime、寿命と言います。

クイズにしない。最初から全部見せて、左の短いコードから右の時間の流れへ案内する。
strcpyを使わず、ここでは寿命という1つの問題だけを見せる。

AIの回収:
AIはCのコードを書けます。でもCが扱っているメモリ・寿命・境界の意味が
それで消えてなくなるわけではない。どの抽象度で問題を見るかは残る。
「AIがあるからCが不要」とも「AI時代だからCが最強」とも言わない。

analogy の限界: メモリが消去されるわけではない。オブジェクトの寿命が終わる。
返したポインタの値は不定になる (C11 6.2.4p2)。有効なアドレスが保証されるわけではない。
だから運悪く「動いてしまう」ことがあるのが厄介。
-->

---
class: bleed mid
---

<div class="chap">持っていける</div>

# その C を、別の場所へ持っていく

<div class="portability">
<div class="port-source">C source<small>同じ bytes の読み取り処理</small></div>
<div class="port-native"><span>↳</span> native<small>別ターゲットへコンパイル</small></div>
<div class="port-browser"><span>↓</span><strong>WebAssembly</strong><span>↓</span><strong>Browser</strong></div>
</div>

<p class="punch" style="margin-top: 24px">小さな処理を、別の実行環境へ。</p>

<!--
想定: 55秒
1枚の move: 「Cはネイティブの言語」→「同じコードを別の実行環境へ運べる」

口頭:
さっきの2バイトを組み立てる処理を含む、小さなCのパーサーがあります。
Cソースはターゲットを変えてコンパイルできます。今回はWebAssemblyへ。
そのモジュールをJavaScriptから読み込んで、ブラウザで動かします。
どんなCプログラムでもそのまま運べる、という意味ではありません。
OSやデバイスに依存する部分と、小さな処理のコアを分けるのがポイントです。

WASM の内部の講義にしない。3ステップだけ。
ビルドは -nostdlib -ffreestanding。標準ライブラリもWASIも使っていない。
native は移植先の概念例。配布中のポインタexportはwasm32向けで、nativeでの実行を示した図ではない。
実際の対象: wasm/usb_descriptor.c の le16 / parse_device_descriptor。
-->

---
class: bleed demo-slide
---

<div class="chap">持っていける · live demo</div>
<h1 class="compact">さっきのC処理を、ブラウザで動かす</h1>

<UsbDescriptorDemo />

<!--
想定: 130秒（正常系を主役に。追加操作は最大1つまで）
1枚の move: 「WASMにした、という話」→「いま目の前で動いている」

進行:
(1) 「正常に解析」だけ押す。さっき手で読んだ 0x046D が、Cから返ってくる。
    最初の理解はこれだけでいい。ここで一度止まる。
(2) 時間があれば遊ぶ: bLength を 0x14 に → -2 でCが止める。
(3) 8バイトしか渡さない → -1。
(4) Big-endian として読む → 0x6D04。同じ18バイトでも読み方で別物になる。
    これは「別の解釈で読んだら」の実演。WASM 自体は little-endian。

アドレスと全フィールドは「メモリと全フィールド」を開いたときだけ見える。
通常の進行では開かない。追加操作も時間が余った場合だけ。

import object は空。生成されたJSランタイムやWASIへの依存はなく、手書きJSが入出力を橋渡しする。
失敗時は自動でJSフォールバックに落ち、バッジが「JS フォールバック」に変わる。
その場合は「今日はJSの同じ処理を表示しています」と明言し、Cが動いたとは説明しない。
読み込み中の早押しはJSで実行。ロード完了後もその結果表示はJSのまま、次のrunからWASMへ戻る。
-->

---
class: bleed mid
---

<div class="chap">つながる</div>

# Cは「他の言語から使われる側」にもいる

<div class="stack" style="margin-top: 22px">

<div class="stack-row"><span>TS / JS<small>Node.js など</small></span><span>Python</span><span>Rust</span></div>
<div class="stack-how">↓　FFI / binding / runtime　↓</div>
<div class="stack-abi">C ABI</div>
<div class="stack-how">↓</div>
<div class="stack-row lib"><span>SQLite<small>データベース</small></span><span>zlib<small>圧縮</small></span></div>

</div>

<p class="punch" style="margin-top: 28px">Cを書くことだけが、Cとの接点ではない。</p>

<!--
想定: 90秒
1枚の move: 「Cは書く人の話」→「他の言語から、既存のC資産を使う接点」

口頭:
例えばSQLiteのデータベースエンジン、zlibの圧縮ライブラリはCで書かれています。
Pythonのsqlite3やzlibなど、普段の言語のAPIを通して既存のC資産を使うことがある。
その間をつなぐのがバインディングやランタイム。呼び出しの約束がC ABIです。
TypeScriptはJavaScriptとして実行され、Node.jsのネイティブモジュールなどを経由する場合があります。
普通のブラウザJSから、任意のnative libraryを直接呼べるという図ではありません。
型の幅、メモリの持ち主、寿命は、その境界で処理が必要。多くはbindingが面倒を見てくれる。
ここは「USBが読める」とは別の理由。Cを書かなくても、その資産とつながれる。

正確性: 言語が常に直接C ABIを叩くわけではない。画面にも中間層を明示している。
ABIはOS・CPU・toolchainごとに異なる。世界共通の単一ABIではない。
例は2つに限定し、FFmpegという別の領域は増やさない。
出典: https://www.sqlite.org/about.html / https://www.sqlite.org/cintro.html
https://zlib.net/zlib_how.html / https://docs.python.org/3/library/ctypes.html
https://nodejs.org/api/n-api.html
-->

---
class: bleed mid
---

# だから、こういう時にCを思い出す

<div class="recall">
<div class="recall-w">見える</div><div class="recall-s">機械に近づきたい<small>OS / device / protocol</small></div>
<div class="recall-w">持っていける</div><div class="recall-s">小さいコアを、別の環境へ<small>native / WASM / 制約のある実行環境</small></div>
<div class="recall-w">つながる</div><div class="recall-s">既存のC資産を使いたい<small>library / ABI / SDK</small></div>
</div>

<p class="lede" style="margin-top: 22px">普段はTypeScriptでいい。条件が変わったら、選び直す。</p>

<!--
想定: 75秒
1枚の move: 「面白いのは分かった」→「で、自分はいつ思い出せばいいのか」

左の3語は冒頭のロードマップと同じ。ここで回収する。

口頭:
何でもCでやれとは言いません。逆です。
このどれにも当てはまらないなら、ふつうに他の選択肢でいい。
でも当てはまるときに、「古いから」で最初に消さないでほしい。
当てはまっても自動的にC、ではない。Rustなども含めて要件・安全性・既存資産で比較する。

想定質問「それ Rust でよくないですか」への20秒回答:
多くの場合 Rust はよい答え。ただし既存の C ABI・既存資産・ツールチェーンが
C しかない環境では C が現実解になる。そこを「古いから」で塗りつぶさないでほしい、
というのが今日の主張。
-->

---
class: bleed spread
---

<div>

<h1 class="say closing-title">技術選定で、<br>最初からCを<br>候補外にしないでほしい</h1>

<div class="three" style="margin-top: 28px"><span>見える</span><span>持っていける</span><span>つながる</span></div>

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
<span class="off">2B</span>
<span class="off">C5</span>
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
<span></span>
<span></span>
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

冒頭と同じ18バイト。今度は offset 8–9 だけに色がついている。
「見える・持っていける・つながる」を一呼吸ずつ回収。
AIによってコードを書くコストは変わっても、どの抽象度で見るか、
どのruntime / ABI / libraryへ接続するかという技術選定は残る。
だから、必要なときはCも選択肢へ戻してほしい。ありがとうございました。
本編の想定は13分30秒。残り1分30秒は操作・間・時間調整用。Appendixは含めない。
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

<p class="note" style="margin-top: 14px; max-width: none">フィールドの対応表。受信 bytes を <code>struct *</code> にキャストする実装例ではない。</p>

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
