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

## Matrix Multiplication

- ベクトルの内積
  - n 次のベクトルの内積の計算を考える
  - X・Y = Z となる時、zij = (ith row of X)・(jth column of Y) = ΣXik・Ykj (Σの範囲は k=1 から n まで)
  - 各 zij について n 回の計算が必要、zij は n^2 個あるので、普通に計算すると θ(n^3) の計算量となる
  - これを効率良くできないか考える
- Applying Divide and Conquer
  - idea
    - X を A, B, C, D の 4 つのブロック、Y を E, F, G, H の 4 つのブロックにわけて X・Y を AE + BG, AF + BH, CE + DG, CF + DH の 4 つとして考えるようにする
- Recursive Algorithm
  - 上記の idea をもとに再帰的に解く
  - step1: X・Y は 8 個の積から構成されるため、その 8 個の積を計算する
  - step2: それぞれを加算する(これに必要なのは θ(n^2) 時間)
  - これを計算すると実行時間は θ(n^3) となる(詳細は the master method で扱う)。これは普通に考えた場合と同じ
  - 8 個の部分問題を減らしたい
- Strassen's Algorithm(1969)
  - 7 個の部分問題に分割する
  - 必要な加算と減算を行う(θ(n^2) 時間で行う)
  - これを行うと結果として、n^3 より良い実行時間となる
- Strassen's Algorithm の詳細
  - 先程と同様に、X を A, B, C, D の 4 つのブロック、Y を E, F, G, H の 4 つのブロックにわけて考える
  - P1 = A(F - H), P2 = (A + B)H, P3 = (C + D)E, P4 = D(G - E), P5 = (A + D)(E + H), P6 = (B - D)(G + H), P7 = (A - C)(E + F) とする
  - すると X・Y は P5 + P4 - P2 - P6, P1 + P2, P3 + P4, P1 + P5 - P3 - P7 の 4 つとして計算できる

## The Closest Pair Problem

- 問題の内容
  - input
    - P = {p1, ..., pn} の n 個の点が実数空間上に与えられる
  - notation
    - d(pi, pj) を pi = (xi, yi) と pj = (xj, yj) の距離とし、`d(pi, pj) = ((xi - xj)^2 + (yi - yj)^2)^1/2` とする
  - output
    - すべての p, q (p, q ∈ P) の組み合わせの中から、d(p, q) が最小となるものを探す
- Initial Observations
  - Brute-force search
    - θ(n^2) かかる
  - ここで 1 次元の場合の Closest Pair を考える
    - 1: Sort points (`O(n * log(n))` かかる)
    - 2: 順々に隣接する点を調べて、closest pair を返す (O(n) かかる)
  - 1 次元の場合を応用して、`O(n * log(n))` で 2 次元の場合もできるように考える
- High-Level Approach
  - 点をコピーして、x 座標でソートした Px と y 座標でソートした Py の 2 つを作る
- ClosestPair(Px, Py) の擬似コード
  - 1: Q = left half of P, R = right half of P. Qx, Qy, Rx, Ry を作る (O(n) time。Q の中から x と y、R の中から x と y を選ぶ)
  - 2: (p1, q1) = ClosestPair(Qx, Qy)
  - 3: (p2, q2) = ClosestPair(Rx, Ry)
  - 4: δ = min{d(p1, q1), d(p2, q2)}
  - 5: (p3, q3) = ClosestSplitPair(Px, Py, δ)
  - 6: Return best of (p1, q1), (p2, q2), (p3, q3)
- ClosestSplitPair(Px, Py, δ) の擬似コード
  - Q の中で x 座標が最大のものの値を x' とすると、[x'-δ, x'+δ] の範囲を調べれば良い (x'を得るのに O(1) 時間)
  - Sy を上記の x 座標で限定された、y 座標でソートされた集合とする (Sy を得るのに O(n) 時間)
  - ClosestSplitPair は以下のようになり、実行時間は O(n) となるので、全体で `O(n * log(n))` で実行できる

```
ClosestSplitPair(Px, Py, δ)
Initialize best = δ, best pair = NULL
for i = 1 to |Sy| - 1
  for j = 1 to min{7, |Sy| - i}
    Let p, q = ith, (i + j)th points of Sy
    if d(p, q) < best
      best pair = (p, q)
      best = d(p, q)
```

- 上記のアルゴリズムが正しく働くことを示すには、以下の証明が必要
  - p ∈ Q, q ∈ R として、d(p, q) < δ となるならば
    - A: p と q は両方とも Sy に含まれる
    - B: p と q は Sy の中で、最大でも 7 つしか離れていない
  - A の証明
    - p = (x1, y1) ∈ Q, q = (x2, y2) ∈ R, d(p, q) <= δ とする
    - d(p, q) <= δ なので、|x1 - x2| <= δ かつ |y1 - y2| <= δ
    - p ∈ Q => x1 <= x' かつ q ∈ R => x2 >= x' なので、x1, x2 ∈ [x'-δ, x'+δ] となることが示された
  - B の証明
    - key
      - x' を中心、bottom を min{y1, y2} とする、δ/2 × δ/2 の 8 つの領域を考える
      - y 座標でソートされた Sy の各点は 8 つの領域の中に、最大でも 1 つしか入れない(距離が δ 以下になってしまうため)
      - よって自分が属している領域を除いて、最大 7 つ調べれば十分であることが示された
    - これは資料の絵を見た方がわかりやすい
