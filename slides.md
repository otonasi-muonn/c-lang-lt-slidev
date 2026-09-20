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

<p class="lede">推し技術LT　—　無音 / ハックツ Committer</p>

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

<p class="note" style="margin-top: 22px">ハックツコミュ「自分の推し技術について語りたいよねの会」15min</p>

</div>

<!--
想定: 20秒
このframeで言いたいこと:
お前は誰ぞい、という自己紹介。ハックツのCommitterの無音です。
推し技術LTなので、自分の好きなCを題材に持ってきました。

次への橋: 「なぜ今さらC、という話をする前に、AIの話を先に置かせてください」

下のバイト列は今は触れない。最後にもう一度出てくる。
-->

---
class: bleed mid
clicks: 1
---

<h1 class="say">今は、知らない言語でも<br>AIに書いてもらえる時代になってきた</h1>

<div class="pivot" v-click="1">
<p class="pivot-line">だから面白いのは、<br><span class="sig">「何語を書けるか」より「何を選ぶか」</span>になった。</p>
<p class="note pivot-tag">— というのは、僕個人の感じ方です</p>
</div>

<!--
想定: 28秒
このframeで言いたいこと:
実装コストが下がったぶん、技術選定のほうが面白くなった、という発表者の立場。

次への橋: 「じゃあ選ぶ側として、Cって何なんだっけ、というところから」

caveat: これは外部の普遍的事実ではない。断言せず、自分の考えとして言う。
「AIがあるからCが有利」とは言わない。最後にもう一度回収する。
-->

---
class: bleed mid
clicks: 1
---

# そもそも、C言語とは

<div class="facts">
<div class="facts-k">成立</div><div class="facts-v">1969 – 1973<span class="facts-s">最も創造的だったのは1972年ごろ</span></div>
<div class="facts-k">作者</div><div class="facts-v">Dennis M. Ritchie<span class="facts-s">Bell Labs</span></div>
<div class="facts-k">用途</div><div class="facts-v">初期Unixのための <span class="wide">system implementation language</span><span class="facts-s">OSそのものを書くための言語として発展した</span></div>
</div>

<p class="punch" v-click="1">assemblyより書きやすく、<br>それでいて機械に近い操作も書ける。<span class="dim">そこが出発点。</span></p>

<!--
想定: 35秒
このframeで言いたいこと:
「古い」「危険」「組み込み」という評判から入らない。まずCが何のために作られたか。

次への橋: 「じゃあ比較対象として、現代側も一言だけ」

歴史講義にしない。3項目だけ読み上げて次へ。
出典: Dennis M. Ritchie, "The Development of the C Language" (HOPL-II, 1993)
  「The C programming language was devised in the early 1970s as a system
   implementation language for the nascent Unix operating system.」
  「C came into being in the years 1969-1973, in parallel with the early
   development of the Unix operating system」
聞かれたら: Cの前身はB、その前はBCPL。PDP-11への移行が型の導入を押した。
-->

---
class: bleed mid
---

# 今日の比較対象は、TypeScript

<div class="facts">
<div class="facts-k">何</div><div class="facts-v">JavaScriptを基盤に、型のための構文などを加えた言語</div>
<div class="facts-k">現在</div><div class="facts-v">2025年8月、GitHubの<span class="wide">月間contributor数で1位</span><span class="facts-s">Pythonを約42,000人上回った (GitHub Octoverse 2025)</span></div>
</div>

<p class="punch">Webアプリを作るなら、<br>僕も普通にTypeScriptを使います。</p>

<p class="note" style="margin-top: 16px">同じレポートで、AI関連リポジトリではPythonが引き続き優勢。</p>

<!--
想定: 30秒
このframeで言いたいこと:
TypeScriptを知らない人がいる前提で、一言だけ紹介する。
そして「ハッカソンのWeb開発で現代的な高水準言語を選ぶ例」として置く。

次への橋: 「その僕が、なんでCを推し技術に選んだのか」

C vs TS の宗教戦争にしない。速度比較もしない。
「自分もWebアプリならTSを使う」を必ず言う。ここで立場を明示しておくと最後が効く。
出典: GitHub Octoverse 2025 (2025-10-30公開)
-->

---
class: bleed mid
---

<h1 class="say">Cは、機械側の都合が<br>表面に出てきやすい</h1>

<div class="surface">
<span>値が何byteか</span>
<span>memory上でどう表現されるか</span>
<span>address</span>
<span>lifetime</span>
</div>

<p class="punch">普段はruntimeやlibraryが隠してくれるものが、<br>自分のコードの側に出てくる。<span class="dim">面倒だし、危険でもある。</span></p>

<!--
想定: 25秒
このframeで言いたいこと:
今日いちばん伝えたい魅力。ただしCを万能化しない。

次への橋: 「言葉だけだと分からないので、いちばん簡単なやつを実際に動かします」

絶対に言わないこと:
- 「Cコード = CPUが実際に行う処理そのもの」
- 「Cならコンピュータの全てが見える」
Cもabstract machineを持つ言語。正確には「低いレイヤーが表面に出てきやすい」。
「面倒・危険でもあるが、自分はそこにコンピュータを触っている感覚があって面白い」まで言う。
-->

---
class: bleed mid
clicks: 3
---

# まず、いちばん簡単なCで

<div class="obs">

<pre class="obs-code"><code><span class="dim">uint32_t</span> x = <span class="wide">0x12345678</span>;</code></pre>

<pre class="obs-code obs-dim" v-click="1"><code><span class="dim">unsigned char</span> *p = (<span class="dim">unsigned char</span> *)&amp;x;
printf(<span class="str">"%02X %02X %02X %02X\n"</span>, p[0], p[1], p[2], p[3]);</code></pre>

<div class="obs-out" v-click="2">
<div class="obs-prompt">$ gcc endian.c &amp;&amp; ./a.out</div>
<div class="bytes four"><span class="sig">78</span><span class="sig">56</span><span class="sig">34</span><span class="sig">12</span></div>
</div>

<div class="obs-name" v-click="3">下位のbyteから並んだ　<strong class="wide">little-endian</strong></div>

<p class="note obs-env" v-click="2">gcc 13.3.0 / x86_64-linux-gnu で実行。C言語がこの並び順を決めているのではない。</p>

</div>

<!--
想定: 55秒
このframeで言いたいこと:
値そのものと、memory上の表現は別だ、ということ。
0x12345678 は「どの言語でも同じ値」。並び方は環境が決めている。

進行:
(1) 値だけ見せる。ここまでは何も不思議じゃない。
(2) 1byteずつ覗くコードを足す。「じゃあ、memoryの上ではどう並んでる？」
(3) 実際の出力。逆から出てくる。ここで一度止まる。
(4) 名前を付ける: little-endian

次への橋: 「これ、実は本物のプロトコルにもそのまま出てきます」

caveat (重要):
- 「C言語が little-endian を決めている」とは言わない。処理系・環境依存。
- unsigned char 経由で object representation を覗くのは規格上認められた読み方。
- big-endian の環境なら 12 34 56 78 になる。
-->

---
class: bleed mid
clicks: 2
---

# さっきのが、そのまま出てくる例

<div class="bytes hero" :class="{ narrowed: $clicks > 0 }" style="margin-top: 20px">
<span>12</span>
<span>01</span>
<span>00</span>
<span>02</span>
<span>00</span>
<span>00</span>
<span>00</span>
<span>08</span>
<span class="pick">6D</span>
<span class="pick">04</span>
<span>2B</span>
<span>C5</span>
<span>00</span>
<span>12</span>
<span>01</span>
<span>02</span>
<span>00</span>
<span>01</span>
</div>

<div class="spans" style="margin-top: 6px">
<i class="on" style="grid-column: 9 / span 2" v-click="1"></i>
</div>

<p class="lede" style="margin-top: 14px">USB Device Descriptor <span class="dim">— デバイスが返す18 bytesの自己紹介</span></p>

<div class="lift" v-click="1">
<div class="lift-k">offset 8–9　メーカーを表す欄</div>
<div class="lift-chain">
<span class="lift-raw">6D 04</span>
<svg class="lift-x" width="54" height="26" viewBox="0 0 54 26" fill="none" aria-hidden="true"><path d="M6 3 L48 23 M48 3 L6 23" stroke="#58c4f0" stroke-width="1.6"/></svg>
<span class="lift-val wide">0x046D</span>
<span class="lift-arrow" v-click="2">→</span>
<strong class="lift-name" v-click="2">Logitech</strong>
</div>
</div>

<p class="note" style="margin-top: 20px">実機のダンプではなく、Device Descriptorの形式に沿って実在するVID / PIDで構成した例。</p>

<!--
想定: 48秒
このframeで言いたいこと:
USBを教えるのではない。「さっき覚えたことだけで、本物の仕様に沿ったbyte列が読めた」という成功体験。

進行:
(1) 18バイトを出す。USBを挿したときにデバイスが返す自己紹介です、とだけ。
(2) 2バイトだけに絞る。offset 8-9。
(3) さっきの little-endian を当てる → 0x046D → Logitech

次への橋: 「で、これ TypeScript でもできます」

禁止:
- enumeration の説明
- descriptor hierarchy の説明
- 14フィールドの一覧
どれも Appendix にある。聞かれたときだけ開く。
画面のbyte列は実機dumpではない。誤って「実機から取得したデータ」と言わない。
出典: torvalds/linux drivers/hid/hid-ids.h (USB_VENDOR_ID_LOGITECH 0x046d)
-->

---
class: bleed mid
---

# これだけなら、TypeScriptの方が楽

<div class="vs" style="margin-top: 24px">
<div>
<div class="vs-k">TypeScript / JavaScript</div>
<pre class="vs-code"><code>view.getUint16(<span class="wide">8</span>, <span class="sig">true</span>)</code></pre>
<div class="vs-hint">「little-endianで読む」を指定するだけ</div>
</div>
<div>
<div class="vs-k">C</div>
<pre class="vs-code"><code>(uint16_t)p[<span class="wide">8</span>]
  | ((uint16_t)p[<span class="wide">9</span>] <span class="sig">&lt;&lt; 8</span>)</code></pre>
<div class="vs-hint">2 bytesの組み立てが自分のコードに出る</div>
</div>
<div class="vs-same"><span class="lab">同じ入力 → どちらも</span><span class="val">0x046D</span></div>
</div>

<p class="punch" style="margin-top: 26px">能力の差ではなく、<br>自分が触っている抽象度の差。</p>

<!--
想定: 32秒
このframeで言いたいこと:
Cにしかできない、とは言わない。むしろ「これだけならTSの方が楽」と自分から言う。

次への橋: 「じゃあ近いと何が嬉しいのか。その前に、近いことの代償を先に」

絶対に言わないこと:
- 「TypeScriptではbytesを扱えない」── 扱える。画面にも「どちらも0x046D」と出す。
- 速度の比較。今日の主題ではない。
TSでもビット演算は書けるし、Cでもhelperに隠せる。言語固有の能力差ではない。
Cのキャストは16-bit int環境での符号付きシフトを避けるため。聞かれたら説明。
前提: p は uint8_t*。view と p は同じ18バイトの先頭を指す。
-->

---
class: bleed mid
clicks: 1
---

# 近いと、こういうものも見えてしまう

<div class="pad" style="margin-top: 20px">

<div class="pad-k">wire</div>
<div class="cellrow big"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div>
<div class="pad-n">7 <small>bytes</small></div>

<div class="pad-k" v-click="1">C object</div>
<div class="cellrow big" v-click="1"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad" aria-label="padding">＋</span></div>
<div class="pad-n sig" v-click="1">8 <small>bytes</small></div>

</div>

<div class="evidence" v-click="1">
<div class="evidence-out"><span>wire   : 7</span><span>sizeof : 8</span></div>
<div class="evidence-src">USB Endpoint Descriptorと、対応する構造体。gcc 13.3.0 / x86_64-linux-gnu。<br>サイズもpaddingもABI依存で、いつも8になるわけではない。</div>
</div>

<p class="punch" v-click="1" style="margin-top: 22px">線の上の長さと、memory上の大きさは<br>同じとは限らない。</p>

<!--
想定: 32秒
このframeで言いたいこと:
「線の上とmemory上は同じとは限らない」。それ一つだけ。

次への橋: 「もう一つ、もっと危ないほうも見せます」

caveat (重要):
- 「Cでは必ずpaddingが入る」とは言わない。「必ず8になる」とも言わない。
- サイズもalignmentもABI依存。これは特定のABIでの実演。
padding の講義にしない。4種類の比較は Appendix。
-->

---
class: bleed mid
clicks: 1
---

# 関数を出たあとの、この住所は

<div class="lifetime">
<pre class="lifetime-code"><code><span class="dim">char *</span>message(void) {
  char buf[] = <span class="wide">"C"</span>;
  <span class="err">return buf;</span>
}</code></pre>
<div class="lifetime-flow">
<div><span class="life-label">関数の中</span><span class="life-memory">buf <b>C</b><b>\0</b></span></div>
<div class="life-exit">↓ 関数を終了</div>
<div><span class="life-label err">buf の寿命が終了</span><span class="life-memory expired">buf <b>C</b><b>\0</b></span></div>
<div class="life-pointer">返したポインタで、<span class="err">その buf はもう参照できない</span></div>
</div>
</div>

<div class="evidence">
<div class="evidence-out">warning: function returns address of local variable [-Wreturn-local-addr]</div>
</div>

<p class="punch" v-click="1" style="margin-top: 20px">AIがCを書けるようになっても、<br>memory・lifetime・境界の意味は消えない。</p>

<!--
想定: 50秒
このframeで言いたいこと:
クイズにしない。最初から全部見せて、時間の流れとして案内する。
buf は関数の中だけの入れ物。出た瞬間にその範囲は終わる。なのに返しているのは住所だけ。

進行:
(1) 左のコード → 右の時間の流れを順に指す
(2) この例はコンパイラが警告してくれる。でも警告が出ない形はいくらでもある。
(3) [click] AIの中盤回収

次への橋: 「これ、現実にどのくらい起きているのか」

caveat (重要):
- memory が消去されるわけではない。objectの寿命が終わる。
- 参照先objectのlifetime終了に伴い、そのobjectを指していたpointer value自体も
  indeterminate になる (C11 6.2.4p2)。だから運悪く「動いてしまう」ことがある。
AI回収では「AIがあるからC不要」とも「AI時代だからCが最強」とも言わない。
消えないのは memory / lifetime / ownership / ABI / byte representation / protocol rules。
-->

---
class: bleed mid
---

# 実際、ここが現代いちばんの弱点

<div class="risk">
<div class="risk-big"><span class="err">約70%</span></div>
<div>
<div class="risk-txt">Chromeの高深刻度セキュリティバグのうち、<br>C/C++のmemory unsafetyが原因のもの。</div>
<div class="risk-note">その半分が use-after-free<span>さっき見た、あの寿命の話</span></div>
</div>
</div>

<div class="risk-2">
CISAなども、memory-safe languagesへの移行ロードマップを公開するよう推奨している。
</div>

<p class="punch">だから「これからは何でもCで書こう」<br>とは、言いません。</p>

<!--
想定: 38秒
このframeで言いたいこと:
Cのmemory unsafetyを「難しいけど楽しい」で終わらせない。重大なリスクとして正面から置く。
さっきの lifetime が、そのまま use-after-free の話につながっている。

次への橋: 「じゃあ今日は何を主張したいのか。問いを変えます」

caveat:
- Rust等のmemory-safe systems languageが適切な場面は当然ある。ここで否定しない。
- 「Cは危険だから使うな」でもない。ゴールはCの万能化ではなく「条件が揃えば候補」。
出典: chromium.org/Home/chromium-security/memory-safety/
  「Around 70% of our high severity security bugs are memory unsafety problems」
  CISA/NSA他 "The Case for Memory Safe Roadmaps" (2023-12)
-->

---
class: bleed mid
---

<h1 class="say">じゃあ、普段TypeScriptやPythonを<br>使っている自分が、<br>どんな時にCを思い出すのか</h1>

<p class="lede">ここまでは「Cって面白いね」の話。<br>ここからが今日の本題です。</p>

<!--
想定: 20秒
このframeで言いたいこと:
問いを切り替える。「面白い」で終わらせない、という宣言。

次への橋: 「その前に、たぶん一番誤解されているところを先に潰します」

ここで間を取る。ここが折り返し地点。
-->

---
class: bleed mid
clicks: 2
---

# Cを使う ＝ 全部Cで書く、ではない

<div class="paths">

<div class="paths-n">1</div>
<div class="paths-b" v-click="1">
<div class="paths-t">既にある、価値あるC資産を利用する</div>
<div class="paths-s">自分でCを書かなくても成立する。むしろ普段からやっている。</div>
</div>

<div class="paths-n">2</div>
<div class="paths-b" v-click="2">
<div class="paths-t">条件が合う小さなcoreだけ、新しくCで書く</div>
<div class="paths-s">こちらは判断が別。コストも別。</div>
</div>

</div>

<p class="punch" v-click="2">この二つは、全然ちがう話。<br><span class="dim">混ぜると「Cを使う」がいきなり重く見える。</span></p>

<!--
想定: 35秒
このframeで言いたいこと:
今日の構造。ここを混ぜないことが、最後の「候補外にしないで」を成立させる。

次への橋: 「まず 2 の側から、一番小さいところで仕組みだけ見せます」

「Cを使う」と言うと「全部Cで書く」に聞こえる。それが一番の誤解。
このあとの demo / SQLite / interop は全部この2分類のどこかに置いて話す。
-->

---
class: bleed demo-slide
---

<div class="chap">いちばん小さいC</div>
<h1 class="compact">これをブラウザで呼ぶ</h1>

<ToyWasmDemo />

<!--
想定: 45秒
このframeで言いたいこと:
目的はただ一つ。「CからコンパイルしたWASM functionを、BrowserのJavaScript側から呼べる」
というmental modelを作ること。それ以上のことは言わない。

進行:
(1) C のソースを読む。2倍するだけ。
(2) ボタンを押す。42 が出る。
(3) 「今の42は、このCソースからコンパイルしたWebAssembly functionが計算した結果です」
(4) すぐに: 「もちろん、数字を2倍するだけならJavaScriptでやってください」

次への橋: 「じゃあ、この中身が『2倍する』じゃなかったら？」

WASMの内部の講義にしない。ビルドは wasi-sdk clang、
--target=wasm32-unknown-unknown -nostdlib -ffreestanding。
標準ライブラリもWASIも使っていない。import object は空。モジュールは77バイト。
ロードに失敗した場合はボタンが無効になり、その旨を表示する。
JSで計算して「Cが動いた」ように見せることはしない。その場合はC sourceと経路図だけで話す。
-->

---
class: bleed demo-slide
---

<div class="chap">中身を入れ替えると</div>
<h1 class="compact">さっき人間が読んだ18 bytesを、Cに読ませる</h1>

<UsbDescriptorDemo />

<!--
想定: 50秒（正常系を主役に。追加操作は最大1つまで）
このframeで言いたいこと:
前半で人間が読んだ 6D 04 → 0x046D を、今度は C から compile した WASM が返す。
USBの新しい説明は一切足さない。伏線回収だけ。

進行:
(1) 「正常に解析」だけ押す。さっき手で読んだ 0x046D が、Cから返ってくる。ここで一度止まる。
(2) 時間があれば遊ぶ: bLength を 0x14 に → -2 でCが止める。
(3) 8バイトしか渡さない → -1。
(4) Big-endian として読む → 0x6D04。同じ18バイトでも読み方で別物になる。
    これは「別の解釈で読んだら」の実演。WASM 自体は little-endian。

次への橋: 「ここまでは自分が書いたCでした。次は、自分が書いていないCの話」

アドレスと全フィールドは「メモリと全フィールド」を開いたときだけ見える。通常は開かない。
失敗時は自動でJSフォールバックに落ち、バッジが「JS フォールバック」に変わる。
その場合は「今日はJSの同じ処理を表示しています」と明言し、Cが動いたとは説明しない。
時間が押していたら、この追加操作は全部飛ばしてよい。
-->

---
class: bleed mid
clicks: 1
---

# 自分が書いていないCなら、もう使っている

<div class="sqlite">
<div class="sqlite-name">SQLite</div>
<div class="sqlite-s">Cで実装されたデータベースエンジン</div>
</div>

<div class="cite" v-click="1">
<div class="cite-src">sqlite.org/whyc.html　— SQLite自身が挙げる、Cを使い続ける理由</div>
<div class="cite-list">
<span>Performance</span>
<span>Compatibility</span>
<span>Low-dependency</span>
<span>Stability</span>
</div>
</div>

<p class="note" v-click="1" style="margin-top: 18px">これはSQLite自身による説明であって、「Cが全言語より優れている」証明ではない。<br>同じページには、条件が揃えばRustへの書き換えも検討しうる、とも書かれている。</p>

<!--
想定: 45秒
このframeで言いたいこと:
単なる有名Cライブラリ一覧にしない。一つのケースを追う。
「長寿命libraryがなぜCを選び続けているか」というcase study。

次への橋: 「で、このSQLite、ブラウザでも動きます」

Compatibility の中身: ほぼ全てのシステムがCで書かれたライブラリを呼べる。
Low-dependency: 最小構成では memcmp / memcpy / memmove / memset / strcmp / strlen / strncmp のみ。
Stability: 「old and boring」であること自体を利点として挙げている。

禁止: これを「Cは速い」の証拠として使わない。SQLite自身のページには
「no other language claims to be faster than C」という強い書き方があるが、
今日はそれを自分の主張として借りない。
出典: sqlite.org/whyc.html

2例目を聞かれたら口頭で: zlib も C。Python の zlib モジュールも Node の zlib も、
その下は同じ C の実装。ただし画面には出さない。有名Cライブラリ一覧にはしない。
-->

---
class: bleed mid
---

# ブラウザで動くSQLiteの中身

<div class="arch">
<div class="arch-row"><span class="arch-a">sqlite3.c</span><span class="arch-g">canonicalなC実装（amalgamation）</span></div>
<div class="arch-row"><span class="arch-a">+ sqlite3-wasm.c</span><span class="arch-g">WASM固有のサポートを足すC</span></div>
<div class="arch-ar">↓　<span class="arch-g">Emscripten</span></div>
<div class="arch-row lit"><span class="arch-a">WebAssembly module</span></div>
<div class="arch-ar">↕　<span class="arch-g">JavaScript glue / binding</span></div>
<div class="arch-row"><span class="arch-a">Browser</span></div>
</div>

<p class="punch">「CだけでブラウザのSQLiteが完結している」<br>わけではない。</p>

<!--
想定: 35秒
このframeで言いたいこと:
CのcoreがWebへ運ばれている、という事実。ただし正確に。
sqlite3.c をそのままブラウザへ放り込んでいるわけではない。

次への橋: 「ここで一個、混ぜちゃいけない話があります」

公式WASM buildでは sqlite3-wasm.c だけを直接コンパイルし、
その中で sqlite3.c を include している。JS側は複数のJSファイルを連結した
glue / binding 層（whwasmutil.js、jaccwabyt.js、sqlite3-api-glue.js など）。
出典: sqlite.org/wasm/doc/trunk/building.md
-->

---
class: bleed mid
clicks: 1
---

# ただし、この2つは別の仕組み

<div class="worlds">

<div class="worlds-h">Web</div>
<div class="worlds-h">Native</div>

<div class="worlds-c">
<div class="w-node">JavaScript</div>
<div class="w-ar">↓　<span class="w-how">WebAssembly interface / glue</span></div>
<div class="w-node lit">Cからcompileしたmodule</div>
</div>

<div class="worlds-c">
<div class="w-tri"><span>Python</span><span>Node.js</span><span>Rust</span></div>
<div class="w-ar">↓　<span class="w-how">Python/C API・ctypes　/　Node-API　/　extern "C"</span></div>
<div class="w-node lit">C library</div>
</div>

</div>

<p class="punch" v-click="1">「全部C ABI」ではない。<br><span class="dim">Cは共通の接点になりやすい、くらいの話。</span></p>

<!--
想定: 40秒
このframeで言いたいこと:
Native interop と WASM を「全部C ABI」の一語で統一しない。仕組みは別々。

次への橋: 「つまり、Cを書かなくてもCは使っている」

正確性 (ここは間違えない):
- Node-API は Node.js が提供する stable な C API で、Node.jsのversionをまたぐ
  ABI stability を明示的に提供している。これは Node.js 側の約束。
- Rust の extern "C" は「そのtargetでdominantなC compilerが使うdefault ABI」に
  合わせるためのもの。C言語仕様がABIを定義しているわけではない。
- Python には Python/C API や ctypes がある。
- ABI は OS / CPU / toolchain ごとに違う。世界共通の単一ABIではない。
出典: nodejs.org/api/n-api.html / doc.rust-lang.org/reference/items/external-blocks.html
  / docs.python.org/3/extending/extending.html
-->

---
class: bleed mid
---

<h1 class="say">Cを書くことだけが、<br>Cを使うことではない</h1>

<p class="lede">SQLiteを使うPythonのコードに、Cは1行も出てこない。<br>それでも、動いているのはCで書かれたcoreです。</p>

<!--
想定: 20秒
このframeで言いたいこと:
「1: 既存C資産を利用する」側の結論。ここで一区切り。

次への橋: 「じゃあ 2 の、新しく書く側は？」

自分でCを書かなくても、SQLiteなどのC資産をPython / Nodeから使っている。
あるいは既存のC codeをWASMへ持ってくる。接点はC sourceを書くことだけではない。
-->

---
class: bleed mid
clicks: 1
---

# 新しくC coreを書くのは、別の判断

<div class="conds">
<span>OS / device / protocol の境界に触る</span>
<span>C APIを要求するSDKや既存環境につなぐ</span>
<span>runtime dependency を非常に薄くしたい</span>
<span>nativeとWASMなど、複数targetへ持っていきたい</span>
</div>

<div class="cost" v-click="1">
<div class="cost-k">増えるコスト</div>
<div class="cost-v">memory safety　/　FFI　/　build　/　ownership　/　deployment　/　debugging</div>
</div>

<p class="punch" v-click="1">条件が揃えば候補になる、というだけ。<br><span class="dim">Rust・C++・Goが適切な場面も当然ある。</span></p>

<!--
想定: 38秒
このframeで言いたいこと:
「既存資産を使う理由」と「新しく書く理由」は別、ということを最後まで分けきる。

次への橋: 「ここまで見たものに、いま名前を付けます」

絶対に言わないこと:
- 「小さいcoreはCで書けばよい」── 言わない。条件付きの候補、まで。
- 「Cを選べばABI stabilityが自動的に得られる」── 言わない。
  API/ABIの長期安定性は target / platform / toolchain / project側の設計と
  互換性維持にも依存する。Node-APIの安定性はNode.js側が約束しているもの。
新規コードなら Rust 等を先に検討する理由は強い。そこを弱く扱わない。
-->

---
class: bleed mid
clicks: 2
---

# 今日のCを、整理すると

<div class="recall">
<div class="recall-w" v-click="1">見える</div><div class="recall-s" v-click="1">byte representation / memory / lifetime<small>0x12345678 が 78 56 34 12 に見えた、あれ</small></div>
<div class="recall-w" v-click="1">持っていける</div><div class="recall-s" v-click="1">C source → WebAssembly → Browser<small>42 と 0x046D を返してきた、あれ</small></div>
<div class="recall-w" v-click="2">つながる</div><div class="recall-s" v-click="2">existing C libraries / bindings / native interfaces<small>SQLiteと、その周りの仕組み</small></div>
</div>

<!--
想定: 38秒
このframeで言いたいこと:
最初に分類を配らなかったのは、ここで初めて名前を付けるため。
体験したものを、あとから整理する。

次への橋: 「もちろん、これでもCが正解とは限りません」

3つとも、さっき画面に出たものを指している。新しい概念はここで一つも足さない。
「見える」は魅力、「持っていける」「つながる」は選定理由に近い。
-->

---
class: bleed mid
---

# もちろん、Cが常に正解ではない

<div class="alt">
<div class="alt-k">Webアプリ</div><div class="alt-v">TypeScriptでいい場面が多い</div>
<div class="alt-k">AI / データ</div><div class="alt-v">Pythonでいい場面が多い</div>
<div class="alt-k">新規のsystems code</div><div class="alt-v">memory safetyが重要ならRust等を検討する理由は強い</div>
</div>

<p class="punch">それでも、機械・OS・device・protocolに近づくとき、<br>既存のC資産につながるとき、<br>小さいcoreを複数の環境へ持っていくとき。</p>

<!--
想定: 28秒
このframeで言いたいこと:
最後の主張を成立させるために、先に譲るところを全部譲る。
ここを飛ばすと「Cで全部書け」に聞こえる。

次への橋: 「それで、今日いちばん言いたかったのは」

想定質問「それ Rust でよくないですか」への20秒回答:
多くの場合 Rust はよい答え。ただし既存のC ABI・既存資産・toolchainがCしかない環境、
あるいはSQLiteのように既に存在するCのcoreを使う場合は、Cが現実解になる。
そこを「古いから」で塗りつぶさないでほしい、というのが今日の主張。
-->

---
class: bleed spread
---

<div>

<h1 class="say closing-title">技術選定で、<br>最初からCを<br>候補外にしないでほしい</h1>

<p class="lede closing-sub">AIで実装の障壁が変わっても、<br>どの抽象度で見るか、どの資産につなぐかは残ります。</p>

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
想定: 33秒
このframeで言いたいこと:
冒頭と同じ18バイト。今度は offset 8-9 だけに色がついている。
冒頭に置いたAIの立場を、ここで閉じる。

「AIがあるからCを使え」ではない。
「実装の障壁が変化しても、どの抽象度・どの既存資産を採用するかは技術選定として残る」。
だから、必要なときはCも選択肢へ戻してほしい。ありがとうございました。

通しの想定は 13分40秒。15分枠に対して約1分20秒の余裕。Appendixは含めない。
追加操作（スライド15の「追加で試す」を全部やる、スライド14で値を変えて2回押す）を
入れると 14分40秒まで伸びる。押していたらそこから削る。
それでも足りないときの削り順: スライド19 → スライド22の3行目 → スライド20のコスト行。
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
