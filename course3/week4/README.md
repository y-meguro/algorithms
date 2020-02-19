# Part 26: The Knapsack Problem

## Problem Definition

- input
  - n 個のアイテムがある
  - それぞれが以下を持つ
    - value vi (nonnegative)
    - size wi (nonnegative and integral)
    - capacity W (a nonnegative integer)
- output
  - Σwi <= W の中で Σvi を最大化させる subset S ⊆ {1, 2, ..., n}

## Developing a Dynamic Programming Algorithm

### Step 1

- optimal solution の構造を元に、再帰的に計算する
- S を max-value solution とする
- Case 1
  - item n ∉ S の場合
  - S は 1st n - 1 item の S でもある
- Case 2
  - item n ∈ S の場合
  - S - {n} は 1st n - 1 item の capacity が W - wn の場合の最適解
- Recurrence from Last Time
  - notation
    - Vi,x を以下の場合の、最適解の値とする
      - 最初の i 個の item のみを使う
      - total size が x 以下
  - upshot
    - Vi,x = max{V(i-1),x, vi + V(i-1),x-wi}

### Step 2

- subproblem を特定する
  - All possible prefixes of items {1, 2, ..., i}
  - All possible (integral) residual capacities x ∈ {0, 1, 2, ..., W}

### Step 3

- 再帰を利用して、Step 1 からシステム的にすべての問題を解く

```
Let A = 2-D array
Initializze A[0, x] = 0 for x = 0, 1, ..., W
for i = 1, 2, ..., n
  for x = 0, 1, ..., W
    A[i, x] = max{A[i - 1, x], A[i - 1, x - wi] + vi}
Return A[n, W]
```

- 実行時間は θ(nW)
  - θ(nW) の subproblem があって、各 θ(1) 時間で実行できる
