# Part 17: Two Motivating Applications

## Distributed Shortest-Path Routing

- Graphs and the Internet
  - Internet はグラフ
    - end hosts と routers が頂点。direct physical or wireless connections が辺
- Internet Routing
  - Stanford の gateway router から Cornell の gateway router にデータを送ることを考える
  - question
    - どのようなルートで送るか？
  - idea
    - shortest-path を探す
  - Dijkstra's algorithm で計算すればよい？
    - しかしこの場合、Stanford の gateway router は Internet 全体を知る必要が出てしまう
  - solution
    - Bellman-Ford algorithm で解決する
      - また、これは netgative edge costs も扱える

## Sequence Alignment

- Motivation
  - ゲノムの計算における基本的な問題
  - input
    - {A, C, G, T} からなる 2 つの文字列
  - problem
    - 2 つの文字列がどのくらい似ているか判定したい
- Similarity の測定
  - question
    - similar が意味するのは何か
  - intuition
    - "AGGGCT" と "AGGCA" はうまく並べることができるので似ている
  - idea
    - Measure similarity via quality of "best" alignment
      - AGGGCT と AGG-CA とすると 1 mismatch(AGGCA に 1 つ "gap" (-) を挿入した)
  - 仮定
    - gap と mismatch から penalties を決定することができる
- Problem Statement
  - input
    - {A, C, G, T} からなる 2 つの文字列
    - Penalty pen gap はそれぞれの gap を表し、0 以上となる
    - Penalty pen AT は A と T のミスマッチを表し、0 以上となる
  - output
    - Needleman-Wunsch score と呼ばれる total penalty を最小化させたもの
    - NW score が小さい ≒ Similar Strings となる
- Algorithms are Fundamental
  - 効率的に best alignment を探すアルゴリズムがないと、genome similarity の測定は役に立たない
  - brute-force search
    - すべての alignments を試し、最も良いものを記憶する
    - これだと長さが 500 の場合、2^500 >= 10^125 の操作が必要となってしまい、現実的でない
  - solution
    - dynamic programming を使う

# Part 18: Introduction to Greedy Algorithms

- Algorithm Design Paradigms
  - Algorithm Design
    - どんな問題にも適用できる単一の "silver bullet" はない
  - Design Paradigms
    - divide & conquer (course1)
    - randomized algorithms (course1)
    - greedy algorithms (本コース)
    - dyamic programming (本コースの後半)

## Greedy Algorithm

- definition
  - "myopic" な(近視眼的な) 決定を繰り返すことで、最終的に望ましい結果を得るアルゴリズム
- 例
  - Dijkstra's shortest path algorithm
- Divide & Conquer との違い
  - 貪欲法は様々な問題に適用できる
  - 実行時間の解析が簡単
  - 正しさを証明するのが難しい
    - 貪欲法は正しくないことも多いので、注意が必要
- Proofs of Correctness
  - 1: 帰納法
  - 2: "Exchange argument"
    - 貪欲法が正しくないと仮定した上で、矛盾を導く
    - 2 つの要素を交換した場合に、最適だと仮定するようなやり方
  - 3: Whatever works!
    - 1 と 2 を組み合わせるやり方だったり、完全に別のものだったり、何らかの正しいやり方でやる
- The Caching Problem
  - キャッシュミスが起きたら、何かをキャッシュから追い出す必要がある。その時にどの要素を追い出せば、キャッシュミスが減るか
- The Optimal Caching Algorithm
  - The "furthest-in-future" algorithm が最適
  - 実際的には Least Recently Used(LRU) を使うことが多いが、理想的なベンチマークとして "furthest-in-future" algorithm の結果を計算することは役に立つ

# Part 19: A Scheduling Application

## A Scheduling Problem

- setup
  - 1 つの共有されるリソース(processor など)
  - たくさんの実行される "job" (prcesses など)
- question
  - どの順で jobs を処理するのがよいか
- 仮定
  - 各 job は weight wj ("priority") と length lj を持つ
- Completion Times
  - 定義
    - completion time Cj は job j も含めたそこまでの job の合計の長さ
    - l1 = 1, l2 = 2, l3 = 3 なら C1 = 1, C2 = 3, C3 = 6 となる
- The Objective Functions
  - Σ(j = 1 to n) wjCj を最小化すること
  - 例えば w1 = 3, w2 = 2, w1 = 1 で、上記の C1 - C3 なら 3・1 + 2・3 + 1・6 = 15 となる
- Intuition for Algorithm
  - 同じ length の job の場合は weight が larger なものを先に実行する
  - 同じ weight の job の場合は length が shorter なものを先に実行する
- Resolving Conflicting Advice
  - では、wi > wj かつ li > lj の場合はどちらを先に実行するか
  - idea
    - "scores" を jobs に設定する
      - weight が増えると大きくなるように
      - length が増えると小さくなるように
  - guess
    - 1: wj - lj の降順で並べる
    - 2: wj / lj の降順で並べる
- Breaking a Greedy Algorithm
  - 例えば、l1 = 5, w1 = 3, l2 = 2, w2 = 1 の場合はどうなるか
    - guess1 のやり方だと 2 が先
      - この場合の実際の completion time は 1・2 + 3・7 = 23
    - guess2 のやり方だと 1 が先
      - この場合の実際の completion time は 3・5 + 1・7 = 22
  - guess1 のやり方は常に正しいわけではない
  - 一方 guess2 のやり方は常に正しい
    - 証明は後述
  - 実行時間は O(n log n)
- 証明
  - 以下を証明する
    - wj / lj の降順に並べることが completion time を最小化することを示す
  - Exchange Argument を利用して示す
  - plan
    - σ を greedy schedule、σ' を最適なスケジュール、σ != σ' として矛盾を導く
  - 仮定
    - すべての wj / lj は重複しないとする
    - w1 / l1 > w2 / l2 > ... > wn / ln とする
      - greedy schedule の σ ではこのままの順で並ぶ
    - σ' の中の、ある連続する i と j (i > j) について考える
      - この i と j だけを入れ替えた場合を考える
        - completion time は wj・li の分だけ増え、wi・lj の分だけ下がる
        - ここで i > j なので wi / li < wj / lj <=> wi・lj < wj・li
        - よって、completion time は増加してしまう。これは σ' が最適なスケジュールであることに矛盾する。証明終わり

# Part 20: Prim's Minimum Spanning Tree Algorithm

## Overview

- informal goal
  - 頂点の集合を最小コストでつなぐこと
- Applications
  - clustering, networking
- Greedy Algorithms
  - Prim's Algorithm
  - Kruskal's Algorithm
  - これらは O(m log n) で解ける(m は辺の数、n は頂点の数)
- Problem Definition
- input
  - 無向グラフ G = (V, E) と e ∈ E についてコスト ce が与えられる
    - 隣接リストで表現すると仮定する
    - コストは負の値でも OK
- output
  - 最小コストの tree T ⊆ E、この T はすべての頂点を通る
- Standing Assumptions
- 仮定 1
  - input graph G は連結している
    - そうでなければ spanning tree (全域木) は作れない
- 仮定 2
  - 各辺のコストは、すべて異なる値とする

## Prim's MST Algorithm

- Prim's MST Algorithm
  - X = {s} で初期化(s は任意の開始点)
  - T = 0
  - while X != V
    - e = (u, v) を、u ∈ X, v ∉ X を満たす G に含まれる最小コストの辺とする
    - Add e to T
    - Add v to X
- 証明の流れ
  - Part 1: spanning tree T' の計算
  - Part 2: T' が MST であることの証明
  - さらにこの処理がヒープを利用して O(m log n) でできることを示す
- Cuts
  - claim
    - Prim's algorithm は spanning tree を出力する
  - cut の定義
    - graph G = (V, E) のカットとは、V を 2 つの空でない集合に分けることとする
    - n 個の頂点がある場合、カットのやり方は約 2^n 通り
- Empty Cut Lemma
  - graph が連結していない <=> ∃ cut(A, B) with no crossing edges
- Two Easy Facts
  - Double-Crossing Lemma
    - cycle C ⊆ E が cut(A, B) にまたがる辺を持っているとする
    - その場合、上記の辺の他にもう 1 つ A と B にまたがる辺を持つ
- Lonely Cut Corollary
  - e が唯一の A, B にまたがる辺だとすると、その辺はサイクルを持っていない
- 証明
  - Prim's algorithm は spanning tree を出力することを示す
    - 1: プリム法は不変条件 T spans X を維持する
    - 2: X != V である (言い換えると (X, V - X) は常に空である)
    - 3: T の中でサイクルはできない
      - 新しく追加される辺 e は first edge crossing(X, V - X) なので、T の中でサイクルを作ることはできない
  - Prim's algorithm が出力する spanning tree は minimum-cost の spanning tree であることを示す
    - The Cut Property
      - G に含まれる辺 e について考える
        - e を cut(A, B) をつなぐ最小コストの辺とする
      - この場合、e は G の MST に含まれる
    - key point
      - すべての辺 e ∈ T' は明らかに Cut Property を満たす
      - T' は MST の subset であり、全域木であるため、T' 自体が MST であるとわかる
  - Cut Property が正しいことの証明
    - cut(A, B) にまたがる最もコストの小さい辺 e があり、MST T' に含まれないと仮定する
      - ここから矛盾を導ければ Cut Property が正しいことが示される
    - idea
      - e を T' の中の別の辺と交換して、よりコストが下がることを示したい
      - しかし、どの辺と e を交換すれば示せるのか？
    - attempted exchange
      - T' は連結しているので、A, B を交差する edge f(!= e) が存在する
      - この f と e を交換した場合、T' のコストは下がる
        - しかし、交換した場合に T' が全域木になるかどうかは e と f の選び方による
        - 例えば、f としかつながっていない点がある場合は全域木とならない
    - smart exchangs
      - Let C = cycle created by adding e to T'
      - この時、Double-Crossing Lemma より、e と異なり、A と B を交差する e' ∈ T' が存在する
        - 図がわかりやすいので、資料を見るとよい
      - ここで e と e' を交換すれば ce < ce' より、T' のコストが下がり、矛盾が示される
- 実装
  - Prim's MST Algorithm (再掲)
    - X = {s} で初期化(s は任意の開始点)
    - T = 0
    - while X != V
      - e = (u, v) を、u ∈ X, v ∉ X を満たす G に含まれる最小コストの辺とする
      - Add e to T
      - Add v to X
  - 実行時間
    - iteration が O(n) 回
    - 各 iteration での処理が O(m) 回
    - なので O(mn) 時間となるが、これを改善する
- Prim's Algorithm with Heap
  - 不変条件
    - 1: V - X の要素を heap にいれる
    - 2: v ∈ V - X に対して、key[v] に edge(u, v) の最小コストを入れる(ただし u ∈ X)
  - check
    - heap の初期化に必要なのは O(m + n log n) = O(m log n) である
      - key の比較に m 回、n 個の要素の挿入で n log n 回
      - ここで G は連結しているので、m >= n - 1 であるので、漸近的に考えると n は m に置き換え可能。O(m + n log n) = O(m log n) としてよい
  - 不変条件 2 の維持
    - Extract-Min が実行されるたびに、key の再計算が必要
    - Pseudocode は以下

```
When v added to X
  for each edge (v, w) ∈ E
    if w ∈ V - X
      Delete w from heap
      Recompute key[w] = min{key[w], cvw}
      Re-Insert into heap
```

- 実行時間
  - 必要な heap の処理は以下
    - n - 1 回の挿入(初期化時)
    - n - 1 回の Extract-Min 処理
    - 各 edge(v, w) の削除と挿入
  - これは O(m) 回の heap 操作が必要 (m >= n - 1 より)
  - よって O(m log n) 時間とわかる
