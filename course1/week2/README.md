各授業で習ったことの抜粋、および自分で調べたことや感じたことのメモを書いています

# Part 3: Divide & Conquer Algorithms

## The Divide and Conquer Paradigm

- 1: Divide into smaller subproblems
- 2: Conquer via recursive calls
- 3: Combine solutions of subproblems into one for the original problem.

## Counting Inversions

- 問題の内容
  - Input: 1〜n までの数字が任意の順番で入っている配列 A
  - Output: number of inversions。すなわち i < j かつ A[i] > A[j] となっている pairs(i, j) の数
  - 例えば {1, 3, 5, 2, 4, 6} が与えられる時、inversions は (3, 2), (5, 2), (5, 4) となる
- Motivation
  - numerical similarity measure between two ranked lists
  - inversions の数が近いと、2 つのリストは似ているってことか
- High-Level Approach
  - Brute-force
    - θ(n^2) 回、だがこれよりもっとよくできる。key idea は Divide + Conquer
  - i と j について以下の 3 つの場合にわける。Left と Right の場合は再帰的に解けばよい。Split については専用の subroutine が必要
    - Left: if i, j <= n/2
    - Right: if i, j > n/2
    - Split: if i <= n/2 < j
- High-Level Algorithm
  - 以下の CountSplitInv を O(n) で実装できれば、全体を `O(n * log n)` で実行できる

```
Count(array A, length n)
if n == 1
  return 0
else
  X = Count(1st half of A, n/2)
  Y = Count(2nd half of A, n/2)
  Z = CountSplitInv(A, n)        // ここはまだ実装してない
  return X + Y + Z
```

- Piggybacking on Merge Sort(piggybacking: 肩に乗る、便乗する)
  - key idea
    - have recursive calls both count inversions and sort
- High-Level Algorithm(revised)

```
Sort-and-Count(array A, length n)
if n == 1
  return 0
else
  (B, X) = Sort-and-Count(1st half of A, n/2)  // B は 1st half of A がソートされたもの
  (C, Y) = Sort-and-Count(2nd half of A, n/2)  // C は 2nd half of A がソートされたもの
  (D, Z) = Merge-and-CountSplitInv(B, C, n/2)  // D は A がソートされたもの。ここはまだ実装してない
  return X + Y + Z
```

- Merge-and-CountSplitInv
  - 2 つの sort された subarray をマージする時(左を B、右を C とする)、C の要素が D に書き込まれる時、B に残っている要素数文をインクリメントすればよい
  - この実行時間は、マージに O(n)、count に O(n) かかるので、合計 O(n) となる
  - 以上より、Sort-and-Count 全体を `O(n * log n)` で実行できることが示された
