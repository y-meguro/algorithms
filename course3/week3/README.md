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

# Part 25: Introduction to Dynamic Programming

## Weighted Independent Sets in Path Graphs

- Problem Statement
  - input
    - 各頂点の負ではない weight ともに、path graph G = (V, E) が与えられる
  - desired output
    - total weight が最大化するような、隣接しない頂点の集合(この集合を independent set と呼ぶ)
  - brute-force search
    - 指数時間がかかる
- A Greedy Approach
  - 隣接しない頂点の中で max-weight となる頂点を前から順に選んでいく
  - うまくいかない
    - 例えば 1 - 4 - 5 - 4 と頂点が並ぶ時、この方法だと 1 + 5 = 6 を答えに選んでしまうが、8 が最適
- A Divide & Conquer Approach
  - 前半と後半に分けて、両者を組み合わせる
  - しかし、前半の最後の頂点と後半の最初の頂点を選んだ時などのように、sub-solutions が conflict する場合がある
    - なのでこちらもうまくいかない
- Optimal Substructure
  - 最適解の構造を推測する
  - notation
    - max-weight independent set(IS) を S ⊆ V とする
    - vn = last vertex of path
- A Case Analysis
  - case 1: vn ∉ S, G' = G with vn deleted とする
    - この場合、S は G' でも IS となる
  - case 2: vn ∈ S とする
    - この時、vn-1 は S に含まれない
    - ここで G" = G with vn-1, vn deleted とする
    - すると、G" の IS は S - {vn} となる
- Toward an Algorithm
  - upshot
    - max-weight IS は以下のどちらか
      - 1: max-weight IS of G'
      - 2: vn + max-weight IS of G"
  - corollay
    - もし vn が max-weight IS に含まれるかどうかがわかるなら、以下のように再帰的に計算していけばいい
      - S1 = max-weight IS of G'
      - S2 = max-weight IS of G"
      - S1 または S2 ∪ {vn} のうち良いほうを返す
    - このやり方は正しいが、指数時間がかかってしまう
- Eliminating Redundancy
  - subproblem のキャッシュをテーブルに保持して、O(1) で lookup できるようにする
  - 配列 A を用意して、A[i] に max-weight IS of Gi を入れる
    - Gi は G の中の最初の i 個の点
  - 初期化
    - A[0] = 0, A[1] = w1
  - Main loop
    - for i = 2, 3, ..., n において A[i] = max{A[i - 1], A[i - 2] + wi}
  - 実行時間
    - O(n) でできる
- Optimal Value vs Optimal Solution
  - note
    - max-weight IS の値は計算するが、IS にどの頂点が含まれるかは計算していない
  - correct but not ideal
    - 各 Gi に値だけでなく、optimal IS (どの頂点も含むか)も格納する
  - better
    - optimal solution を再構築できるように配列を埋めていく
  - key point
    - vi が Gi の max-weight IS に所属する <=> wi + max-weight IS of Gi-2 >= max-weight IS of Gi-1
- A Reconstruction Algorithm
  - A は optimal value が埋められた配列とする
  - 以下のようになる
  - 最後に返される S が max-weight IS of G
  - 実行時間は O(n)

```
Let S = 0
While i >= 1
  if A[i - 1] >= A[i - 2] + wi
    i -= 1
  else
    Add vi to S
    i -= 2
Return S
```

## Principles of Dynamic Programming

- 上述の WIS algorithm は dynamic programming algorithm
- Key
  - 1: small number の subproblem を特定する
  - 2: small subproblem の解を使って、素早く正確に "larger" subproblem を解く
    - A[i] = max{A[i - 1], A[i - 2] + wi} のような感じ
  - 3: すべての subproblem を解いた後、final solution を計算する
