# C言語LT Slidev Deck

ハックツコミュ「自分の推し技術について語りたいよねの会」向け、15分セッション用のSlidev資料。

## コンセプト

**AI時代に、なぜ今さらC言語なのか。**

USB、WASM、型変換などを入口に、C言語を「古い低級言語」ではなく「コンピュータの境界面に立てる言語」として見せる。

## 開発

```bash
npm install
npm run dev
```

## オンライン発表メモ

- Discord画面共有では、ブラウザのSlidev画面を共有する
- 聴衆にその場で操作してもらう前提にはしない
- インタラクティブ要素は登壇者が操作して見せる
- デモが壊れても進行できるよう、各デモは説明だけでも成立させる
- 公開後はGitHub Pagesで「触れる資料」として見てもらう

## デプロイ

`package.json` の `build` の `--base` は、公開リポジトリ名に合わせて変更してください。

```bash
npm run build
```

GitHub Pagesを使う場合は `.github/workflows/deploy.yml` を利用できます。
