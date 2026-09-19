# USB説明：差し込み用ブロック

`SLOT:USB-ACCURACY` に入れる素材。15分LTでは**必須の独立スライドは2枚**に留める。構造体の差し替えは既存のコードスライド内の断片なので、枚数を増やさない。Appendixは質問が出たときだけ開く。

## 配置と優先度

| 優先度       | ブロック                                     | 入れる場所                                         | 想定枚数 |
| ------------ | -------------------------------------------- | -------------------------------------------------- | -------- |
| 必須         | M0: Device Descriptorの構造体                | `UsbDeviceDescriptor` を見せる既存コード部分と置換 | 単独0枚  |
| 必須         | M1: enumeration と階層                       | USB導入の直後。`型は、ただの名前じゃない` の前     | 1枚      |
| 必須         | M2: `sizeof != bLength`                      | M1の直後。Cの「実体」に戻る山場                    | 1枚      |
| 余裕があれば | A1: 生バイト列を `struct *` にキャストしない | M2の直後、またはAppendix                           | 1枚      |
| Appendix     | A2: 18バイトの全デコード                     | 最終スライドの後                                   | 1枚      |

## M0 — Device Descriptorは18バイト（必須・単独0枚）

**入れる場所:** 既存の `# ただのバイト列が、構造体になる` にある `UsbDeviceDescriptor` のコードを、次で丸ごと置換する。これはフィールド一覧を説明するための構造体であり、受信バッファをこの型にキャストして読む実装例ではない。

```c
typedef struct {
    uint8_t  bLength;             // offset 0
    uint8_t  bDescriptorType;     // 1
    uint16_t bcdUSB;              // 2
    uint8_t  bDeviceClass;        // 4
    uint8_t  bDeviceSubClass;     // 5
    uint8_t  bDeviceProtocol;     // 6
    uint8_t  bMaxPacketSize0;     // 7
    uint16_t idVendor;            // 8
    uint16_t idProduct;           // 10
    uint16_t bcdDevice;           // 12
    uint8_t  iManufacturer;       // 14
    uint8_t  iProduct;            // 15
    uint8_t  iSerialNumber;       // 16
    uint8_t  bNumConfigurations;  // 17
} UsbDeviceDescriptor;            // wire format: 18 bytes
```

<div class="mt-3 text-sm opacity-75">
<code>iManufacturer</code> / <code>iProduct</code> / <code>iSerialNumber</code> はString Descriptorへのindex。0は「文字列なし」。<br>
末尾の <code>bNumConfigurations</code> が、Configurationが複数あり得る入口になる。
</div>

**口に出す言葉:** 「ここでは18バイトを、18バイトとして読まないといけない。末尾4バイトは飾りではない。文字列はindexで横に飛び、Configurationは複数持てる。」

---

## M1 — USB: 「時系列」と「木」は別（必須・1枚）

**入れる場所:** USB導入の直後、M0の前後どちらでもよい。M0をこの直後に置くなら、M1では構造体コードを再掲しない。

```md
<!-- SLOT:USB-ACCURACY:MAIN-1 -->

---

layout: two-cols
---

# USB: 「時系列」と「木」は別

::left::

## enumeration（時系列）

<div class="text-sm leading-relaxed space-y-2">
  <div>接続検出 → バスリセット<br><span class="opacity-65">Default / address 0 / EP0</span></div>
  <div><code>GET_DESCRIPTOR(Device, 8)</code><br><span class="opacity-65">offset 7の <code>bMaxPacketSize0</code> を知る</span></div>
  <div class="opacity-65">（必要なら再リセット：これはホスト実装依存）</div>
  <div><code>SET_ADDRESS(n)</code><br><span class="opacity-65">新しいaddressはStatusステージ完了後に有効</span></div>
  <div><code>GET_DESCRIPTOR(Device, 18)</code></div>
  <div><code>GET_DESCRIPTOR(Configuration, 9)</code><br><span class="opacity-65"><code>wTotalLength</code> を読む</span></div>
  <div><code>GET_DESCRIPTOR(Configuration, wTotalLength)</code><br><span class="opacity-65">連結されたdescriptor群を一括取得</span></div>
  <div><code>SET_CONFIGURATION(bConfigurationValue)</code><br><span class="opacity-65">Configured。0ならAddress状態へ戻る</span></div>
</div>

::right::

## descriptor（階層）

<pre class="text-sm leading-relaxed"><code>Device (18B)
└─ Configuration (9B) × bNumConfigurations
   └─ Interface (9B) × bNumInterfaces
      ├─ Endpoint (7B) × bNumEndpoints
      └─ クラス固有Descriptor（HID / CDC …）</code></pre>

<div class="mt-4 text-sm leading-relaxed opacity-80">
alternate settingは同じinterface番号の別Descriptor。<br>
String Descriptorは木の外。各<code>i*</code> indexから横参照する。<br>
EP0にはEndpoint Descriptorがない。だから<code>bMaxPacketSize0</code>はDevice側にある。
</div>

<div class="mt-5 rounded-xl bg-yellow-300/10 border border-yellow-300/30 p-3 text-sm">
<code>GET_DESCRIPTOR</code> はリクエスト種別。木の頂点ではない。
</div>
```

**口に出す言葉:** 「左は起きた順、右は返ってきたデータの形。混ぜると、`GET_DESCRIPTOR` が親に見えてしまう。Configuration以下は順番に別々に取るのではなく、長さを読んでから一つの連結ブロブとして取る。」

**注記:** 先頭8バイトを読んでから再リセットする流れは、Windows/Linuxなどで見られる代表的なホスト実装の流れであり、全ホストへ強制する一本の手順ではない。USB 2.0 §9.1.2は複数の初期化シーケンスを許すため、スライド上も「ホスト実装依存」と明記する。

---

## M2 — `bLength` を信じろ。`sizeof` を信じるな。（必須・1枚）

**入れる場所:** M1の直後。`GET_DESCRIPTOR(Configuration, 9)` → `wTotalLength` の二段階取得を受けて、「なぜwire formatの長さを使うのか」をCの話として回収する。

```md
<!-- SLOT:USB-ACCURACY:MAIN-2 -->

---

# <code>bLength</code> を信じろ。<code>sizeof</code> を信じるな。

<table class="mt-6 w-full text-left text-sm">
  <thead><tr class="border-b border-white/20"><th>Descriptor</th><th>wire上の <code>bLength</code></th><th>よくあるABIでの <code>sizeof</code></th></tr></thead>
  <tbody>
    <tr><td>Device</td><td>18</td><td class="text-green-300">18 — たまたま一致</td></tr>
    <tr><td>Configuration</td><td>9</td><td class="text-red-300">10 — 末尾padding 1</td></tr>
    <tr><td>Interface</td><td>9</td><td class="text-green-300">9 — たまたま一致</td></tr>
    <tr><td>Endpoint</td><td>7</td><td class="text-red-300">8 — 末尾padding 1</td></tr>
  </tbody>
</table>

<div class="grid grid-cols-2 gap-4 mt-7 text-sm">
<div class="rounded-xl bg-white/5 p-4">
  <code>uint16_t</code> のalignmentが2のABIを例にする。<br>
  Deviceの16-bit fieldはoffset 2 / 8 / 10 / 12。末尾は18なのでpaddingなし。<br>
  Configurationは9、Endpointは7で終わるため、それぞれ偶数境界まで1埋まる。
</div>
<pre class="rounded-xl bg-black/50 p-4 text-xs"><code>while (remain >= 2) {
  uint8_t n = p[0];
  if (n < 2 || n > remain) break;
  // p[1]はtype、pからn bytesを解釈
  p += n;
  remain -= n;
}</code></pre>
</div>

<div class="mt-6 text-xl text-center">
Configurationは <code>wTotalLength</code> bytes の連結ブロブ。<br>
1バイトずれる <code>p += sizeof(*desc)</code> で、以降が全部壊れる。
</div>

<div class="mt-3 text-center text-sm opacity-65">
C規格はこの<code>sizeof</code>を保証しない。ここでの数値は「典型ABIの実演」であってwire formatの定義ではない。
</div>
```

**口に出す言葉:** 「Deviceで18と出るのは正解ではなく、偶然。Endpointは7が8になる。同じUSBのdescriptorなのに、合うものと合わないものが混ざる。だからポインタを進める基準はCの都合ではなく、wire上の`bLength`。」

---

## A1 — 生バイト列を `struct *` にキャストしない（余裕があれば・1枚）

**入れる場所:** M2の直後。15分ではAppendix送りでよい。項目は6個に止め、各項目を深掘りしない。

````md
<!-- SLOT:USB-ACCURACY:APPENDIX-CAST -->

---

# `(Desc *)buf` は「読めた」だけで、正しくない

<div class="grid grid-cols-2 gap-4 mt-6 text-sm leading-relaxed">
  <div class="rounded-xl bg-red-300/10 p-4"><b>エンディアン</b><br>wireはlittle-endian。<code>6D 04</code>は<code>0x046D</code>。BE機でそのまま読むと逆になる。</div>
  <div class="rounded-xl bg-red-300/10 p-4"><b>アライメント</b><br><code>uint8_t[]</code>は<code>Desc</code>に必要なalignmentを保証しない。足りないアドレスへの変換はUB。</div>
  <div class="rounded-xl bg-red-300/10 p-4"><b>padding</b><br>wireの7 bytesとCの<code>sizeof == 8</code>は別物。進める長さが壊れる。</div>
  <div class="rounded-xl bg-red-300/10 p-4"><b>effective type / alias</b><br>宣言済みの<code>uint8_t[]</code>を、互換でないstruct lvalueとして読むのはUB。</div>
  <div class="rounded-xl bg-red-300/10 p-4"><b><code>packed</code>は解決策ではない</b><br>非標準で方言ごとに違う。paddingを消しても、未アラインのmember access問題は残る。</div>
  <div class="rounded-xl bg-green-300/10 p-4"><b>byteから組み立てる</b><br>wireの意味をコードに書く。読める環境に偶然依存しない。</div>
</div>

```c
static uint16_t le16(const uint8_t p[2]) {
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}
```
````

**口に出す言葉:** 「x86で読めても、Cとして正しいとは限らない。Cでは『メモリを見られる』ぶん、バイト列をどういう値として読むかも自分で決める。」

**注記:** 実アドレスがたまたま`Desc`のalignmentを満たせば、変換だけによるalignment UBは避けられる。`uint8_t[]`が保証しない、というのが正確な主張であり、「偶数アドレスでも必ずalignment UB」ではない。なお、上の`le16`は各項を`uint16_t`へ明示変換してからshiftする。`p[1] << 8`だけでは、16-bit `int`環境で符号付きshiftの問題を持ち得る。

---

## A2 — 18バイトを全部読む（Appendix・1枚）

**入れる場所:** Appendix。M0の構造体を見せた直後にデモをするなら、A1と入れ替えてもよい。

```md
<!-- SLOT:USB-ACCURACY:APPENDIX-DECODE -->

---

# 18 bytes。逆から読まない。

<pre class="mt-5 rounded-xl bg-black/60 p-4 text-lg"><code>12 01 00 02 00 00 00 08  6D 04 2B C5 00 12 01 02 00 01</code></pre>

<div class="mt-3 text-sm opacity-70">
実機の生ダンプではない。実在するVID/PID（Logitech <code>0x046D</code> / Unifying Receiver <code>0xC52B</code>）で組んだ説明用の現実的な例。
</div>

<table class="mt-5 w-full text-left text-xs leading-relaxed">
  <thead><tr class="border-b border-white/20"><th>offset</th><th>bytes</th><th>field</th><th>値</th></tr></thead>
  <tbody>
    <tr><td>0</td><td>12</td><td>bLength</td><td>18</td></tr>
    <tr><td>1</td><td>01</td><td>bDescriptorType</td><td>Device</td></tr>
    <tr><td>2</td><td>00 02</td><td>bcdUSB</td><td>0x0200 → BCD 2.00</td></tr>
    <tr><td>4</td><td>00</td><td>bDeviceClass</td><td>0 → classはInterface側</td></tr>
    <tr><td>5</td><td>00</td><td>bDeviceSubClass</td><td>0</td></tr>
    <tr><td>6</td><td>00</td><td>bDeviceProtocol</td><td>0</td></tr>
    <tr><td>7</td><td>08</td><td>bMaxPacketSize0</td><td>8 bytes</td></tr>
    <tr><td>8</td><td>6D 04</td><td>idVendor</td><td>0x046D (Logitech)</td></tr>
    <tr><td>10</td><td>2B C5</td><td>idProduct</td><td>0xC52B (Unifying Receiver)</td></tr>
    <tr><td>12</td><td>00 12</td><td>bcdDevice</td><td>0x1200 → BCD 12.00</td></tr>
    <tr><td>14</td><td>01</td><td>iManufacturer</td><td>String #1</td></tr>
    <tr><td>15</td><td>02</td><td>iProduct</td><td>String #2</td></tr>
    <tr><td>16</td><td>00</td><td>iSerialNumber</td><td>なし</td></tr>
    <tr><td>17</td><td>01</td><td>bNumConfigurations</td><td>1</td></tr>
  </tbody>
</table>
```

**口に出す言葉:** 「見えているのは`6D 04`。意味は`0x046D`。この反転を自分で書くか、CPUとコンパイラの偶然に任せるかが、Cの境界面。」

---

## 検算結果と、渡された前提からの訂正

### offset / size の通し計算

Device Descriptorは `1 + 1 + 2 + 1 + 1 + 1 + 1 + 2 + 2 + 2 + 1 + 1 + 1 + 1 = 18`。したがってoffsetは順に `0, 1, 2, 4, 5, 6, 7, 8, 10, 12, 14, 15, 16, 17` で、末尾は18になる。

Configuration Descriptorは `1 + 1 + 2 + 1 + 1 + 1 + 1 + 1 = 9`、Interface Descriptorは `1 × 9 = 9`、Endpoint Descriptorは `1 + 1 + 1 + 1 + 2 + 1 = 7`。いずれもUSB 2.0 SpecificationのTable 9-8 / 9-10 / 9-12 / 9-13と一致する。

`uint16_t`のalignmentが2で、提示順に素直なstructを置く**代表的なABI**なら、Deviceは16-bit fieldがoffset 2 / 8 / 10 / 12に全て収まり、object extent 18も2の倍数なので`sizeof == 18`。Configurationはextent 9を2へround upして10、Endpointは7を8、全fieldが`uint8_t`のInterfaceは9になる。ただしCはメンバpadding・末尾padding・alignmentを実装に委ねるため、これを全C処理系の保証としては言えない。

### 訂正が必要な点

- `0x0210`のBCD表記は **2.10**。値として2.1と同じでも、仕様に沿う表示は2.10であり、hexの下位`0x10`を「16」と読む誤りを防げる。
- USB 2.0の`bMaxPacketSize0`はpacket sizeそのもの（8 / 16 / 32 / 64）。**9 = 2^9 = 512** はSuperSpeed（USB 3.x）のDevice Descriptorでの符号化であり、USB 2.0の説明へ混ぜない。A2の`08`はUSB 2.0で8 bytes。
- 「`uint8_t[]`をcastしたら、アドレスが偶数でも必ずalignment UB」は誤り。実アドレスが対象型に必要なalignmentを満たすならalignmentだけのUBはない。ただし配列型からはそのalignmentが保証されず、endian / padding / effective typeの問題も残る。
- `p[0] | (p[1] << 8)`は、16-bit `int`まで含めて厳密に移植するなら不十分。A1のようにshift前に`uint16_t`へcastする。
- `bNumInterfaces`はalternate settingのDescriptor総数ではなく、interface番号の数。alternate settingがあるとInterface Descriptorは追加され得る。
- 「byteから明示的に組み立てるのが唯一移植的に正しい」は強すぎる。安全なbyte-wise decoder（または同等に境界・endian・alignmentを処理する実装）が必要、という言い方にする。

### 参照した規格箇所

- USB 2.0 Specification §9.1.2、Table 9-8 (Device Descriptor)、Table 9-10 (Configuration)、Table 9-12 (Interface)、Table 9-13 (Endpoint)
- ISO C11 §6.2.6.1（object representation / padding）、§6.3.2.3p7（異なるobject pointer型への変換とalignment）、§6.5p7（lvalue accessとeffective type）
