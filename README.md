# C言語LT Slidev Deck

ハックツコミュ「自分の推し技術について語りたいよねの会」向け、15分セッション用のSlidev資料。

## コンセプト

**AI時代に、なぜ今さらC言語なのか。**

普段はTypeScriptを使う立場から、Cの「見える・持っていける・つながる」を見せる。本編13枚、想定13分30秒＋操作・間の余裕1分30秒。USBのbytesはケーススタディとし、WASMデモと既存Cライブラリへの接点を通して「技術選定で、最初からCを候補外にしない」へつなげる。技術的な詳細はspeaker notesとAppendixへ置く。

## 開発

```bash
npm ci
npm run dev
```

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
