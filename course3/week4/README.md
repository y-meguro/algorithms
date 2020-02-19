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

# Part 27: Sequence Alignment

## Problem Definition

- recall
  - AGGGCT と AGGCA の類似度を total penalty = αgap + αAT で測った
- input
  - いくつかのアルファベット Σ (like {A, C, G, T}) から構成される String X = x1...xm, Y = y1...yn が与えられる
- feasible solutions
  - 文字列の長さが等しくなるため gap を挿入する
- goal
  - total penalty を最小化する alignment を出力する

## A Dynamic Programming Approach

- key step
  - subproblem を特定すること。大抵の場合は optimal solution の構造にヒントがある
- structure of optimal solution
  - X, Y の optimal alignment を考える。final position はどうなっているか
  - 3 つの場合がある
    - Case 1: xm, yn がマッチしている
    - Case 2: xm が gap とマッチしている
    - Case 3: yn が gap とマッチしている
  - optimal substructure
    - X' = X - xm, Y' = Y - yn とする
    - Case 1: X' & Y' が optimal
    - Case 2: X' & Y が optimal
    - Case 3: X & Y' が optimal
- The Subproblems
  - 以下のように定める
    - Xi = 1st i letters of X
    - Yj = 1st j letters of Y
- The Recurrence
  - notation
    - Pij = penalty of optimal alignment of Xi & Yj とする
  - recurrence
    - for all i = 1, ..., m, and j = 1, ..., n
      - Pij は以下の中の最小のもの
        - (1) αXiYj + Pi-1,j-1
        - (2) αgap + Pi-1,j
        - (3) αgap + Pi,j-1
- Base Cases
  - Pi,0 と P0,i は i・αgap となる
- The Algorithm
  - 実行時間は O(mn)

```
A = 2-D array
A[i, 0] = A[0, i] = i・αgap, ∀i >= 0
for i = 1 to m
  for j = 1 to n
    A[i, j] = min{A[i - 1, j - 1] + αXiYj, A[i - 1, j] + αgap, A[i, j - 1] + αgap}
```

- Reconstructing a Solution
  - A が埋まった状態の A[m, n] から trace back していく
  - A[i, j] について
    - A[i, j] が case 1 で埋められた場合、xi と yj をマッチさせて A[i - 1, j - 1] に進む
    - A[i, j] が case 2 で埋められた場合、xi と gap をマッチさせて A[i - 1, j] に進む
    - A[i, j] が case 3 で埋められた場合、gap と yj をマッチさせて A[i, j - 1] に進む
  - もし i = 0 or j = 0 となったら残っているものを gap で埋める
  - 実行時間は O(m + n)
