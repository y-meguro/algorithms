# Part 8: Linear-Time Selection

## Randomized Selection

- 問題
  - n 個の異なる数字が与えられ、i 番目の大きさの数字を返す
- `O(n * log n)` で実行する場合
  - merge sort を行った後、i 番目の要素を返せばいい
  - ソートを使う場合、これ以上速くできないが、ここでは i 番目の要素がわかればいいので、もう少し速くできる
- Quick Sort を修正し、O(n) で実行できないか考える
  - key idea
    - ソートを行わなくとも、pivot の左にある要素は pivot より小さく、pivot の右にある要素は pivot より大きいとわかる
    - 例えば 10 個の要素があって、5 番目の要素を探したいとする。3 番目の要素を pivot に選んだとすると、pivot の右にある要素の中から、2 番目の大きさのものを返せばいいとわかる
- Randomized Selection
  - 以下が擬似コード
  - quality は pivot 選択の質による
    - 最悪だと θ(n^2)
    - median を選び続けられた場合は T(n) <= T(n/2) + O(n) となり、これは T(n) = O(n) となる (Master Method の case 2)
  - 平均実行時間は O(n)
    - 証明は後述

```
Rselect(array A, length n, order statistic i)
if n == 1
  return A[1]
Choose pivot p from A uniformly at random
Partition A around p
let j = new index of p
if j == i
  return p
if j > i
  return Rselect(1st part of A, j - 1, i)
if j < i
  return Rselect(2nd part of A, n - j, i - j)
```

- 平均実行時間が O(n) となることの証明
  - Proof 1: Tracking Progress via Phases
    - Rselect は recursive call の外側で、ある定数 c > 0 を使い、cn 回以下の操作を行っているとする
    - Rselect が phase j にある時、現在の配列のサイズは (3/4)^j+1・n から (3/4)^j・n の間にあるとする
    - Xj は phase j にある時の、recursive calls の回数とする
    - 以上を用いて、`running time of Rselect <= ΣXj * c * (3/4)^j * n` ただし、Σ の範囲はすべての phase j
  - Proof 2: Reduction to Coin Flipping
    - Rselect が選ぶ pivot が 25-75 split(or better) なら、現在の phase は終了する
    - 25-75 split or better の確率が 50% であることを思い出すと、E[Xj] <= コインを投げて 1 枚表が出るまで投げる枚数と言い換えられる
  - Proof 3: Coin Flipping Analysis
    - N を表が出るまで投げるコインの枚数とする
    - E[N] = 1 + (1/2) * E[N]
      - 1st coin は投げるので 1
      - 1st coin が裏の確率は 1/2 なので、その確率に 2 枚目以降の期待値 E[N] をかける
      - これを計算すると E[N] = 2 とわかる
  - これらより、`Expected running time of Rselect <= E[cn * Σ(3/4)^j * Xj]`。この式を A とする
  - `A = cn * Σ(3/4)^j * E[Xj]`。ここで Proof 2 と 3 より E[Xj] <= 2 なので `A <= 2cn * Σ(3/4)^j`
  - ここで Σ(3/4)^j = 4 なので、`A <= 8cn = O(n)` となり、平均実行時間が O(n) となることが証明された

## Deterministic Selection

- Guaranteeing a Good Pivot
  - "best" pivot は median
  - goal
    - 見つけた pivot が十分良いことを保証すること
  - key idea
    - use "median of medians"
- A Deterministic ChoosePivot
  - ChoosePivot(A, n)
    - logically break A into n/5 groups of size 5 each
    - sort each group
    - copy n/5 medians into new array C
    - recursively compute median of C
    - return this as pivot
- Pseudocode
  - 以下のようになる
  - Rselect と異なり、2 回の recursive call がある(`p = DSelect(C, n/5, n/10)` の分が多い)

```
DSelect(array A, length n, order statistic i)
Break A into groups of 5, sort each group
C = the n/5 "middle elements"
p = DSelect(C, n/5, n/10)
Partition A around p
let j = new index of p
if j == i
  return p
if j > i
  return DSelect(1st part of A, j - 1, i)
if j < i
  return DSelect(2nd part of A, n - j, i - j)
```

- 実行時間
  - O(n) となる
    - 証明は後述
- だが、実際は Rselect ほど良くない
  - 以下の理由のため
    - Worse constants
      - big-Oh で隠れているが、定数部分が Rselect より悪い
    - not-in-place
      - DSelect では additional memory storage が必要になってしまう
- Rough Recurrence
  - T(n) を長さ n の配列が与えられた時の Dselect の最大実行時間とする
  - ある定数 c >= 1 が存在し、以下のようになる。T(?) は 2 回目の recursive call のところと対応
    - 1: T(1) = 1
    - 2: T(n) <= c * n + T(n/5) + T(?)
- The Key Lemma
  - key lemma
    - 2nd recursive call guaranteed to be on an array of size <= 7n/10 (roughly)
  - rough proof
    - k = n/5 = グループ数
    - xi = ith smallest of the k "middle elements"
    - よって、pivot は xk/2 と表せる
  - goal
    - 30% 以上の要素が xk/2 以下であり、30% 以上の要素が xk/2 以上であることを示したい
  - key point
    - ここで xk/2 は半分のグループの 3 番目の要素より大きく、半分のグループの 3 番目の要素より小さい
    - なので、30% の要素よりは大きく、同様に 30% の要素よりは小さい
- Rough Recurrence(Revisited)
  - T(1) = 1
  - T(n) <= cn + T(n/5) + T(7n/10) (ここで、c >= 1)
  - subproblem のサイズが n/5 と 7n/10 で異なるので、Master Method が使えない
  - n と独立なある定数 a が存在し、すべての n >= 1 で T(n) <= an となることを示したい
- 帰納法で示す
  - a = 10c とし、すべての n >= 1 で T(n) <= an となることを示す
  - n = 1 の時、T(1) = 1 <= a * 1。これは a >= 1 より成り立つ
  - n < k のすべての k で成り立つとすると、n = k の時、T(n) <= cn + T(n/5) + T(7n/10) <= cn + a(n/5) + a(7n/10) <= n(c + 9a/10) = an となり、n = k でも成り立つ
  - 以上より、すべての n について証明された

## Sorting Lower Bound

- 定理
  - すべての比較ソート(comparison-based sorting)は、最悪実行時間が `Ω(n * logn)` となる
- Comparison-Based Sort
  - accesses input array elements only via comparisons
    - 比較を行う時にだけ、input の配列の要素にアクセスするもの
  - 比較ソートの例
    - Merge Sort, Quick Sort, Heap Sort
  - 非比較ソートの例
    - Bucket Sort, Counting Sort, Radix Sort
- 最悪実行時間が `Ω(n * logn)` となることの証明
  - {1, 2, ..., n} が任意の順で並んだ配列が与えられたとする
    - これは n! 通りある
  - この配列を k 回の比較でソートすることを考える
    - 正しくソートするには `2^k >= n!` を満たすような k でないとならない
    - `2^k >= n! >= (n/2)^n/2` => `k >= n/2 * log2 n/2 = Ω(n * log n)`

# Part 9: Graphs and The Contraction Algorithm

## Graphs

- 頂点(Vertices, V)と辺(Edges, E)から構成される
- 辺には有向のもの(directed)と、無向のもの(undirected)がある

## Cuts of Graphs

- 定義
  - graph(V, E) のカットとは、V を 2 つの non-empty な集合 A と B に分割するもの
    - [カット (グラフ理論) - Wikipedia](https://ja.wikipedia.org/wiki/%E3%82%AB%E3%83%83%E3%83%88_(%E3%82%B0%E3%83%A9%E3%83%95%E7%90%86%E8%AB%96))
  - cut(A, B) の crossing edges(交差辺)とは以下のどちらか
    - 無向グラフの場合: エンドポイントが A, B のそれぞれにある
    - 有向グラフの場合: A から B (または B から A)に向かっている辺

## The Minimum Cut Problem

- input
  - 無向グラフ G = (V, E)
- goal
  - カットを行うための crossing edges の最小切断回数
- 以下のようなものに応用される
  - identify network bottlenecks / weaknesses
  - community detection in social networks
  - image segmentation

## Sparse vs Dense Graphs

- Sparse Graph (疎グラフ)
- Dense Graph (密グラフ)
- n を頂点の数、m を辺の数とすると、ほぼすべてのケースで m は Ω(n) かつ O(n^2) となる
  - "sparse" graph では m は O(n) に近い
  - "dense" graph では m は θ(n^2) に近い

## The Adjacency Matrix (隣接行列)

- Aij = 1 ⇔ G が i-j の辺を持つ
  - 他にもいくつかの変形がある
    - Aij = # of i-j edges(多重辺が許される場合)
    - Aij = weight of i-j edge
    - Aij = +1 / -1 (辺の向きを表す)
- 必要とする空間は θ(n^2)

## Adjaency Lists (隣接リスト)

- [隣接リスト - Wikipedia](https://ja.wikipedia.org/wiki/%E9%9A%A3%E6%8E%A5%E3%83%AA%E3%82%B9%E3%83%88)
- 必要とする空間は θ(m + n)
- 隣接行列と隣接リストのどちらがよいかは、graph density と必要となる operations に依存する
  - 疎グラフの場合、隣接リストのほうがメモリを無駄にしない

## Random Contraction Algorithm

- While there are more than 2 vertices:
  - ランダムに残っている辺の中から 1 つ選ぶ(その辺が点 u と v を結ぶとする)
  - merge (or "contract") u and v into single vertex
  - self-loop を削除する
- return cut represented by final 2 vertices
  - 最後に残った 2 頂点がカットを表している
- key question
  - What is the probablity of success?
- 準備
  - グラフ G = (V, E) を n 個の頂点、m 個の辺があるグラフとする
  - 最小カットで A, B の 2 つの集合ができるとする
  - k を (A, B) を交差する辺の数とする
- うまく行かない場合(最小カットにならない場合)
  - A, B を交差する、ある辺を F とする
    - もし F が縮約されてしまうと、アウトプットは (A, B) にならない
  - なので Pr[output is (A, B)] = Pr[never contracts an edge of F]
  - ここで Si = 辺 F が i 回目に縮約される事象の集合 とすると Pr[not S1 ∧ not S2 ∧ ... ∧ not Sn-2] を計算すれば良い
- 最初の縮約を考える
  - 各頂点から最低でも k 本の辺が出ている
    - もし k - 1 以下の場合、その辺を全部切断すれば最小カットになってしまう
  - よって kn <= 2m となり、m >= kn/2 とわかる
  - ここで Pr[S1] = k/m (1 回目は m 本の中から k 本のどれかが選ばれる確率)なので、Pr[S1] <= 2/n となる
- 2 回目の縮約
  - `Pr[not S1 ∧ not S2] = Pr[not S2 | not S1] * Pr[not S1]`
  - ここで Pr[not S1] >= 1 - 2/n であり、Pr[not S2 | not S1] = 1 - k/(# of remaining edge) である
  - 1回目と同様にすべての点は k 本以上の辺を持つので、remaining edge の数は、`1/2 * k * (n - 1)`
  - 以上より計算すると、`Pr[not S2 | not S1] >= 1 - 2/(n - 1)`
- すべての縮約
  - `Pr[not S1 ∧ not S2 ∧ ... ∧ not Sn-2] = Pr[not S1] * Pr[not S2 | not S1] * Pr[not S3 | not S1 ∧ not S2] * ... * Pr[not Sn-2 | not S1 ∧ ... ∧ not Sn-3]`
  - `>= (1-2/n) * (1-2/(n-1)) * (1-2/(n-2)) * ... * (1-2/(n-(n-3)))`
  - `= n-2/n * n-3/n-1 * ... * 1/3 = 2/n(n-1) >= 1/n^2`
- 成功する確率(すべて失敗しない確率)
  - N 回やってすべて失敗する確率は (1 - 1/n^2)^N 以下
  - ここで 1 + x <= e^x を利用する
  - `N = n^2` の時、`Pr[all fail] <= (1 - 1/n^2)^N <= (e^(-1/n^2))^N = 1/e`
  - また `N = n^2 * ln n` の時、`Pr[all fail] <= (1/e)^ln n = 1/n`

## Counting Minimum Cuts

- グラフは何通りかの min cuts の選択肢を持つ
  - 例えば木構造だと、n-1 通りの minimum cuts がある
