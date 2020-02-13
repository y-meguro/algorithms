# Part 5: Quicksort Algorithm

## Overview

- 平均実行時間 `O(n * log n)`
- additional storage がとても小さくて済む
- key
  - pivot を使って分割する
- やり方
  - 配列から 1 つの要素を選んで pivot とする
  - 配列を再配置する
    - pivot の左には pivot より小さい要素が来るようにする
    - pivot の右には pivot より大きい要素が来るようにする
- 2 cool facts about partition
  - Linear O(n) time, no extra memory
    - 後述の「Partition Subroutine」で extra memory が不要なやり方を説明
  - Reduces problem size
- High-Level Description
  - QuickSort(array A, length n)
    - If n=1 return
    - p = ChoosePivot(A,n)
    - Partition A around p
    - Recursively sort 1st part
    - Recursively sort 2nd part

## Partition Subroutine

- O(n) の extra memory を使えば簡単。O(n) 時間で partition できる
- In-Place Implementation
  - extra memory を使わずにやる
- 仮定
  - 配列の先頭の要素を pivot とする(先頭以外を pivot とする場合、pivot と先頭の要素を swap すれば同じ)
- Higl-Level Idea
  - pivot, p より小さい要素, p より大きい要素(ここまで partition 済み), まだ partition されていない要素 となるようにする
  - p より大きい要素が開始するインデックス i と、まだ partition されていない要素が開始するインデックス j を記憶しておく
    - pivot: 1
    - p より小さい要素 [2, i)
    - p より大きい要素 [i, j)
    - まだ partition されていない要素 [j, end]
  - j 番目の要素(まだ partition されていない最も左側の要素)が p より小さい場合は、i 番目の要素と swap、i と j を共にインクリメントする。p より大きい場合は、j をインクリメントする
  - 上の操作を最後まで行った後、ピボットを i 番目の要素と交換すれば、pivot の左側は pivot より小さい要素、右側は pivot より大きい要素となる
- Pseudocode

```
Partition(A, l, r)
p = A[l]
i = l + 1
for j = l + 1 to r
  if A[j] < p
    swap A[j] and A[i]
    i = i + 1
swap A[l] and A[i - 1]
```

- 上記の実行時間は O(n)

## Chosing a Good Pivot

- QuickSort の実行時間は pivot の質に左右される
  - 常に 1 番小さいものを選んでしまうと `θ(n^2)`
  - 常に真ん中のものを選べれば `θ(n * log n)`
- Random Pivots
  - すべての recursive call でランダムに pivot を選ぶ
  - もしすべての pivot が 25-75% の間にある要素であれば実行時間は `O(n * log n)` になる
  - また、半分の pivot が 25-75% の間にある要素であれば実行時間は `O(n * log n)` になる
- QuickSort の平均実行時間
  - `O(n * log n)`

# Part 6: Quicksort Analysis

- 準備(用語の定義)
  - Sample Space Ω
    - pivot をランダムに選択した、可能性のある全ての結果の集合
  - C(σ)
    - σ∈Ω に対して、C(σ) を 2 つの要素の比較回数の合計値とする
  - E[C]
    - 平均の比較回数。これが `O(n * log n)` になることを示したい
  - Xij(σ)
    - σ∈Ω、zi = ith smallest element of A、i < j として、Xij(σ) は zi, zj が σ の場合に QuickSort で比較される回数とする
- A Decomposition Approach
  - ∀σ, C(σ) = Σ(i=1 to n-1)Σ(j=i+1 to n) Xij(σ)
  - よって E[C] = Σ(i=1 to n-1)Σ(j=i+1 to n) E[Xij]
  - ここで E[Xij] = 0・Pr[Xij=0] + 1・Pr[Xij=1] = Pr[Xij=1]
  - 以上より `E[C] = Σ(i=1 to n-1)Σ(j=i+1 to n) Pr[zi, zj get compared]` となる
- Key Claim として、以下の主張が正しいことを証明する
  - すべての i < j について、Pr[zi, zj get compared] = 2/(j - i + 1) となる
  - 証明
    - zi, zi+1, ..., zj-1, zj の中のどれかが pivot に選ばれることを考える
    - 1: もし zi か zj が最初に選ばれたら、zi と zj は直接比較される
    - 2: もし zi+1, ..., zj-1 のどれかが先に選ばれたら、zi と zj は直接比較されない
    - 1・2 から Pr[zi, zj get compared] = 2/(j - i + 1) となる
- よって、`E[C] = Σ(i=1 to n-1)Σ(j=i+1 to n) 2/(j - i + 1)` となる。
  - `Σ(j=i+1 to n) 1/(j - i + 1)` は 1/2 + 1/3 +... となり、`Σ(i=1 to n-1)` は n 以下なので、`E[C] <= 2 * n * Σ(k=2 to n) 1/k` となる
  - ここで `Σ(k=2 to n) 1/k <= ln n` なので `E[C] <= 2n * ln n` が示された

# Part 7: Probability Review

## Sample Space

- Smaple Space Ω
  - 日本語だと標本空間
  - "all possible outcomes"
  - i∈Ω とすると 確率 p(i) >= 0 となり、Σp(i) = 1 となる

## Events

- event は subset S ⊆ Ω のこと
- 日本語だと事象
- 例えばサイコロを 2 つ投げて目の合計が 7 になる事象を考えると S = {(1, 6), (2, 5), (3, 4), (4, 3), (5, 2), (6, 1)} となり、Pr[S] = 1/6

## Random Variables

- 日本語だと確率変数
- ある現象がいろいろな値を取りうるとき、取りうる値全体を確率変数 X として表す
- 2 つのサイコロの目の合計だと 2 から 12 が取りうる値の範囲となる

## Expectation

- 日本語だと期待値
- E(X) = average value of X = ΣX(i)・p(i)
- 2 つのサイコロの目の合計だと、期待値は 7

## Linearity of Expectation

- 日本語だと期待値の線形性
- 期待値は線形性を持つため、E[ΣXj] = ΣE[Xj] が成立する
  - これが成り立つと、例えば E[X1 + X2] = E[X1] + E[X2] が成り立つ
  - [高校数学における線形性の8つの例 | 高校数学の美しい物語](https://mathtrain.jp/linear)

## Conditional Probability

- 日本語だと条件付き確率
- X, Y ⊆ Ω となる events として、Pr[X|Y] = Pr[X∩Y] / Pr[Y]

## Independence (of Events)

- 日本語だと独立
- Events X, Y ⊆ Ω が independent ⇔ Pr[X∩Y] = Pr[X]・Pr[Y]
