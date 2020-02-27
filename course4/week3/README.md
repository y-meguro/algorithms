# Part 33: Approximation Algorithms for NP-Complete Problems

## A Greedy Knapsnack Heuristic

- Strategies for NP-Complete Problems
  - 3 つあった(復習)
    - Identify computationally tractable special cases
    - Heuristics
    - Exponential time but better than brute-force search
  - この Heuristics の部分を扱う
- Knapsack Revisited
  - input
    - n 個のアイテムが与えられる。それぞれ value vi と size wi を持ち、ナップサックの capacity W も与えられる
  - output
    - subset S ⊆ {1, 2, ..., n} を出力する。S の合計のサイズがキャパシティを超えず、value が最大となっている
- A Greedy Heuristic
  - motivation
    - ideal items have big value, small size
  - step 1
    - ソートして、アイテムを reindex する
      - v1/w1 > v2/w2 > ... > vn/wn
  - step 2
    - この順番で詰めていき、重量を超えた時点で止める
  - 例
    - W = 5
    - v1 = 2, w1 = 1
    - v2 = 4, w2 = 3
    - v3 = 3, w3 = 3
    - とすると {1, 2} を返す
- A Refined Greedy Heuristic
  - step 3
    - step 2 の解か、maximum valuable item かどちらか良い方を返すようにする
  - theorem
    - この 3-step greedy solution は optimal solution の 50% 以上の値を返す
    - 1/2 approximation algorithm と言われる

## Analysis of a Greedy Knapsack Heuristic

- Performance Gurarantee
  - theorem
    - 3-step の greedy solution は optimal solution の 50% 以上の値を返す
  - thought experiment
    - suitable "fraction" を入れることを認めるとする
      - 最後のアイテムについて、サイズがオーバーするときは、部分的に入れてよいものとする
    - 例えば、W = 3, v1 = 3, v2 = 2, w1 = w2 = 2 とする
    - この時、v1 は全て入れられる(100%)。v2 は 50% 入れて、value も半分入れる。計 4 が答えとなる
- Proof Sketch
  - 主張
    - Greedy fractional soution は少なくとも non-fractional feasible solution 程度には良い解となる
  - 証明
    - 1: S を任意の feasible solution とする
    - 2: S では W のうちの l units が埋められているとする
    - 3: greedy fractional solution を使うと、少なくとも l units が埋められる
    - 4: 貪欲法の基準により、3 で使われた vi/wi は 2 で使われているものよりも、サイズあたりの価値が高い
    - 5: よって、3 の解は S 以上の価値となる。証明終わり
- Analysis of Greedy Heuristic
  - step 2 では 1st k items が入っている
  - 3-step greedy algorithm >= total value of 1st k items
  - また step 3 により 3-step greedy algorithm >= value of (k + 1) item となる
  - すると 2・(3-step greedy algorithm) >= total value of 1st (k + 1) items
  - `>= total value of greedy fractional solution`
  - `>= optimal knapsack solution` となり、「3-step の greedy solution は optimal solution の 50% 以上の値を返す」ことが示された
- A Refined Analysis
  - suppose
    - アイテム i のサイズ wi <= capacity W の 10% とする
  - consequence
    - step 2 で、すべてのアイテムを詰められない場合、ナップスナックの 90% 以上が詰められていることになる
    - value of 2-step greedy algorithm >= 90% value of greedy fractional solution
    - `>= 90% value of optimal solution`

## A Dynamic Programming Heuristic for Knapsack

- Arbitrarily Good Approximation
  - goal
    - user-specified parameter ε > 0 を定めて、(1 - ε)-approximation となることを保証する
  - catch
    - εが減ると、実行時間は増える
- The Approach: Rounding Item Values
  - high-level idea
    - 厳密にはわずかに不正確だが、より簡単な方法でナップサック問題の解を得る
  - recall
    - すべての wi と W が整数であれば、ナップサック問題は動的計画法により、O(nW) 時間で解ける
  - alternative
    - すべての vi が整数なら、ナップサック問題は O(n^2・vmax) で解ける(ただし、vmax = maxi{vi})
    - これについては別のビデオで説明する
  - upshot
    - もしすべての vi が n の多項式におさまる小さい整数であるならば、多項式時間のアルゴリズムが知られている
  - plan
    - vi の lower-order bits を切り捨てる
- A Dynamic Programming Heuristic
  - step 1
    - vi を最も近い m の 倍数まで切り下げる
    - vi^ = vi/m の切り捨て とする
  - step 2
    - values v1^, ..., vn^、sizes w1, ..., wn のアイテムについて、動的計画法を利用して問題を解く
    - この実行時間は O(n^2・max vi^)

## Dynamic Programming for Knapsack, Revisited

- 先程の講義で出てきた、実行時間が O(n^2・vmax) となることについて説明する
- The Subproblems and Recurrence
  - subproblems
    - i = 0, 1, ..., n で x= 0, 1, ..., nvmax とする
    - Si,x を first i items のみを利用して、価値 x を満たすための、最小サイズとする
  - recurrence
    - Si,x = min{S(i-1),x, wi + S(i-1),(x-vi)}
- The Algorithm

```
Let A = 2-D array
Base case: A[0, x] = 0 if x = 0, +∞ otherwise
for i = 1, 2, ..., n
  for x = 0, 1, ..., nvmax
    A[i, x] = min{A[i - 1, x], wi + A[i - 1, x - vi]}
Return the largest x such that A[n, x] <= W
```

- 実行時間は O(n^2・vmax)

## Analysis of a Dynamic Programming Heuristic for Knapsack

- Accuracy Analysis 1
  - vi を最も近い m の 倍数まで切り下げる
  - vi^ = vi/m の切り捨て とする
  - すると vi >= m・vi^ >= vi - m
  - また S' を元々の問題の optimal solution、S を我々の heuristic's solution とする
  - すると Σ(i∈S)vi^ >= Σ(i∈S')vi^
- Accuracy Analysis 2
  - Σ(i∈S)vi >= mΣ(i∈S)vi^ >= mΣ(i∈S')vi^ >= Σ(i∈S')(vi - m)
  - thus
    - Σ(i∈S)vi >= (Σ(i∈S')vi) - mn (S'に含まれるのは最大で n 個のアイテム)
  - constraint
    - Σ(i∈S)vi >= (1 -ε)Σ(i∈S')vi
    - 上記を満たすには mn <= εΣ(i∈S')vi となればよい
      - ここで Σ(i∈S')vi の値はわからないが、vmax 以上であることは間違いない
  - sufficient
    - mn = εvmax となるように m を設定する
- Running Time Analysis
  - point
    - m = εvmax/n とすることで、解が >= (1 - ε)・value of optimal solution となる
  - recall
    - 実行時間は O(n^2・vmax^)
  - note
    - すべての i について vi^ <= vi/m <= vmax/m = vmax・n/εvmax = n/ε
    - よって実行時間は O(n^3/ε)