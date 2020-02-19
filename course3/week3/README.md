# Part 24: Huffman Codes

## Introduction and Motivation

- Binary Codes
  - アルファベット Σ の各文字を binary string にマップする
  - 5 bit の binary string で 32 種類表すことができる
  - Can we do better?
    - Yes. もし使用頻度の高いものと低いものがあるならば、可変長のコードを利用して、よりよくできる
- Ambiguity
  - Σ = {A, B, C, D} を考える
  - 固定長で {00, 01, 10, 11} で表せる
  - 一方、可変長で {0, 01, 10, 1} と表すとする。しかし、この場合、"001" と情報が送られた時、AB なのか AAD なのかわからない
- Prefix-Free Codes
  - problem
    - 可変長の場合、文字の切れ目がわからない
  - solution
    - Prefix-free codes
      - すべてのペア i, j ∈ Σ において、f(i), f(j) がどちらももう片方の prefix となっていないようなもの
    - 例
      - {0, 10, 110, 111}
  - Why useful?
    - より短い長さで表現することができる
    - 例: A が 60%, B が 25 %, C が 10%, D が 5% で現れるとする
      - 固定長だと平均 2 文字
      - {0, 10, 110, 111} で表したとすると、0.6・1 + 0.25・2 + 0.1・3 + 0.05・3 = 1.55 となる

## Problem Definition

- Codes as Trees
  - goal
    - 与えられた文字列の出現頻度の集合に対して、ベストな binary prefix-free encoding を返すこと
  - useful fact
    - binary codes <-> binary trees
    - 資料の図がわかりやすい
- Prefix-Free Codes as Trees
  - in general
    - 左側の子どもなら 0、右側の子どもなら 1
    - すべての i ∈ Σ に対して、1 つの "i" とラベル付されたノードが対応する
    - Encoding of i ∈ Σ <-> root から node "i" までのパスに沿った bit が対応している
    - Prefix-free <-> Labeled nodes = the leaves
  - to decode
    - root から葉に到達するまで、繰り返し path を辿っていく
  - note
    - encoding i の長さは depth of i in tree に対応する
- Problem Definition
  - input
    - 各文字列 i ∈ Σ に対して、確率 pi が与えられる
  - notation
    - average encoding length L(T) = Σ(i∈pi) pi・[depth of i]
  - output
    - この average encoding legth が最小化されるような tree T を出力する

## A Greedy Algorithm

- Building a Tree
  - natural but suboptimal idea
    - top-down に分割統治を行っていく
    - Σ を Σ1, Σ2 が約 50% ずつになるように分けて、再帰的に Σ1 用の T1 と Σ2 用の T2 を計算していく
  - Huffman's (optimal) idea
    - bottom-up にマージしながら木を作っていく
- A Greedy Approach
  - question
    - どのペアをマージするのが "safe" なのか
  - observation
    - 最終的な encoding length of i は、そのノードの subtree がマージされた回数となる
    - 最初の試行では、最も頻度の低い 2 つをマージすれば良い
  - How to Recurse?
    - idea
      - a, b をマージしたら新しい "meta-symbol" ab に置き換える
      - ab の確率 p ab は pa + pb となる

## Huffman's Algorithm

- Huffman's Algorithm
  - if |Σ| = 2 return
  - Let a, b ∈ Σ have the smallest frequencies
  - Let Σ' = Σ with a, b replaced by new symbol ab
  - pab = pa + pb とする
  - 再帰的に T' を計算する(T' はアルファベット Σ' と対応)
  - Extend T' to a tree T with leaves <-> Σ by splitting leaf ab into two leaves a & b (ここで元の a と b に戻す)
  - Return T
- 正しいことの証明
  - 以下を証明する
    - Huffman's algorithm が binary tree を計算し、その binary tree は average encoding length `L(T) = Σ(i∈pi) pi・[depth of i]` を最小化していること
  - 帰納法で示す
    - n = |Σ| (n >= 2) とする
    - base case
      - n = 2 の時、最適な木を出力できる
    - inductive step
      - n = |Σ| > 2 とする
      - Σ' を Σ から smallest frequencies の a と b について、meta-symbol ab に置き換えたものとする。pab = pa + pb とする
      - ここで、すべての T' と T において L(T) - L(T') は pa[a's depth in T] + pb[b's depth in T] - pab[ab's depth in T'] = pa(d + 1) + pb(d + 1) - (pa + pb)d = pa + pb
        - d は T' の depth
      - Try exchange
        - a, b を選んでマージした tree T^ と、a, b の代わりに x, y を選んだ tree T" を考える
        - そして L(T^) <= L(T") となることを示したい
        - L(T") - L(T^) = (px - pa)・[x's depth in T" - a's depth in T"] + (py - pb)・[y's depth in T" - b's depth in T"]
        - ここで px - pa, x's depth in T" - a's depth in T", py - pb, y's depth in T" - b's depth in T" はすべて 0 以上なので L(T") - L(T^) >= 0 が示された。証明終わり
  - 実行時間
    - naive implementation だと O(n^2)、ここで n = |Σ|
    - speed up
      - ヒープを使う
        - key に frequency を入れる
        - 2 つの smallest frequency symbols を抽出してマージを行ったあとは、meta-symbol を再挿入する
      - これで実行時間は O(n log n) となる
    - さらに速くするには Sorting + O(n) additional work で行うやり方がある
      - 2 つの queue を利用して symbol を管理するやり方
