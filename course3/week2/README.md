# Part 21: Kruskal's Minimum Spanning Tree Algorithm

## Kruskal's MST Algorithm

- やり方
  - コストの昇順で辺をソートしておく。c1 < c2 < ... < cm となる
  - T = 0
  - for i = 1 to m
    - if T ∪ {i} has no cycle
      - Add i to T
  - return T
- 証明
  - 以下を示す
    - Kruskal's algorithm が最小全域木を求められていること
  - T' を Kruskal's algorithm の出力とする
  - T' に巡回はない
  - T' は連結である
    - Empty Cut Lemma より T' がすべての cut をまたいでいることを示す必要がある
    - ここで G は連結であるため、少なくとも 1 つの辺は A, B をまたいでいる
      - Kruskal はそのうちの最初の 1 つの辺を含む
  - T' のすべての辺は Cut Property を満たす
    - edge(u, v) が T に追加されるときを考える
    - T ∪ {(u, v)} は巡回を持たないので、T は u-v のパスを持たない
    - すると (u, v) は A, B をまたぐ最初の辺であり、A, B をまたぐ最小コストの辺
    - よって Cut Property を満たすことが示された
  - 実行時間
    - 最初のソートが O(m log n)
      - ここで m = O(n^2) なので `log m = 2 * log n`、よって O(m log m) = O(m log n)
    - for ループが O(m)
    - サイクルのチェックが O(n)
    - なので普通に実装すると O(m log n) + O(mn) = O(mn)
    - plan
      - サイクルのチェックを O(1) にして、O(m log n) で実行できるようにする

## Union-Find

- The Union-Find Data Structure
  - find(x)
    - x が所属するグループの名前を返す
  - union(ci, cj)
    - グループ ci と cj を 1 つにまとめる
  - Why useful for Kruskal's algorithm
    - Union-Find の objects は Kruskal's algorithm の頂点の集合を表し、groups は連結された components を表す
    - T に edge(u, v) を追加する <=> u と v の component を連結する
- Union-Find Basics
  - motivation
    - O(1) で Kruskal's algorithm のサイクルチェックを実行したい
  - idea 1
    - connected component ごとに leader vertex を持たせる
  - 不変条件
    - 各頂点がその component の leader を指せるようにする
  - key point
    - edge(u, v) が与えられた時、u と v が同じ component にあるか O(1) 時間で確認できること
  - idea 2
    - 2 つの component をマージする時、小さい方の component が大きい方の leader を受け継ぐとする
    - 不変条件を回復するのにかかる最悪実行時間は O(n)。これは 2 つの component が両方 n/2 頂点の時
    - もっと速くしたい
  - Updating Leader Pointers
    - 各頂点の視点から見ると、Kruskal's algorithm の中で leader pointer が更新されるのは θ(log n) 回
- もう 1 度、実行時間の整理
  - ソートに O(m log n)
  - サイクルチェックが O(m) 回
    - 各 iteration で O(1) でチェックできる
  - leader pointer updates が O(n log n) 回
  - トータルで O(m log n) となる

## State-of-the-Art MST Algorithms

- question
  - O(m log n) より速く実行できるか？
  - できる！
    - O(m) randomized algorithm
    - O(mα(n)) deterministic
      - この α(n) は inverse Ackermann function と言われる
      - [巨大数：アッカーマン関数とは | 高校数学の美しい物語](https://mathtrain.jp/ackermann)
      - Optimal deterministic MST algorithm で漸近的な実行時間は、θ(m) と θ(mα(n)) の間にあることはわかっているが、そのどこになるかはわかっていない
