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
