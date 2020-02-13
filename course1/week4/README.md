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
