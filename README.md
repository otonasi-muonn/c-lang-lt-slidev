# C言語LT Slidev Deck

ハックツコミュ「自分の推し技術について語りたいよねの会」向け、15分セッション用のSlidev資料。

## コンセプト

**AI時代に、なぜ今さらC言語なのか。**

普段はTypeScriptを使う立場から、Cが何のために作られ、何が面白く、どういう条件なら
2026年の技術選定に戻ってくるのかを、実際に動くコードと実在するソフトウェアで見せる。

本編23枚 / 38 presentation state、想定およそ14分。Appendix 5枚は質問が出たときだけ開く。

話の順番そのものが主張になっている。詳しくは `docs/design-brief.md`。

- 前半は「Cの何が面白いのか」。`uint32_t x = 0x12345678` を1バイトずつ観測して
  little-endian に名前を付け、その知識だけでUSB Device Descriptorの2バイトから
  実在するvendor IDを読む。
- 中盤で代償を隠さない。padding、lifetime、そしてmemory safetyの現実。
- 後半は「じゃあいつ選ぶのか」。**既存のC資産を使う**話と**新しく小さいcoreを書く**話を
  最後まで分けて扱う。
- 「見える・持っていける・つながる」という整理は最後に初めて出す。冒頭では配らない。

## デモ

実際にCからコンパイルしたWebAssemblyを2つ使う。fakeデモは置かない。

| モジュール | ソース | 役割 |
| --- | --- | --- |
| `double_it.wasm` (77 B) | `wasm/double_it.c` | 「CのfunctionをJSから呼べる」というmental modelだけを作る |
| `usb_descriptor.wasm` | `wasm/usb_descriptor.c` | 前半で人間が読んだ18バイトを、同じC実装が読む |

`double_it` はロードに失敗したらボタンが無効になり、その旨を表示する。JSで計算して
Cが動いたように見せることはしない。`usb_descriptor` はJSフォールバックを持つが、その場合は
バッジが「JS フォールバック」に変わる。どちらの場合も、動いていないものを動いたとは言わない。

WASMのビルドには wasi-sdk 25.0 が要る。

```bash
WASI_SDK=/path/to/wasi-sdk npm run build:wasm
```

## 開発

```bash
npm ci
npm run dev
```

## QA

レンダリング結果を見ずに完成とみなさない。ビルド済みサイトに対して、全presentation state を
1920x1080 でキャプチャし、はみ出し・小さすぎる文字・console error・両デモの実動作・
フォールバック表示の正直さ・キーボード送りを検査する。

```bash
npm run build
python output/playwright/serve_dist.py 4173 &
python output/playwright/qa_deck.py
```

スクリーンショットと `qa-results.json` は `output/playwright/` に出る。
このディレクトリはローカルの `.git/info/exclude` で除外されているため、
QAハーネス自体はコミットされていない。

## オンライン発表メモ

- Discord画面共有では、ブラウザのSlidev画面を共有する
- 聴衆にその場で操作してもらう前提にはしない
- インタラクティブ要素は登壇者が操作して見せる
- デモが壊れても進行できるよう、各デモは説明だけでも成立させる
- 公開後はGitHub Pagesで「触れる資料」として見てもらう

## デプロイ

このリポジトリの公開先は `https://otonasi-muonn.github.io/c-lang-lt-slidev/`。`package.json` の `build` は GitHub Pages のサブパスに合わせて `--base /c-lang-lt-slidev/` を指定している。フォークなどで公開リポジトリ名を変える場合は、この `--base` も変更してください。

スライド番号付きURLを共有しても GitHub Pages の深いパスで 404 にならないよう、ビルド時は hash ルーティングを使う（例: `#/7`）。

```bash
npm run build
```

GitHub Pages の公開元を GitHub Actions に設定すると、main への push で `.github/workflows/deploy.yml` が `npm ci`、ビルド、デプロイを実行する。
