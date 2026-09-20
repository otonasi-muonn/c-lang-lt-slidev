---
theme: default
title: AI時代に、なぜ今さらC言語なのか
info: |
  ハックツコミュ「自分の推し技術について語りたいよねの会」15分セッション用 Slidev 資料
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

<div class="flex justify-between items-start">

<div>
<h1 class="say">AI時代に、<br>なぜ今さらC言語なのか</h1>

<div class="flex items-center gap-4">
  <img src="/avatar.png" alt="無音" class="rounded-full object-cover" style="width: 48px; height: 48px; border-radius: 50%; object-fit: cover; border: 1px solid var(--rule-lit);" />
  <p class="lede" style="margin: 0">推し技術LT　—　無音 / ハックツ Committer</p>
</div>
</div>

<img src="/avatar.png" alt="無音" class="rounded-full object-cover" style="width: 140px; height: 140px; border-radius: 50%; object-fit: cover; border: 2px solid var(--rule-lit); margin-top: 8px;" />

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

<p class="note" style="margin-top: 22px">ハックツコミュ「自分の推し技術について語りたいよねの会」15分セッション用</p>

</div>

<!--
⚡【10秒ひとこと要約】
「ハックツの無音です！今日はAI時代にあえてC言語を推す面白さについてお話しします！」
--------------------------------------------------
想定: 20秒
【口頭トークガイド】
「皆さんこんにちは！ハックツのコミッター（Committer）をやっている無音（むおん）と申します。
今日は『推し技術について語るLT』ということで、私が大好きな『C言語』についてお話しします。
令和の、しかもAI全盛期の今、なぜあえて半世紀前の言語である『C』なのか？ その面白さを共有できればと思います」

次への橋:
「『なぜ今さらC言語なのか』という本題に入る前に、まずは前提として『AI時代の開発環境』について少し触れさせてください」

【発表メモ】
・画面下の18バイトの数字（12 01 00 ...）は、この時点ではあえて一切触れない（最後のスライドで伏線回収する演出）。
・自分のアイコン（桜と基盤の木）を載せている点も、自然に自己紹介の雰囲気に繋げる。
-->

---
class: bleed mid
clicks: 1
---

<h1 class="say">今は、知らない言語でも<br>AIに書いてもらえる時代になってきた</h1>

<div class="pivot" v-click="1">
<p class="pivot-line">だから面白いのは、<br><span class="sig">「書ける言語から選ぶ」制約がなくなり、<br>「課題に最適な言語を自由に選べる」状態</span>になった</p>
<p class="note pivot-tag">— あくまで個人の感想です</p>
</div>

<!--
⚡【10秒ひとこと要約】
「AIのおかげで『書ける言語』ではなく『課題に最適な言語』を選べる、技術選定が一番面白い時代になりました！」
--------------------------------------------------
想定: 30秒
【口頭トークガイド】
(1) クリック前:
「最近、GitHub CopilotやClaude、ChatGPTなどのAIツールが本当に凄くて、文法をよく知らないプログラミング言語でも、AIにお願いすれば動くコードを書いてくれる時代になりましたよね」

(2) 1クリック目（「だから面白いのは…」）:
「だからこそ逆に面白いのが、『自分が書ける言語の中から選ぶ』という制約が消えて、『この課題にはどの言語が一番適しているか？』を自由に選べるようになった点です。
実装のコストが下がったからこそ、純粋な『技術選定』が以前よりずっと楽しくなったと感じています」

次への橋:
「では、その選択肢の一つとして、そもそも『C言語』ってどんな立ち位置の言語だったのか、おさらいしてみましょう」

【補足メモ】
・注意点: 「AIがあるからCが有利」と断定するのではなく、あくまで「エンジニアとしての個人の視点・楽しさ」として話す（最後のまとめで回収する）。
-->

---
class: bleed mid
clicks: 1
---

# そもそも、C言語とは

<div class="facts">
<div class="facts-k">成立</div><div class="facts-v">1972年 / <span class="dim">Dennis M. Ritchie</span><span class="facts-s">Bell Labs（ベル研究所）で開発</span></div>
<div class="facts-k">用途</div><div class="facts-v">初OS（初期Unix）を作るための言語 <span class="facts-s">ハードウェアを直接制御する目的で誕生</span></div>
<div class="facts-k">実行</div><div class="facts-v">機械語に直接変換され、そのまま動く<span class="facts-s">実行時の仲介機構（VMやGC）を持たず、高速・軽量</span></div>
</div>

<p class="punch" v-click="1">アセンブリ言語より扱いやすく、<br>ハードウェアも直接制御できる</p>

<!--
⚡【10秒ひとこと要約】
「C言語はOSを作るために生まれた、VMもGCもない『人間が読めるアセンブリ』のような最速・最軽量の言語です」
--------------------------------------------------
想定: 35秒
【口頭トークガイド】
(1) クリック前:
「C言語は1972年、ベル研究所のデニス・リッチーによって作られました。
元々は『UNIX（ユニックス）』というOSを作るために設計された言語で、メモリやCPUなどのハードウェアを直接操るために生まれました。
Javaのような仮想マシン（VM）や、メモリを自動掃除するガベージコレクション（GC）のような仲介役がなく、コンパイルするとそのままCPUが実行できる機械語になります」

(2) 1クリック目（まとめパンチライン）:
「一言で言えば、『人間が読み書きしやすいアセンブリ言語』のような存在で、ハードウェアを一番生々しくコントロールできるのが最大の特徴です」

次への橋:
「では、比較対象として、私たちが普段Web開発などで一番よく触っている現代の代表的な言語も見てみましょう」

【補足・質問対策】
・歴史メモ: C言語の前身はB言語、さらにその前身はBCPL（ビーシーピーエル）。PDP-11というミニコンへの移植時に『型』が必要になってCが誕生した。
・歴史の講義にしすぎず、3つのポイント（OS用・直接実行・高速軽量）をテンポよく読み上げる。
-->

---
class: bleed mid
---

# 今日の比較対象は、TypeScript

<div class="facts">
<div class="facts-k">概要</div><div class="facts-v">JavaScriptに静的型システムを導入した言語<span class="facts-s">補足：Web開発における事実上の業界標準（デファクトスタンダード）</span></div>
<div class="facts-k">現在</div><div class="facts-v">2025年8月、GitHubの<span class="wide">月間コントリビューター数で1位</span><span class="facts-s">補足：Pythonを約42,000人上回った（GitHub Octoverse 2025）</span></div>
</div>

<p class="punch">Webアプリを作るなら、<br>第一候補として真っ先に選ばれる言語です。</p>

<p class="note" style="margin-top: 1px">同レポートにおいて、AI関連リポジトリではPythonが引き続き優勢。</p>

<!--
⚡【10秒ひとこと要約】
「普段Webなら自分も迷わずTypeScriptを使います。GitHubでも1位の最高峰言語です。じゃあなぜCなのか？」
--------------------------------------------------
想定: 35秒
【口頭トークガイド】
「比較として挙げるのは、現代のWeb開発のデファクトスタンダード（標準）、TypeScriptです。
JavaScriptに型の安全性を足した言語で、GitHub公式の年次レポート（Octoverse 2025）でも、月間コントリビューター数でPythonを抜いて堂々の世界1位になりました。
私もハッカソンや個人開発でWebアプリを作るなら、真っ先にTypeScriptを選びます。これ以上に書きやすくて生産性の高い言語はありません」

次への橋:
「では、普段TypeScriptを愛用している私が、なぜわざわざC言語を『推し技術』として語るのか。その核心に入っていきます」

【補足メモ・発表のコツ】
・絶対に『TypeScript vs C言語』の勝ち負け論や速度論争にしない。「自分もWeb開発なら迷わずTypeScriptを使う」とリスペクトを宣言しておくことで、後半の説得力が増す。
・データの新しさ: Octoverse年次レポートは毎年10月下旬発表のため、現時点で本データが公式の最新確定値（次回2026年版は来月10月下旬発表予定）。
-->

---
class: bleed mid
---

<h1 class="say">Cは、機械側の都合が<br>表面に出てきやすい</h1>

<div class="surface">
<span>値が何バイトか</span>
<span>メモリ上でどう並ぶか</span>
<span>どのアドレスにあるか</span>
<span>いつまで生きているか</span>
</div>

<p class="punch">普段はランタイムやライブラリが隠してくれるものが、<br>自分のコードの側に出てくる<br><span class="dim">面倒だし、危険でもある</span><br></p>

<h1 class="say" style="color: var(--sig); margin-top: 24px; margin-bottom: 0;">ただ面白い！</h1>

<!--
⚡【15秒ひとこと要約】
「C言語の魅力は、メモリやアドレスといった『機械側の都合』が全部むき出しになること。面倒で危険だけど、これが最高に面白い！」
--------------------------------------------------
想定: 30秒
【口頭トークガイド】
「C言語の最大の魅力は、『コンピュータ・機械側の都合が、コードの表面にそのまま出てくること』です。
この値は何バイト消費するのか？ メモリのどこに配置されるのか？ いつ消えるのか？
普段TypeScriptやPythonを使っていると、言語のランタイムやガベージコレクションが裏で全部良しなに隠してくれていますよね。
C言語では、それが全部むき出しになって自分の目の前に現れます。
正直、面倒くさいですし、一歩間違えればバグやクラッシュを引き起こす危険もあります。でも……これが最高に面白いんです！」

次への橋:
「口頭の理屈だけだと伝わりにくいので、一番シンプルな例を実際に画面で動かして見てみましょう」

【補足・注意点】
・NGワード: 「C言語＝CPUそのもの」「Cならコンピュータの全てが見える」とは言わない。C言語も抽象マシン（Abstract Machine）規格。
・あくまで「普段隠されている下のレイヤーが表面に露出して、コンピュータを直に触っている手応えがあるのが楽しい」という感情を素直に伝える。
-->

---
class: bleed mid
clicks: 3
---

# メモリ上の並びを直接確認する

<div class="obs">

<pre class="obs-code"><code><span class="dim">uint32_t</span> x = <span class="wide">0x12345678</span>;</code></pre>

<pre class="obs-code" v-click="1" style="margin-top: 18px; font-size: 16px; color: var(--ink); line-height: 1.75;"><code><span style="color: var(--ink-2)">unsigned char</span> *p = (<span style="color: var(--ink-2)">unsigned char</span> *)&amp;x;
<span style="color: var(--ink-2)">// printf: 画面に出力する関数（%02X で1バイトを2桁の16進数表示）</span>
printf(<span style="color: var(--wide)">"%02X %02X %02X %02X\n"</span>, p[0], p[1], p[2], p[3]);</code></pre>

<div class="obs-out" v-click="2">
<div class="obs-prompt" style="color: var(--ink-2);">$ gcc endian.c &amp;&amp; ./a.out</div>
<div class="bytes four"><span class="sig">78</span><span class="sig">56</span><span class="sig">34</span><span class="sig">12</span></div>
</div>

<div class="obs-name" v-click="3" style="color: var(--ink);">下位バイトから順に格納される <strong class="wide">リトルエンディアン（little-endian）</strong></div>

<p class="note obs-env" v-click="2" style="color: var(--ink-2);">gcc 13.3.0 / x86_64-linux-gnu で実行<br>C言語の規則ではなく、CPUのメモリ配置をCがそのまま露出させている。</p>

</div>

<!--
⚡【15秒ひとこと要約】
「0x12345678をメモリ上で覗くと、CPUの都合で逆順の『78 56 34 12（リトルエンディアン）』で並んでいるのがそのまま見えます」
--------------------------------------------------
想定: 55秒
【口頭トークガイド】
(1) クリック前:
「まず、0x12345678 という4バイトの数値を定義します。ここまではどのプログラミング言語でも同じ、ごく普通の数値です」

(2) 1クリック目（コード追加）:
「では、この数値はメモリの上で実際にどう並んでいるのでしょうか？ ポインタを使って1バイトずつ覗いてみます。
ここで呼んでいる printf（プリントエフ）は画面に文字を出力する関数で、%02X は『1バイトを2桁の16進数で表示する』という指定です」

(3) 2クリック目（実行結果）:
「これをコンパイルして実行してみると……なんと『78 56 34 12』と、後ろの桁から逆順で出力されます！」

(4) 3クリック目（まとめ）:
「このように、下位の桁（小さい位）から順にメモリへ並べる方式を『リトルエンディアン』と呼びます。
これはC言語が決めたルールではなく、いま動いているパソコンのCPUのメモリ配置を、C言語がそのまま表面に見せてくれているわけです」

次への橋:
「これ、実は教科書の中だけの話ではなく、本物のプロトコル（通信規格）にもそのまま出てきます」

【補足メモ（カタカナ解説）】
・リトルエンディアン（little-endian）: 小さい桁からメモリに並べる方式。
・ビッグエンディアン（big-endian）: 大きい桁（12 34 56 78）から並ぶ環境（ネットワーク通信規格など）もある。
・オブジェクト表現: アンサインド・チャー（unsigned char）型を使ってメモリの生データを直接覗くのは、Cの規格で正式に認められた安全な読み方。
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

<p class="lede" style="margin-top: 14px">USB デバイスディスクリプタ（Device Descriptor）<br><span class="dim">デバイスが返す18バイトの自己紹介</span></p>

<div class="lift" v-click="1">
<div class="lift-k" style="font-size: 18px; color: var(--ink-2); margin-bottom: 14px;">offset 8–9　メーカーを表す欄　—　<span style="color: var(--sig); font-weight: 700;">下位のバイトが先（リトルエンディアン）</span></div>
<div class="lift-chain">
<span class="lift-raw">6D 04</span>
<span class="lift-arrow">→</span>
<span class="lift-val wide">0x046D</span>
<span class="lift-arrow" v-click="2">→</span>
<strong class="lift-name" v-click="2">Logitech</strong>
</div>
</div>

<p class="note lit" style="margin-top: 20px">実機のダンプではなく、デバイスディスクリプタ（Device Descriptor）の形式に沿って実在するVID / PIDで構成した例</p>

<!--
⚡【15秒ひとこと要約】
「USBの18バイトの自己紹介データ（デバイスディスクリプタ）も全く同じ。リトルエンディアンで読むとロジクールの製品だと分かります」
--------------------------------------------------
想定: 48秒
【口頭トークガイド】
(1) クリック前:
「USB機器をパソコンに挿すと、デバイスは最初に18バイトの自己紹介データを返してきます。これを『デバイスディスクリプタ』と呼びます」

(2) 1クリック目（2バイトに注目）:
「この中の offset 8〜9（9〜10バイト目）に注目してください。ここはメーカーを表す欄です。
画面には『6D 04』と並んでいます。さっきやった『リトルエンディアン（下位バイトが先）』を思い出してください」

(3) 2クリック目（変換と特定）:
「後ろの桁から並べ直すと、16進数で『0x046D』になります。
この 0x046D をUSBのメーカー一覧で照合すると……マウス等で有名な『Logitech（ロジクール）』だとわかるんです！」

次への橋:
「さっき学んだメモリの並び順の知識だけで、本物の規格のデータが読めましたね。で、実はこれ、TypeScriptでも普通に扱えます」

【補足メモ】
・デバイスディスクリプタ（Device Descriptor）: USB機器がPCに接続された際、機器の種別やメーカー情報を伝える基本的な自己紹介データ構造。
-->

---
class: bleed mid
---

# これだけなら、TypeScriptの方が楽

<div class="vs" style="margin-top: 24px">
<div>
<div class="vs-k">TypeScript / JavaScript</div>
<pre class="vs-code"><code>const view = new DataView(buf);
const vid: number =
    view.getUint16(<span class="wide">8</span>, <span class="sig">true</span>);</code></pre>
<div class="vs-hint">第2引数の <span class="sig">true</span> が「リトルエンディアン（little-endian）で読む」</div>
</div>
<div>
<div class="vs-k">C</div>
<pre class="vs-code"><code>(uint16_t)p[<span class="wide">8</span>]
  | ((uint16_t)p[<span class="wide">9</span>] <span class="sig">&lt;&lt; 8</span>)</code></pre>
<div class="vs-hint">2バイトの組み立てが自分のコードに出る</div>
</div>
<div class="vs-same"><span class="lab">同じ入力 → どちらも</span><span class="val">0x046D</span></div>
</div>

<p class="punch" style="margin-top: 26px">能力の差ではなく、<br>自分が触っている抽象度の差</p>

<!--
⚡【10秒ひとこと要約】
「バイナリを読むだけならTypeScriptのDataViewの方が圧倒的に楽。これは能力差ではなく、触っている抽象度の違いです」
--------------------------------------------------
想定: 35秒
【口頭トークガイド】
「さっきのバイナリの読み取りですが……正直に言うと、これだけならTypeScriptの方が圧倒的に楽です！
TypeScriptには DataView という仕組みがあって、`view.getUint16(8, true)` と書くだけで、第2引数の `true`（リトルエンディアン指定）に従って2バイトを自動で合体してくれます。
一方、C言語だと `(uint16_t)p[8] | ((uint16_t)p[9] << 8)` のように、8ビットずらしてOR演算する（ビットシフトする）コードを自分で書かないといけません。
結果はどちらも同じ『0x046D』になります」

「これは言語の能力の差ではなく、『自分がコンピュータのどの抽象度（レイヤー）を触っているか』の違いです」

次への橋:
「『じゃあ楽なTypeScriptだけでいいじゃん』となりますよね。機械に近いと何が嬉しいのか？……をお話しする前に、まず『近いことの代償・恐ろしさ』をお見せします」

【補足・質問対策】
・C言語のキャスト `(uint16_t)`: 8ビット値をそのまま左シフトすると整数拡張で意図しない挙動になる環境を防ぐ安全な書き方。
・強調ポイント: TypeScriptでもバイト列は普通に扱える。C言語が万能でTSが劣っているという話ではなく、「触っている深さが違う」というリスペクトの視点。
-->

---
class: bleed mid
clicks: 1
---

<div class="chap">近いことの代償</div>

# 近いと、こういうものも見えてしまう

<div class="pad" style="margin-top: 20px">

<div class="pad-k">通信上</div>
<div class="cellrow big"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div>
<div class="pad-n">7 <small>バイト</small></div>

<div class="pad-k" v-click="1">構造体</div>
<div class="cellrow big" v-click="1"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad" aria-label="パディング">＋</span></div>
<div class="pad-n sig" v-click="1">8 <small>バイト</small></div>

</div>

<div class="evidence" v-click="1">
<div class="evidence-out"><span>wire   : 7</span><span>sizeof : 8</span></div>
<div class="evidence-src" style="color: var(--ink-2); font-size: 13px;">USB エンドポイントディスクリプタ（Endpoint Descriptor）の6フィールドをそのまま並べた構造体。gcc 13.3.0 / x86_64-linux-gnu。<br>サイズもパディングもABI依存で、いつも8になるわけではない。</div>
</div>

<p class="punch" v-click="1" style="margin-top: 22px">通信上の長さと、メモリ上の大きさは<br>同じとは限らない。</p>

<!--
⚡【10秒ひとこと要約】
「近いことの代償として、CPUの都合で勝手に1バイト隙間が空く『パディング』のようなメモリの罠が見えてしまいます」
--------------------------------------------------
想定: 45秒
【口頭トークガイド】
(1) クリック前:
「C言語がメモリに近いことの代償として、こういう厄介なものも見えてしまいます。
例えば USBの Endpoint Descriptor（エンドポイント記述子）は、通信規格上は7バイトのデータです」

(2) 1クリック目（構造体のサイズ表示）:
「ところが、これをC言語で構造体（struct）としてそのまま定義してサイズ（sizeof）を測ると……なんと『8バイト』になります！
1バイト増えていますよね。この自動で差し込まれた1バイトを『パディング（詰め物）』と呼びます」

(3) 具体的な落とし穴と解説:
「なぜ増えるかというと、CPUがメモリを読み書きしやすいよう、コンパイラが自動で隙間を空けて配置する（アライメント）からです。
これの何が危険かというと、『通信で届いた7バイトの生データを、そのまま構造体にポインタキャストして読もう！』とすると、
この見えないパディングのせいで後ろのデータが1バイトズレてしまい、値がめちゃくちゃに壊れます。
組み込みやネットワーク通信をやると、誰もが一度は踏む超定番の落とし穴です」

次への橋:
「通信上の長さと、メモリ上の大きさは同じとは限らない。では、もう一つ『もっと危ないメモリの罠』をお見せします」

【補足メモ（登壇・質問対策）】
・パディング（Padding）: CPUのアクセス効率（アライメント境界）のため、コンパイラがメンバ間や末尾に挿入する隙間バイト。
・どう対策するか: `__attribute__((packed))` などのコンパイラ拡張でパディングを詰めるか、さっきのように1バイトずつ取り出して組み立てる。
・環境依存性: パディングの有無やサイズはCPUアーキテクチャやABI（x86_64、ARMなど）によって異なり、常に8バイトになるとは限らない（Appendixに各記述子の比較あり）。
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
<div class="evidence-out"><span>warning: function returns address of local variable [-Wreturn-local-addr]</span></div>
<div class="evidence-src" style="color: var(--ink-2); font-size: 13px;">この形なら、黙っていてもコンパイラが教えてくれる。ただし警告が出ない書き方もいくらでもある。</div>
</div>

<p class="punch" v-click="1" style="margin-top: 20px">AIがCを書けるようになっても、<br>メモリと寿命の意味は消えない。</p>

<!--
⚡【15秒ひとこと要約】
「ローカル変数のポインタを返すと寿命が切れてバグる。AIがコードを書けても、メモリと寿命のルールを理解するのは人間の役目です」
--------------------------------------------------
想定: 50秒
【口頭トークガイド】
(1) クリック前:
「パディングの次にお見せしたい、もう一つの危険な罠がこれです。
この `message` 関数を見てください。中で `buf` という配列を作って、その先頭アドレス（住所）を `return` で返しています。
一見、文字列を返しているだけのように見えますよね」

(2) メモリの寿命の解説:
「ところが、右の図を見てください。`buf` は関数の中だけで作られたローカル変数（スタック領域）なので、関数が終わった瞬間にそのメモリの寿命は尽きてしまいます。
関数の外に返されたのは『かつてデータが存在した住所』だけ。もうそこには誰も住んでいません」

(3) コンパイラ警告とAIへの接続（1クリック目）:
「この単純なコードなら、親切なコンパイラが『ローカル変数のアドレスを返してるよ』と警告（ワーニング）を出してくれます。
ですが、ポインタが構造体や引数を経由すると、コンパイラも警告を出せなくなります。
最近はAIにC言語を書かせることもできますが、コードが文法的に合っていても、『この変数がいつ生まれ、いつ死ぬのか』というメモリの寿命（ライフタイム）のルールを人間が理解していなければ、恐ろしいバグを見逃してしまうことになります」

次への橋:
「『でも、そんなミス滅多に起きないでしょ？』と思うかもしれません。実はこれ、現代のソフトウェアにおいて一番深刻な問題なんです」

【補足メモ・質問対策】
・ダングリングポインタ（Dangling Pointer）: 寿命が切れたメモリ領域を指したままの無効なポインタ。
・運悪く動いてしまう恐怖: C言語の規格（C11）上、寿命が切れた後のポインタ参照は未定義動作（Undefined Behavior）。メモリが即座にゼロクリアされるわけではないため、テスト環境ではたまたま動いてしまい、本番で突然クラッシュや情報漏洩を引き起こす。
-->

---
class: bleed mid
---

# 実際、ここが現代いちばんの弱点

<div class="risk">
<div class="risk-big"><span class="err">約70%</span></div>
<div>
<div class="risk-txt">Chromeの高深刻度セキュリティバグのうち、<br>C/C++のメモリ安全性の問題が原因のもの。</div>
<div class="risk-note">その半分が use-after-free<span style="color: var(--ink-2);">（さっき見た、あの寿命の話）</span></div>
<div class="risk-scope" style="color: var(--ink-2);">2015年以降の高・重大深刻度912件を対象にした、Chromium 自身の集計</div>
</div>
</div>

<div class="risk-2">
CISAをはじめとする各国機関は、メモリ安全性の脆弱性をどう無くすかを示すロードマップの公開を推奨している。
</div>

<p class="punch">だから「これからは何でもCで書こう」<br>とは、言いません。</p>

<!--
⚡【10秒ひとこと要約】
「Chromeの重大バグの7割がメモリ安全性の問題です。だから『何でもCで書こう』なんて言うつもりはありません」
--------------------------------------------------
想定: 40秒
【口頭トークガイド】
「実際、世界最高峰のエンジニアたちが集まるGoogle Chromeの開発チームでも、高深刻度なセキュリティバグの約70%が『CやC++のメモリ安全性の問題』なんです。
そして、そのうちの実に半分が、先ほどお話ししたメモリ寿命の罠――いわゆる『ユース・アフター・フリー（Use-After-Free: 解放後メモリの不正利用）』です」

「アメリカのサイバーセキュリティ機関（CISA）なども、『メモリ安全性のない言語からの移行計画を作ろう』と強く呼びかけています。
だからこそ、私は『これからは何でもC言語で書こう！』なんて暴論を言うつもりは全くありません」

次への橋:
「では、普段TypeScriptやPythonなどのモダンな言語を愛用している私たちが、一体どんな場面でC言語を思い出すべきなのでしょうか？ ここからが今日一番話したい本題です」

【補足メモ（登壇・質問対策）】
・ユース・アフター・フリー（Use-After-Free）: メモリを解放（free）した後や寿命が切れた後に、残ったポインタ経由でアクセスしてしまう脆弱性。攻撃者に任意のコードを実行されるリスクがある。
・Rust等の扱い: メモリ安全な言語（Rustなど）が適切な場面は当然あるため、Rustを否定するのではなく「C言語のリスクを正面から受け止めた上で、適切な使い所を見極める」というスタンスを強調する。
-->

---
class: bleed mid
---

<h1 class="say">じゃあ、普段TypeScriptやPythonを<br>使っている自分が、<br>どんな時にCを思い出すのか</h1>

<p class="lede">ここまでは「Cって面白いね」の話。<br>ここからが今日の本題です。</p>

<!--
⚡【10秒ひとこと要約】
「では、普段モダン言語を使う私たちが、一体どんな時にC言語を思い出すべきなのか？ ここからが本題です」
--------------------------------------------------
想定: 25秒
【口頭トークガイド】
「ここまでお話ししてきたのは、『C言語って機械の生データが見えて面白いよね、でもメモリ管理は危険だよね』という前提の知識でした。
ここからが今日の本題です。
普段TypeScriptでWeb開発をしたり、PythonでAIやデータ分析をしている私たちが、実際の開発の中で『どんな瞬間にC言語を思い出すのか』。そのリアルな活用法をお話しします」

次への橋:
「その本題に入る前に、多くの人が抱いている『ある大きな誤解』を最初に解消させてください」

【発表メモ】
・ここはセッションの折り返し地点（約7〜8分経過）。少し間を取り、聴衆の目線を一度引き戻す。
・「単なるC言語オタクの思い出話」ではなく、「普段モダン言語を書くエンジニアのための実用的な話」にフェーズが切り替わったことを伝える。
-->

---
class: bleed mid
clicks: 2
---

# Cを使う ＝ 全部Cで書く、ではない

<div class="paths">

<div class="paths-n">1</div>
<div class="paths-b">
<div class="paths-t" v-click="1">既にある、価値あるC資産を利用する</div>
<div class="paths-s" v-click="1">自分でCを書かなくても成立する。むしろ普段からやっている。</div>
</div>

<div class="paths-n">2</div>
<div class="paths-b">
<div class="paths-t" v-click="2">条件が合う小さなコアだけ、新しくCで書く</div>
<div class="paths-s" v-click="2">こちらは判断が別。コストも別。</div>
</div>

</div>

<p class="punch" v-click="2">この二つは、全然ちがう話。<br><span class="dim">混ぜると「Cを使う」がいきなり重く見える。</span></p>

<p class="note lit" v-click="2" style="margin-top: 16px">AIに書かせる部分が増えるほど、「どっちをやるか」の判断だけが自分に残る。</p>

<!--
⚡【10秒ひとこと要約】
「Cを使う＝全部Cで書く、ではありません。『①既存の資産を使う』と『②小さなコアだけ書く』は全く別の話です」
--------------------------------------------------
想定: 40秒
【口頭トークガイド】
(1) クリック前:
「『C言語を使う』と聞くと、多くの人は『アプリ全体をゼロから全部C言語で書くこと』を想像して、『うわ、大変そう……』と身構えてしまいます。
でも、実はそうじゃないんです。C言語との付き合い方には、まったく別の2つのルートがあります」

(2) 1クリック目（「1: 既にあるC資産を利用する」）:
「1つ目は『世界中ですでに磨き上げられた、価値あるC言語の既存資産を利用する』こと。
これは自分でCコードを1行も書かなくても成立しますし、皆さんも普段から無意識に恩恵を受けています」

(3) 2クリック目（「2: 小さなコアだけCで書く」）:
「2つ目は『どうしても必要な条件が揃ったときだけ、小さなコア機能だけを新しくCで書く』こと。
この2つはコストもリスクも全く別の話です。混ぜてしまうから『Cを使う＝重い・時代遅れ』に見えてしまうんです。
AIがコードを自動生成してくれる時代だからこそ、エンジニアに残された一番大事な仕事は『この2つのどちらを選ぶべきか』を正しく見極める判断力です」

次への橋:
「まずは『2番（新しく小さなコアを書く）』の最小の実例として、ブラウザで動くデモをお見せします」

【補足メモ】
・この後の展開: デモ（スライド14・15）が「2: 小さなコアを書く」、SQLite（スライド16・17）が「1: 既存資産を使う」に対応している。全体の骨組みになるスライド。
-->

---
class: bleed demo-slide
---

<div class="chap">2 — 小さいコアを書く、のいちばん小さい版</div>
<h1 class="compact">これをブラウザで呼ぶ</h1>
<p class="note lit demo-lede">WebAssembly＝ブラウザがJavaScript以外のコードも実行できる形式。</p>

<ToyWasmDemo />

<!--
⚡【10秒ひとこと要約】
「【デモ1】C言語で書いた小さな関数をWebAssemblyにすれば、ブラウザのJavaScriptから直接呼び出せます」
--------------------------------------------------
想定: 45秒
【口頭トークガイド】
(1) 画面の解説:
「『新しくCでコアを書く』の最もシンプルな最小例です。
画面に出ているC言語のコードは、引数を2倍にするだけの超シンプルな関数です。
WebAssembly（ウェブアセンブリ / WASM）という技術を使うと、このC言語のソースコードをコンパイルして、ブラウザの中で動かすことができます」

(2) デモ実演:
「いまスライド上の『実行』ボタンを押してみます。……はい、『42』と表示されました！
今この瞬間に動いたのは、JavaScriptではなく、C言語からコンパイルされたWASMモジュールです」

(3) 補足とツッコミ:
「もちろん、数値を2倍するだけならJavaScriptで直接書けばいいですよね。
でも、『C言語で書いた関数を、ブラウザのフロントエンドから直接呼び出せる』という仕組みそのものが、非常に強力な武器になります」

次への橋:
「では、この中身が『単に2倍する関数』ではなく、先ほど手作業で解読した『あのUSBの18バイトを解析するロジック』だったらどうなるでしょうか？」

【補足メモ（技術背景）】
・ビルド構成: wasi-sdk clang（--target=wasm32-unknown-unknown -nostdlib -ffreestanding）。標準ライブラリを使わず極小モジュール（77バイト）にコンパイルしている。
・トラブル対応: 万一ボタンが動かない場合は「Cソースと実行経路」を図示・説明して進行する。
-->

---
class: bleed demo-slide
---

<div class="chap">中身を入れ替えると</div>
<h1 class="compact">さっき自分たちで読んだ18バイトを、Cに読ませる</h1>

<UsbDescriptorDemo />

<!--
⚡【15秒ひとこと要約】
「【デモ2】前半手作業で読んだUSBの18バイト解析をWASMに任せると、一瞬でロジクール（0x046D）を特定してくれます」
--------------------------------------------------
想定: 50秒
【口頭トークガイド】
(1) 伏線回収の導入:
「先ほど前半で、皆さんと一緒に手作業で読んだ『USBの18バイト（デバイスディスクリプタ）』を覚えていますでしょうか？
今度はあの解析処理を、C言語で書いたコアロジックに任せてみます」

(2) デモ実演（正常系）:
「画面の『正常に解析』ボタンを押してみます。
……はい！ 先ほど私たちが電卓のように手動で並び替えた『0x046D』というベンダーIDが、C言語のWASMから瞬時に返ってきました！」

(3) 追加実演（異常系やエンディアンの検証・時間があれば1つだけ）:
「もし途中のデータ長（bLength）を壊してみると……Cのコアが『-2（不正なフォーマット）』として安全にエラー検知して弾きます。
また、ビッグエンディアンとして誤って読むと『0x6D04』という全く別の値になります。
このように、複雑で厳密なバイナリ処理のコアだけをC言語で堅牢に作り、ブラウザのUIから呼び出すことができるわけです」

次への橋:
「ここまでは『自分で新しくCを書く』話でした。次はもう一つのルート、『世界中にある既存のC資産を使う』話に進みます」

【発表メモ】
・正常系の解析（0x046D）を主役に。時間が押している場合は追加操作は無理に触らず次に進む。
・万一WASMエラーが出ても自動でJSフォールバックに落ちるので、「今日はJSで同じロジックを再現しています」と落ち着いて案内すればOK。
-->

---
class: bleed mid
clicks: 1
---

<div class="chap">1 — 既にあるC資産を使う</div>

# 自分が書いていないCなら、もう使っている

<div class="sqlite">
<div class="sqlite-name">SQLite</div>
<div class="sqlite-s">Cで実装されたデータベースエンジン</div>
<div class="sqlite-more">zlibも、libpngも、CPython自体もCで書かれている。</div>
</div>

<div class="cite" v-click="1">
<div class="cite-src" style="color: var(--ink-2); font-size: 13px;">sqlite.org/whyc.html　— SQLite自身が挙げる、Cを使い続ける理由</div>
<div class="cite-list">
<span>Performance <small style="font-size: 16px; color: var(--ink-2);">（高速性）</small></span>
<span>Compatibility <small style="font-size: 16px; color: var(--ink-2);">（高い互換性）</small></span>
<span>Low-dependency <small style="font-size: 16px; color: var(--ink-2);">（極小の依存）</small></span>
<span>Stability <small style="font-size: 16px; color: var(--ink-2);">（枯れた安定性）</small></span>
</div>
</div>

<p class="note" v-click="1" style="margin-top: 18px; color: var(--ink-2);">これはSQLite自身による説明であって、「Cが全言語より優れている」証明ではない。<br>同じページには、条件が揃えばRustへの書き換えを検討する余地がある、とも書かれている。</p>

<!--
⚡【10秒ひとこと要約】
「SQLiteやPython自体もC言語製。圧倒的な互換性と枯れた安定性があるから、世界中で選ばれ続けています」
--------------------------------------------------
想定: 45秒
【口頭トークガイド】
(1) クリック前:
「2つ目のルート、『既にあるC言語の資産を使う』についてです。
世界で最も普及しているデータベースエンジン『SQLite』は、すべてC言語で書かれています。
他にも、画像圧縮の zlib や libpng、さらには私たちが普段実行している Python の標準処理系（CPython）自体も、実はC言語で実装されています。
つまり、皆さんが『私はC言語なんて1行も書いていない』と思っていても、裏側では毎日C言語の恩恵を受けまくっているわけです」

(2) 1クリック目（SQLiteがCを使い続ける4つの理由）:
「では、なぜSQLiteの開発チームは、今なおC言語を選び続けているのでしょうか？
公式ドキュメントには4つの理由が挙げられています。
高速な性能（Performance）はもちろんですが、特に重要なのが『圧倒的な互換性（Compatibility）』と『依存関係の少なさ（Low-dependency）』、そして『枯れた安定性（Stability）』です。
あらゆるOSや言語から呼び出せて、最小構成なら標準ライブラリの数個の関数だけで動く。このポータビリティこそがC言語の真骨頂です」

次への橋:
「そして驚くべきことに、このC言語で書かれたSQLiteは、今やWebブラウザの中でもそのまま動いてしまいます」

【補足メモ（質問対策・登壇メモ）】
・客観性の担保: SQLite自身が公式に「他言語より優れている」と過信しているわけではなく、「枯れていて退屈（Old and boring）だからこそ壊れない」という実用主義。Rustへの移行の可能性も公式で言及されている点に触れると説得力が増す。
・低依存性（Low-dependency）: 最小構成では memcmp, memcpy, memmove, memset, strcmp, strlen 程度しか外部関数を要求しない。
-->

---
class: bleed mid
---

# ブラウザで動くSQLiteの中身

<div class="arch">
<div class="arch-row"><span class="arch-a">sqlite3-wasm.c</span><span class="arch-g">WASM固有のサポートを足す、唯一コンパイルされるCファイル</span></div>
<div class="arch-row sub"><span class="arch-a">└ #include "sqlite3.c"</span><span class="arch-g">SQLite本体のC実装（amalgamation）</span></div>
<div class="arch-ar">↓　<span class="arch-g">Emscripten</span></div>
<div class="arch-row lit"><span class="arch-a">WebAssembly モジュール</span></div>
<div class="arch-ar">↕　<span class="arch-g">JavaScript のグルー / バインディング</span></div>
<div class="arch-row"><span class="arch-a">ブラウザ</span></div>
</div>

<p class="punch">「CだけでブラウザのSQLiteが完結している」<br>わけではない。</p>

<!--
⚡【10秒ひとこと要約】
「ブラウザで動くSQLiteも、CのコアをWASMにして、JavaScriptの接着剤と連携させることで実現しています」
--------------------------------------------------
想定: 35秒
【口頭トークガイド】
「『ブラウザでSQLiteが動く』と聞くと、『C言語のコードをそのままポイッとブラウザに投げ込んだら動いた』と思われがちです。
でも、実際の中身はそう単純ではありません」

「画面の図をご覧ください。
SQLite本体の巨大なCコード（sqlite3.c）を、WASM用の拡張ラッパー（sqlite3-wasm.c）で包み、Emscripten（エムスクリプテン）というツールでWebAssemblyに変換しています。
そしてブラウザ側では、JavaScriptのグルーコード（接着剤の役割をするバインディング）がメモリの受け渡しを仲介して、初めてWeb上でSQLが実行できるようになっています」

「つまり、C言語だけで完結しているのではなく、『C言語の強力なコア』と『JavaScriptの柔軟な制御』が手を取り合って動いているんです」

次への橋:
「ここで一つ、絶対に混同してはいけない『連携の仕組みの違い』を整理しておきましょう」

【補足メモ】
・amalgamation（アマルガメーション）: SQLiteの何十万行ものソースコードを、配布・ビルドしやすいように1つの巨大な `sqlite3.c` に結合したファイル形式。
・Emscripten（エムスクリプテン）: C/C++コードをWebAssembly + JSバインディングにコンパイルするオープンソースのツールチェーン。
-->

---
class: bleed mid
clicks: 1
---

# ただし、この2つは別の仕組み

<div class="worlds">

<div class="worlds-h">Web</div>
<div class="worlds-h">ネイティブ</div>

<div class="worlds-c">
<div class="w-node">JavaScript</div>
<div class="w-ar">↓　<span class="w-how">WebAssembly のインターフェース / グルー</span></div>
<div class="w-node lit">Cからコンパイルしたモジュール</div>
</div>

<div class="worlds-c">
<div class="w-tri"><span>Python</span><span>Node.js</span><span>Rust</span></div>
<div class="w-ar">↓　<span class="w-how">Python/C API・ctypes　/　Node-API　/　extern "C"</span></div>
<div class="w-node lit">Cライブラリ</div>
</div>

</div>

<p class="punch" v-click="1">つなぎ方は、相手ごとに別々。<br><span class="dim">Cは共通の接点になりやすい、くらいの話です。</span></p>

<p class="note" style="margin-top: 16px">ABIはOS・CPU・ツールチェーンごとに違う。<br>C言語そのものが、世界共通のABIを保証しているわけではない。</p>

<!--
⚡【10秒ひとこと要約】
「C言語は世界共通の魔法ではなく、Webでもネイティブでも『どの言語もC用の窓口を用意している』から共通の接点になれます」
--------------------------------------------------
想定: 40秒
【口頭トークガイド】
(1) クリック前:
「Webで動かす話と、ネイティブ環境で動かす話。どちらも『C言語をつないでいる』ように見えますが、実は技術的な仕組みは全く別物です」

「左の『Webの世界』では、ブラウザのセキュリティサンドボックスの中で動かすために、WebAssemblyの専用インターフェースとJavaScriptのグルーコードを経由します。
右の『ネイティブの世界』では、Pythonなら ctypes、Node.jsなら Node-API、Rustなら extern "C" というように、それぞれの言語が用意したCバインディング機構を使って直接メモリをつなぎます」

(2) 1クリック目（まとめパンチライン）:
「『C言語を使えば何でも自動でつながる魔法の共通規格がある』わけではありません。
正しくは、『どの言語・どのプラットフォームも、C言語とつなぐための専用の窓口を必ず用意してくれているから、C言語が一番共通の接点になりやすい』という現実的な話なんです」

次への橋:
「つまり、私たちが普段意識していなくても……こういう結論になります」

【補足メモ（技術的正確性・質問対策）】
・ABI（Application Binary Interface）: OS・CPU・コンパイラごとに規定されるバイナリレベルの呼び出し規約。世界共通の「CのABI」が存在するわけではなく、ターゲット環境ごとの規約に各言語が合わせている。
・Node-API: Node.jsのバージョンが上がってもバイナリ互換性を保つ公式のC API。
-->

---
class: bleed mid
---

<h1 class="say">Cを書くことだけが、<br>Cを使うことではない</h1>

<p class="lede">SQLiteを使うPythonのコードに、Cは1行も出てこない。<br>それでも、動いているのはCで書かれたコアです。</p>

<!--
⚡【10秒ひとこと要約】
「PythonからSQLiteを使うときCは1行も書きません。Cを書かなくても、私たちはすでにCのコアを使っています」
--------------------------------------------------
想定: 25秒
【口頭トークガイド】
「『C言語を書くことだけが、C言語を使うことではない』。
これが、1つ目のルート（既存資産を使う）の最も重要な結論です」

「私たちがPythonで `sqlite3.connect()` と書くとき、Pythonコードの中にC言語の構文は1行も出てきません。
でも、実際に高速で安全にディスクにデータを書き込んでいるのは、長年磨き抜かれたC言語のコアエンジンです。
『C言語の恩恵を受けるために、自分がC言語の達人になる必要はない』――すでに世界中にある素晴らしいCの資産に、モダンな言語から乗っかるだけで十分なんです」

次への橋:
「では、もう一つの『自分で新しくCでコアを書く』のは、一体どういう条件が揃ったときでしょうか？」

【発表メモ】
・ここで「1: 既にある資産を使う」の話を完全にクローズし、聴衆に安心感を与える（「あ、自分もCの恩恵受けてるんだ」と思わせる）。
・テンポよく次の「新しく書く条件」へバトンを渡す。
-->

---
class: bleed mid
clicks: 1
---

# 新しくCでコアを書くのは、別の判断

<div class="conds">
<span>OS・デバイス・プロトコルの境界に触る<small>USB機器、シリアル通信、自作プロトコル</small></span>
<span>C APIを要求するSDKや既存環境につなぐ<small>マイコンのSDK、既存アプリのプラグイン</small></span>
<span>ランタイムの依存を非常に薄くしたい<small>配布物を小さく、依存を増やさず</small></span>
<span>ネイティブとWASMなど、複数のターゲットへ持っていきたい<small>CLIとブラウザで同じ処理を動かす</small></span>
</div>

<div class="cost" v-click="1">
<div class="cost-k">増えるコスト</div>
<div class="cost-v">メモリ安全性　/　FFI　/　ビルド　/　所有権　/　デプロイ　/　デバッグ</div>
</div>

<p class="punch" v-click="1">条件が揃えば候補になる、というだけ。</p>

<p class="note lit" v-click="1" style="margin-top: 12px">Rust・C++・Goが適切な場面も当然ある。</p>

<!--
⚡【10秒ひとこと要約】
「新しくCでコアを書くのは、OS・ハード境界や極小配布など『条件が揃った時だけ』。コストも踏まえて冷静に選びます」
--------------------------------------------------
想定: 45秒
【口頭トークガイド】
(1) クリック前（4つの条件）:
「では、新しくC言語でコアを書くべきなのはどんな時でしょうか？ 私の中では主に4つの条件があります」

「1つ目は、USBやシリアル通信など『OSやハードウェアの境界に直接触る』とき。
2つ目は、マイコンやC言語のSDKしかない『制約のある環境につなぐ』とき。
3つ目は、重いランタイムを持ち込まず『配布サイズを究極に小さくしたい』とき。
そして4つ目は、先ほどのデモのように『同じ解析ロジックを、ネイティブCLIでもブラウザでもマルチに動かしたい』ときです」

(2) 1クリック目（増えるコストと冷静な判断）:
「ただし！ これらをやるには、メモリ管理、FFI（言語間連携）、ビルド環境など、確実に開発コストが増えます。
だから『何でもかんでもCで書こう』ではなく、これらの『条件がピタリと揃った時だけ、有力な選択肢（候補）として浮上してくる』。それだけのことなんです」

次への橋:
「ここまで見てきたC言語の姿を、一度きれいに3つの言葉で整理してみましょう」

【補足メモ（質問対策）】
・Rust/C++/Goとの比較: 新規開発でメモリ安全性が最優先ならRust、大規模オブジェクト指向ならC++、並行処理と開発生産性ならGoが優れた選択肢。それらを否定せず「C言語が光るピンポイントな境界領域」を定義する。
・FFI（Foreign Function Interface）: 異なるプログラミング言語間で関数を呼び出し合うためのインターフェース機構。
-->

---
class: bleed mid
clicks: 2
---

# 今日のCを、整理すると

<div class="recall">
<div class="recall-w" v-click="1">見える</div><div class="recall-s" v-click="1">バイト表現 / メモリ / 寿命<small>0x12345678 が 78 56 34 12 に見えた、あれ</small></div>
<div class="recall-w" v-click="1">持っていける</div><div class="recall-s" v-click="1">Cのソース → WebAssembly → ブラウザ<small>42 と 0x046D を返してきた、あれ</small></div>
<div class="recall-w" v-click="2">つながる</div><div class="recall-s" v-click="2">既存のCライブラリ / バインディング / ネイティブ連携<small>SQLiteと、その周りの仕組み</small></div>
</div>

<!--
⚡【10秒ひとこと要約】
「今日のCを整理すると、機械が『見える』、ブラウザへ『持っていける』、既存資産に『つながる』の3つです」
--------------------------------------------------
想定: 40秒
【口頭トークガイド】
(1) 1クリック目（「見える」「持っていける」）:
「今日皆さんと一緒に見てきたC言語の世界を、3つのキーワードで振り返ります」

「1つ目は『見える』。0x12345678 が 78 56 34 12 と並んでいたように、高水準言語が隠してくれるメモリやバイト表現が、そのまま目の前に見えました。
2つ目は『持っていける』。C言語で書いた小さな関数や解析ロジックが、WebAssemblyを通じて、そのままブラウザのJavaScriptから呼び出せました」

(2) 2クリック目（「つながる」）:
「そして3つ目は『つながる』。SQLiteのように、何十年も磨かれた世界中の資産が、PythonやNode.js、Rustなどのあらゆる言語と今なお強固につながっています」

「『見える』『持っていける』『つながる』。これが、現代において私たちが体験できるC言語のリアルな姿です」

次への橋:
「もちろん、これらを知ったからといって、明日から全ての開発をC言語にする必要はありません」

【発表メモ】
・新しい概念は一切出さず、前半と中盤で見せた具体例を3つの言葉に綺麗に回収する。
・テンポよくリズムに乗せて「見える」「持っていける」「つながる」とコールする。
-->

---
class: bleed mid
---

# もちろん、Cが常に正解ではない

<div class="alt">
<div class="alt-k">Webアプリ</div><div class="alt-v">TypeScriptでいい場面が多い</div>
<div class="alt-k">AI / データ</div><div class="alt-v">Pythonでいい場面が多い</div>
<div class="alt-k">新規のシステムコード</div><div class="alt-v">メモリ安全性が重要なら、Rust等を選ぶ理由は十分にある</div>
</div>

<p class="punch">それでも、機械・OS・デバイス・プロトコルに近づくとき、<br>既存のC資産につながるとき、<br>小さいコアを複数の環境へ持っていくとき。</p>

<!--
⚡【10秒ひとこと要約】
「WebならTS、AIならPython、新規ならRust。それでも、ハード境界や既存資産に触れるときCが輝きます」
--------------------------------------------------
想定: 30秒
【口頭トークガイド】
「もちろん、すべての場面でC言語が正解だとは絶対に言いません。
Webアプリを作るならTypeScriptが圧倒的に快適ですし、AIやデータ処理ならPythonの豊富なエコシステムを使うべきです。
新規にシステムコードを書く場合でも、メモリ安全性を最優先にするならRustを選ぶべき強い理由があります」

「それでも……機械やOS、ハードウェアのプロトコルに極限まで近づくとき。
世界中の巨大なC言語資産と手を取り合うとき。
そして、小さなコアロジックをブラウザやCLIなど複数の環境へ届けたいとき」

次への橋:
「だからこそ、今日最後に私が皆さんにお伝えしたいメッセージは、これです」

【補足メモ（質問対策: 「それRustでよくない？」への切り返し）】
・多くの新規開発においてRustは極めて強力な選択肢。ただし「既存のC資産・C ABIをそのまま使う場面」「ツールチェーンが限られた極小マイコン環境」「SQLiteのように完成されたコアを使う場合」は、依然としてC言語が最も無駄のない現実解になる。
-->

---
class: bleed spread
---

<div>

<h1 class="say closing-title">技術選定で、<br>最初からCを<br>候補外にしないでほしい</h1>

<p class="lede closing-sub">使うのは、既にあるCでいい。書くのは、小さなコアだけでいい。<br>AIで実装のコストが下がっても、どの抽象度を選ぶかは残ります。</p>

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

<p class="note lit" style="margin-top: 20px">このスライドは、あとから自分で触れます。デモもそのまま動きます。<br><span class="mono">https://otonasi-muonn.github.io/c-lang-lt-slidev/</span></p>

</div>

<!--
⚡【15秒ひとこと要約】
「使うのは既存のCでいい、書くのは小さなコアでいい。技術選定のとき、最初からCを候補外にしないでほしいです！」
--------------------------------------------------
想定: 40秒
【口頭トークガイド】
「『技術選定のとき、最初からC言語を選択肢から外さないでほしい』。
これが、今日私が一番伝えたかったメッセージです」

「全部をC言語で書く必要なんて全くありません。使うのは、世界中にある既存のC資産でいい。新しく書くにしても、小さなコア機能だけでいいんです。
AIの進化によって、コードを書くハードルそのものは劇的に下がりました。
しかし、『どの抽象度のレイヤーで課題を解くか』という技術選定の責任と面白さは、これからも私たちエンジニアの手に残り続けます」

「画面下の18バイト、冒頭では意味不明な数字の羅列に見えたかもしれませんが、今の皆さんなら『0x046D、ロジクールだな』と読めるはずです。
今日使ったスライドとブラウザ上のデモは、すべてこちらのURLで公開していますので、ぜひ手元で遊んでみてください。
ご清聴ありがとうございました！」

【発表メモ・通し時間管理】
・冒頭の18バイトを指し示し、「最初と最後で同じものを見ていても、知識によって意味が違って見える」という体験を鮮やかに回収して締める。
・通しの想定時間は約13分30秒〜14分（15分枠に対して約1分〜1分半の余裕）。焦らず堂々と締める。
・時間が足りない時の削り順: スライド19の語りを短縮 → スライド22の比較を早口に → スライド20のコスト説明を1点に絞る。
-->

---

<div class="k">USB 2.0</div>

<h1 class="compact">Appendix: 18バイトを受け取るまでの全工程</h1>

<div class="cols">
<div>

<h2>enumeration（時系列）<span class="faint">　ホスト ▶ ◀ デバイス</span></h2>

<div class="exch">
<div class="exch-n">1</div>
<div class="exch-out"></div>
<div><div class="exch-req">接続検出 → バスリセット</div><div class="exch-foot"><span class="exch-sub">Default / アドレス 0 / EP0 のみ</span></div></div>
<div class="exch-n">2</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">GET_DESCRIPTOR(Device, 8)</div><div class="exch-foot"><span class="exch-sub">offset 7 の <code>bMaxPacketSize0</code> を知る<br>（必要なら再リセット：ホスト実装依存）</span><span class="exch-ret ">◀ 8 B</span></div></div>
<div class="exch-n">3</div>
<div class="exch-out">▶</div>
<div><div class="exch-req">SET_ADDRESS(n)</div><div class="exch-foot"><span class="exch-sub">新しいアドレスは Status ステージ完了後に有効</span></div></div>
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
⚡【15秒ひとこと要約】
「USBの18バイトは、バスリセットやアドレス割り当てなど7段階の列挙（エニュメレーション）を経て届く、デバイスの最初の自己紹介です」
--------------------------------------------------
本編時間外（想定: 45〜60秒）
※「この18バイトって実際どうやって取るの？」と質問された場合に開く。

【口頭トークガイド】
「『この18バイトって、USB機器を挿したときにどうやって手元に届くの？』という補足です。
USB機器をPCに接続すると、OSとデバイスの間で『エニュメレーション（列挙）』という7段階の初期対話が自動で行われます。

左側の時系列を見ていただくと、いきなり18バイト全部を読むのではなく、
まずステップ2で先頭8バイトだけを読んでパケットサイズを確認し、
ステップ3で機器にアドレス（固有の番号）を割り当ててから、
ステップ4で初めて完全な18バイトのデバイスディスクリプタを取得しています。

そして右側の図にあるように、ディスクリプタは階層ツリー構造になっていて、
デバイス情報（18B）の下に、コンフィグレーション（9B）、インターフェース（9B）、エンドポイント（7B）がぶら下がっています」

【想定Q&A・技術深掘りメモ】
・Q: なぜ最初に8バイトだけ読むの？
  A: オフセット7にあるエンドポイント0の最大パケットサイズ（bMaxPacketSize0）をホストコントローラが知る必要があるため。主要OSの歴史的な実装慣習（USB 2.0仕様書§9.1.2自体には明示されていないが事実上の標準手順）。
・Q: Configuration以降のディスクリプタはどうやって取るの？
  A: 1つずつバラバラにリクエストするのではなく、Configurationの先頭9バイトで全体の長さ（wTotalLength）を確認し、その長さ分の巨大な1つの塊（連結ブロブ）として一括ダウンロードしてメモリ上で走査・パースします。
・Q: bNumInterfaces はディスクリプタの総数？
  A: 違います。インターフェース「番号」の数です。代替設定（Alternate Setting）が存在する場合、同じ番号に対して複数のInterface Descriptorが連なります。
-->

---

<h1 class="compact">Appendix: 18バイトの全フィールド</h1>

<div class="k">offset</div>

<div class="dump-head"><span>通信上のバイト列</span><span>C declaration</span><span>value</span></div>

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

<p class="note" style="margin-top: 14px; max-width: none">フィールドの対応表。受信したバイト列を <code>struct *</code> にキャストする実装例ではない。</p>

<!--
⚡【15秒ひとこと要約】
「18バイトの内訳です。規格バージョン、ベンダーID、プロダクトID、文字列への参照番号などが整然と並んでいます」
--------------------------------------------------
本編時間外（想定: 40〜50秒）
※「18バイトの残りの欄には何が入ってるの？」と質問された場合に開く。

【口頭トークガイド】
「『18バイトの残りのデータには何が入っているの？』という補足です。
オフセット0から順に、全体の長さ18（bLength）、ディスクリプタ種別1（bDescriptorType）、USB規格バージョン（bcdUSB: 0x0200＝USB 2.0）と並んでいます。

そして本編で取り上げたオフセット8〜11の『ベンダーID（Logitech）』と『プロダクトID（Unifyingレシーバー）』があり、
その先にはデバイスのバージョン（bcdDevice）、そしてメーカー名や製品名の文字列ディスクリプタを指すインデックス番号（iManufacturer, iProduct）が格納されています。
文字列そのものが直書きされているのではなく、参照番号になっているのがポイントです。

ただし画面下の注記にもある通り、このC言語の構造体は『フィールドの対応表』であって、
届いた生データをそのままこの構造体にキャストして読むのはNGです。その理由は次のスライドでお話しします」

【想定Q&A・技術深掘りメモ】
・Q: bcdUSB や bcdDevice の "bcd" って何？
  A: Binary Coded Decimal（2進化10進数）の略です。0x0200 は16進数の512ではなく、上位バイトがメジャー、下位バイトがマイナーを表し「USB 2.00」という意味になります。
・Q: なぜ文字列（"Logitech" など）がここに入っていないの？
  A: デバイスディスクリプタを固定長（18バイト）に保つためです。文字列は可変長で多言語（英語、日本語など）対応が必要なため、別の String Descriptor として切り離され、ここではインデックス番号（ID）だけで参照します。
・Q: なぜ構造体にキャストして読まないの？
  A: 次のスライド（パディング問題）に加えて、エンディアン変換の欠落、未アライメントアクセス違反（ARM等のSIGBUS）、コンパイラ依存のメモリ配置の差異を避けるためです。
-->

---

<div class="k">ABI</div>

<h1 class="compact">Appendix: 通信上の長さと <code>sizeof</code></h1>

<div class="abi" style="margin-top: 8px">
<div class="abi-name">Device</div><div class="abi-lab">通信上</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">18</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">18</div><div class="abi-note ">たまたま一致</div>
<div class="abi-gap"></div>
<div class="abi-name">Configuration</div><div class="abi-lab">通信上</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div><div class="abi-num">10</div><div class="abi-note sig">末尾のパディング 1</div>
<div class="abi-gap"></div>
<div class="abi-name">Interface</div><div class="abi-lab">通信上</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">9</div><div class="abi-note ">たまたま一致</div>
<div class="abi-gap"></div>
<div class="abi-name">Endpoint</div><div class="abi-lab">通信上</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span></div><div class="abi-num">7</div><div></div>
<div></div><div class="abi-lab">sizeof</div><div class="cellrow"><span></span><span></span><span></span><span></span><span></span><span></span><span></span><span class="pad"></span></div><div class="abi-num">8</div><div class="abi-note sig">末尾のパディング 1</div>
</div>

<p class="punch" style="margin-top: 22px; font-size: 20px">進む基準は通信上の長さ。<br><span class="dim">ただし信頼できない入力では、その長さ自体も検証する。</span></p>

<p class="note" style="margin-top: 14px">C 規格はこの <code>sizeof</code> を保証しない。<br>典型的な ABI の実演であって、通信上のフォーマットの定義ではない。</p>

<!--
⚡【15秒ひとこと要約】
「構造体のsizeofと通信サイズが一致するのは単なる偶然。パディング事故や入力改ざんを防ぐため、1バイトずつ検証して組み立てます」
--------------------------------------------------
本編時間外（想定: 50〜60秒）
※「なんで構造体キャストじゃダメなの？」「パディングって他でも起きるの？」と聞かれた場合に開く。

【口頭トークガイド】
「本編のスライド9で『エンドポイントは7バイトなのに構造体は8バイトになる』とお話ししましたが、他のディスクリプタと並べた一覧がこちらです。

デバイス（18B）やインターフェース（9B）は、通信上の長さと構造体の sizeof がたまたま一致しています。
しかし、これはあくまで『偶然一致しているだけ』です。
コンフィグレーションは9バイトなのに10バイト、エンドポイントは7バイトなのに8バイトと、末尾に1バイトのパディング（隙間）が勝手に差し込まれます。
もし『全部構造体にキャストして読めばいいや』と安易にやると、パディングのせいで後続のデータが1バイトずつズレて即座にバグります。

さらに重要なのが、画面下のパンチラインです。
外部からUSB経由で届くデータは『攻撃者が自由に偽装できる信頼できない入力（untrusted input）』です。
ディスクリプタに書かれている長さ（bLength）自体を鵜呑みにせず、受信バッファの残りサイズと突き合わせて検証しながら1バイトずつ安全にパースするのが、堅牢なシステムプログラミングの鉄則です」

【想定Q&A・技術深掘りメモ】
・Q: #pragma pack(1) や __attribute__((packed)) でパディングを消せばいいのでは？
  A: コンパイラ依存で移植性を失うだけでなく、アライメント（CPUがメモリアドレスを偶数境界で読み取る制約）が崩れます。x86では低速化で済みますが、ARM等のアーキテクチャでは非アライメントアクセスで即座にSIGBUS例外（クラッシュ）を起こすリスクがあります。
・Q: バッファオーバーランはどう防ぐ？
  A: パースのループで必ず `bLength` が最小長（ヘッダの2バイト）以上かつ受信残量 `remain` 以下であるか（`n < 2 || n > remain`）を検証してからポインタを進めます:
     ```c
     while (remain >= 2) {
       uint8_t n = p[0];
       if (n < 2 || n > remain) break; // 長さの正当性を検証
       p += n; remain -= n;
     }
     ```
・Q: 構造体キャストがダメな理由の総まとめ:
  ①パディングによるオフセットのズレ
  ②リトル/ビッグエンディアン変換がされない
  ③アライメント違反によるクラッシュ・速度低下
  ④C言語規格上の Strict Aliasing Rule（有効型規則）違反
-->

---
class: mid
---

<div class="k">§6.3.1.8</div>

<h1 class="compact">Appendix: 型は、ただの名前じゃない</h1>

<BitWidthDemo />

<!--
⚡【15秒ひとこと要約】
「C言語の型は単なるラベルではなく、CPUのレジスタ幅や符号拡張・整数拡張といった計算規則そのものを定義しています」
--------------------------------------------------
本編時間外（想定: 45〜60秒）
※「型って何でそんなに細かく指定するの？」「unsignedとsignedで何が変わるの？」と聞かれた場合に開く。

【口頭トークガイド】
「『C言語の型って何が特別なの？』という補足です。
高水準言語では、型は単に『数値が入る箱』程度の意識で書けますが、C言語では『メモリ上で何ビットを占有し、CPUがそれを符号あり（signed）として解釈するか、符号なし（unsigned）として解釈するか』という厳格な規則（Usual Arithmetic Conversions: 通常の算術変換）が存在します。

このデモでビット幅を切り替えてみると分かりますが、
例えば同じ `0xFF` という1バイトでも、`uint8_t` なら 255 ですが、`int8_t`（符号あり）なら -1 になります。
これを16ビットや32ビットに拡張（符号拡張）したとき、
unsignedなら単に上にゼロが詰まりますが、signedだと最上位ビットの1がズラーッと上までコピーされて `0xFFFFFFFF` になります。

さらに、C言語には『計算するときは小さい整数を一旦 int に広げてから計算する（整数拡張）』というルールもあります。
型を理解することは、CPUがデータをどう読み取り、どう計算しているかを直接制御することそのものなんです」

【想定Q&A・技術深掘りメモ】
・Q: 整数拡張（Integer Promotion）って何？
  A: C言語の基本仕様（C11 §6.3.1.1）。`char` や `short` など `int` より小さい型は、式の中で評価される際に自動的に `int`（表現できなければ `unsigned int`）に昇格されます。例えば `uint8_t a = 0xFF; ~a` を実行すると、反転結果は 0x00 ではなく 32ビットの `~0x000000FF = 0xFFFFFF00`（マイナスの値）になり、意図せぬバグの温床になります。
・Q: 符号付き整数のオーバーフローはどうなる？
  A: `unsigned` のオーバーフローは定義された安全なラップアラウンド（2のn乗の剰余）ですが、`signed` のオーバーフローはC言語規格上『未定義動作（Undefined Behavior）』です。コンパイラの最適化によって、オーバーフロー検査コードそのものが「起きない前提」で消去される危険があります。
-->

---
class: bleed mid
---

<h1 class="say">Cは「C++から機能を減らした言語」<br>ではない。</h1>

<p class="lede">CにはCの都合、Cの設計、Cの進化がある。</p>

<p class="punch mono" style="margin-top: 40px"><span class="faint">C99 </span>restrict<span class="faint">　　C11 </span>_Generic<span class="faint">　　C99 </span>designated initializer</p>

<!--
⚡【15秒ひとこと要約】
「CはC++の劣化版ではなく、メモリ重複排除（restrict）や型ジェネリクス（_Generic）など独自の哲学で進化し続ける別言語です」
--------------------------------------------------
本編時間外（想定: 45〜60秒）
※「C言語とC++って何が違うの？」「C++で書けばよくない？」と聞かれた場合に開く。

【口頭トークガイド】
「よくある誤解として、『C言語って、C++からオブジェクト指向などの便利機能を抜いただけの劣化版（サブセット）でしょ？』と言われることがあります。これは明確に間違いです。
C言語とC++は、設計思想も進化のベクトルも異なる『完全に別の兄弟言語』です。

画面下にある3つの機能を見てください。
例えば、C99で導入された `restrict` キーワード。これは『2つのポインタが同じメモリ領域を絶対に指していない（重複しない）』とコンパイラに宣言するもので、極限のメモリアクセス最適化やSIMDベクトル化を可能にします。これは長年C++規格には存在しませんでした。
また、C11で追加された `_Generic` は、マクロを使って引数の型に応じた関数呼び出しをコンパイル時に分岐させる、C言語流のミニマルな型ジェネリクスです。

C言語は機能を増やして重くするのではなく、『薄い抽象化で、ハードウェアの最高性能を直接引き出す』という独自の美学を持って今も進化し続けています」

【想定Q&A・技術深掘りメモ】
・Q: C++でC言語のコードをそのままコンパイルできる？
  A: できません。例えば `void *` から他ポインタ型への暗黙の型変換（`malloc` の戻り値代入など）はCでは合法ですがC++ではエラーになります。また変数名に `class` や `template`、`new` 等のC++予約語が使えないなど、文法レベルで非互換です。
・Q: restrict の威力はどれくらい？
  A: ポインタ経由のメモリ読み書きループで、コンパイラが「片方のポインタへの書き込みによって、もう片方のポインタの指す値が変わるかもしれない（エイリアシング）」と疑わずに済むため、レジスタに乗せたまま一気にSIMD命令で処理できます。画像処理や行列計算で数倍の速度差が出ることもあります。
・Q: designated initializer（指示付き初期化子）とは？
  A: `struct Point p = { .x = 10, .y = 20 };` のように、構造体のメンバ名を明示して初期化する記法。メンバの順序変更に強く可読性が高いため、Linuxカーネルなど巨大なCコードベースで標準的に使われています（C++にはC++20でようやく導入されました）。
-->
