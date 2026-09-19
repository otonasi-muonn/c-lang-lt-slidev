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
1枚の move: なし。18バイトを黙って置いておくだけ。

名乗り。そのあと、消したスライドのぶんをここで口頭で言う:
「Cは古いです。危ないです。書きやすくもない。常に最速でもない。
　それでも今日は、Cがまだ面白い場所の話をします。」

下のバイト列には触れない。「あとで回収します」も言わない。
気づく人だけ気づけばいい。
-->

---
class: bleed mid
---

<div class="who">PC</div>

<div class="ask">君は誰？</div>

<div v-click>

<div class="who" style="margin-top: 44px">USBデバイス</div>

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

<p class="lede" style="margin-top: 30px">ただの 18 バイト。<br><span class="dim">意味を与えるのは、次の一手。</span></p>

<p class="note" style="margin-top: 20px">実機の生ダンプではなく、実在する VID / PID で組んだ説明用の例。</p>

</div>

<!--
想定: 70秒
1枚の move: 「USBは電源と通信の線」→「挿した瞬間に会話が始まっていて、
最初の返事がこれ」

口頭:
USBを挿すと、PCは必ず最初に「お前は何者だ」と聞く。
デバイスは自己紹介を返す。その自己紹介がこれ。18バイト。多くも少なくもない。

analogy は「自己紹介」1つだけ。名刺・履歴書などへ広げない。
自由記述ではなく決まった様式の用紙である、という限界は次の1枚が即座に回収する。

「descriptor」「enumeration」という語はここでは出さない。
聞かれたら: この18バイトの正式名称は Device Descriptor。取得の手順全体は
enumeration と呼ばれ、Appendix にある。
-->

---
class: bleed mid
---

# この18個には、名前がついている

<div class="bytes hero" style="margin-top: 24px">
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

<div class="spans" v-click>
<i class="" style="grid-column: 1 / span 1"></i>
<i class="" style="grid-column: 2 / span 1"></i>
<i class="" style="grid-column: 3 / span 2"></i>
<i class="" style="grid-column: 5 / span 1"></i>
<i class="" style="grid-column: 6 / span 1"></i>
<i class="" style="grid-column: 7 / span 1"></i>
<i class="" style="grid-column: 8 / span 1"></i>
<i class="on" style="grid-column: 9 / span 2"></i>
<i class="" style="grid-column: 11 / span 2"></i>
<i class="" style="grid-column: 13 / span 2"></i>
<i class="" style="grid-column: 15 / span 1"></i>
<i class="" style="grid-column: 16 / span 1"></i>
<i class="" style="grid-column: 17 / span 1"></i>
<i class="" style="grid-column: 18 / span 1"></i>
</div>

<div class="span-labels" v-click>
<span style="grid-column: 9 / span 2">idVendor</span>
</div>

<p class="lede" style="margin-top: 40px">どこからどこまでが何か、長さも位置も決まっている。<br><span class="dim">今日は、この2バイトだけ見ます。</span></p>

<!--
想定: 80秒
1枚の move: 「意味不明な18個」→「区画に分かれていて、それぞれに名前がある」

口頭:
18バイトは、のっぺりした塊ではない。1バイトの欄が10個、2バイトの欄が4個。
どこが何かは規格で決まっている。全部で14個。
今日はそのうち1つ、8番目から2バイトの欄だけ見ます。

14個の全一覧は Appendix。ここでは出さない。
名前を読み上げない。1つに集中させる。
-->

---
class: bleed mid
---

<h1 class="compact" style="text-align: center; margin-bottom: 22px"><code>6D 04</code> は、いくつ？</h1>

<div class="swap" style="margin-top: 10px">

<div class="swap-k">wire に届いた順</div>
<div class="swap-row"><span>6D</span><span>04</span></div>

<div class="swap-cross" v-click><svg width="224" height="38" viewBox="0 0 224 38" fill="none" aria-hidden="true"><path d="M46 3 L178 35" stroke="#78818f" stroke-width="1.5"/><path d="M178 3 L46 35" stroke="#78818f" stroke-width="1.5"/></svg></div>

<div v-click>
<div class="swap-k" style="margin-top: 4px">先に届いた方が下の桁</div>
<div class="swap-row"><span>04</span><span>6D</span></div>
</div>

<div class="swap-val" v-click style="margin-top: 12px">0x046D</div>

<div class="swap-mean" v-click>Logitech</div>

</div>

<p class="note" v-click style="margin-top: 18px; text-align: center">見えている順と、値としての向きが違う。これを little-endian と呼ぶ。</p>

<!--
想定: 80秒
1枚の move: 「6D 04 という2バイト」→「0x046D という1つの値」→「Logitech」

口頭:
6D 04。素直に読むと 0x6D04 に見える。でも違う。
USBの線の上では、小さい桁から先に流れてくる。だから 6D が下の桁、04 が上の桁。
値は 0x046D。この番号は Logitech に割り当てられている。
── 今、18個の数字のうち2個から、メーカー名が出てきた。

この反転を自分のコードで書くか、CPUとコンパイラの都合に任せるか。
その選択があるのがCという言語。

analogy は使わない。入れ替わりの絵そのものが直感になっている。
little-endian という語は、絵を見せたあとに初めて出す。

聞かれたら: big-endian の機器でそのまま読むと 0x6D04 になる。
デモの4番目のボタンで実際にそうなる。
-->

---

# Cの構造体にすると、何バイト？

<h2>USB には他にも、決まった長さのブロックがある。これは 7 バイト。</h2>

<div class="pad" style="margin-top: 22px">

<div class="pad-k">wire</div>
<div class="cellrow big"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div>
<div class="pad-n">7</div>

<div class="pad-k" v-click="1">C の struct</div>
<div class="cellrow big" v-click="1"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div>
<div class="pad-n sig" v-click="1">8</div>

</div>

<p class="punch" v-click="1" style="margin-top: 34px">型の都合で、末尾に隙間が入る。<br><span class="dim">次のブロックの先頭は、<code>sizeof</code> では計算できない。</span></p>

<!--
想定: 70秒
1枚の move: 「wireの長さ = Cのstructの長さ」→「別物」

口頭:
USBには、さっきの18バイト以外にも決まった長さのブロックがある。たとえば7バイトのもの。
（正式名称は Endpoint Descriptor。画面には出していない。聞かれたら言う。）
これをCの構造体にすると、8バイトになる。
荷物そのものは7個でも、棚に置くと棚側の都合で隙間が1つできる。これを padding と言う。
だから「次のブロックはここから」を sizeof で計算すると1バイトずれて、以降が全部壊れる。
進む基準は、線の上に書いてある長さのほう。

analogy は「棚の隙間」1つだけ。
限界: padding は必ず末尾に入るわけでも、必ず1バイトでもない。ABI 依存。
Appendix に4種類の比較と、C規格はこの sizeof を保証しないという但し書きがある。

Appendix にある正確な規則: 線の上の長さ (bLength) を使う。ただし信頼できない
入力では bLength 自体も検証する (2 以上、残りバイト数以下)。
-->

---

<div class="k">LIVE</div>

<h1 class="compact">この C が、いまブラウザで動いている</h1>

<UsbDescriptorDemo />

<!--
想定: 165秒
1枚の move: 「Cって組み込みとかOSの言語でしょ」→「いまブラウザで動いてる」

進行:
(1) まず「正常に解析」だけ押す。18バイトを渡して、idVendor が 0x046D と出る。
    さっき手で読んだものを、Cが読んだ。これがこのデモの本体。
(2) そのあとで壊す: bLength を 0x14 に → -2。Cが戻り値で止める。
(3) 8バイトしか渡さない → -1。
(4) Big-endian として読む → 0x6D04。同じ18バイトなのに別のデバイスになる。
    さっきの「6D 04 は 0x046D」をここで回収する。

左の in / call / out はポインタ。最初は空で、押すと実アドレスが出る。
最初から読み上げない。(2) 以降で「Cが直接メモリを触っている」話をするときに指す。

import object は空。JSグルーもWASI依存もない。
失敗時: 自動でJSフォールバックに落ち、バッジが「JS フォールバック」に変わる。
そのまま進行してよい。表示と実際に動いているengineは必ず一致する。
-->

---

# AIはこれを1秒で書く。コンパイルも通る。

<div class="life" style="margin-top: 26px">
<div class="life-code">char *copy(const char *s) {</div>
<div class="life-span" style="grid-row: 2 / 5">buf</div>
<div class="life-code">  char buf[256];</div>
<div class="life-code">  strcpy(buf, s);</div>
<div class="life-code"><span class="sig">  return buf;</span></div>
<div class="life-code">}</div>
<div class="life-end" v-click="1">関数を出た時点で無効</div>
</div>

<p class="punch" v-click="1" style="margin-top: 40px">返しているのは、もう自分のものではないアドレス。<br><span class="dim">書くのがAIでも、何が起きるかを読むのは人間の仕事。</span></p>

<!--
想定: 75秒
1枚の move: 「コンパイルが通る = 正しい」→「通るのに、無効なメモリを返している」

口頭:
まずコードだけ見せて「どこが問題？」と一拍おく。それからクリック。
ホテルの部屋番号を教えてもらったようなもの。番号は正しい。
でも関数を出た瞬間にチェックアウト済みで、その部屋はもう自分のものではない。
これを lifetime、生存期間と言う。

AIはこのコードを1秒で書くし、コンパイルも通るし、動いてしまうこともある。
だから「コンパイルが通った」は正しさの証明にならない。
今日見てきたような、バイトの意味・長さ・境界を読む力が、そこで効く。

analogy は「チェックアウト」1つだけ。
限界: メモリが消去されるわけではない。使う権利がなくなるだけで、
だから運悪く「動いてしまう」ことがあるのが厄介、という方向で補足する。

言わなくてよい詳細: strcpy の境界チェックがないこと、ABI/FFI、未定義動作の定義。
聞かれたら答える。
-->

---

# こういう場面で、Cを思い出す

<div class="k" style="padding-top: 0.6em">if</div>

<div class="evid">
<div class="evid-row two"><div class="evid-claim">デバイス / OS とつながる</div><div class="evid-fact">18 bytes → 名前のついた値</div></div>
<div class="evid-row two"><div class="evid-claim">言語をまたぐ共通コアを置く</div><div class="evid-fact">JS → linear memory → C</div></div>
<div class="evid-row two"><div class="evid-claim">ランタイムを薄くして小さく動かす</div><div class="evid-fact">usb_descriptor.wasm = 769 B</div></div>
<div class="evid-row two"><div class="evid-claim">既存の C 資産を Web へ運ぶ</div><div class="evid-fact">usb_descriptor.c → .wasm</div></div>
</div>

<div class="k" style="padding-top: 54px">else</div>

<p class="lede branch">このどれにも当てはまらないなら、<br>C を選ばなくてよい。</p>

<!--
想定: 80秒
1枚の move: 「面白いのは分かった。で、いつ使うの？」→「この4つのどれかなら候補」

右の列は全部、今日この場で画面に出たもの。新しい主張は足していない。

口頭:
全部Cでやれとは言いません。逆です。
このどれにも当てはまらないなら、Cを選ばなくていい。
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

<p class="lede" style="margin-top: 26px">18 バイトの意味を読むところから、<br><span class="dim">ブラウザで動く WASM まで。</span></p>

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
想定: 35秒
1枚の move: 最初に置いた18バイトが、意味を持って戻ってくる。

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

18バイトを18バイトとして読む。末尾4バイトは飾りではない。
文字列は index で横に飛び、Configuration は複数持てる。

この構造体はフィールド一覧を説明するためのものであって、
受信バッファをこの型にキャストして読む実装例ではない。理由は次の Appendix。
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
同じUSBの descriptor なのに、合うものと合わないものが混ざる。

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
