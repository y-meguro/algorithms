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

# Part 22: Clustering

## Clustering

- informal goal
  - n 個の "points" を "coherent groups" に分類する
- 仮定
  - input に対して (dis)similarity measure が与えられるとする
    - 例えば、距離 d(p, q) のようなもの
    - d(p, q) = d(q, p)
- goal
  - same cluster <=> "nearby"

## Max-Spacing k-Clusterings

- 仮定
  - k = # of clusters desired とする
  - p と q が separated の場合、2 つは異なるクラスタに所属するとする
- 定義
  - The spacing of a k-clustering is `min separated p,q d(p, q)`
    - これが大きいほうがよい
- Peoblem statement
  - distance measure d と k が与えられた時、maximum spacing の k-clustering を計算する
- A Greedy Algorithm
  - 最初にすべての頂点を別々のクラスタに入れる
  - Repeat only k clusters
    - Let p, q = closest pair of separated points
    - p と q を同じクラスタにマージする
- 上記の貪欲法が正しいことの証明
  - C1, ..., Ck を spacing S の greedy clustering とする
  - C1^, ..., Ck^ を任意の別のクラスタリングとする。これのスペースが S 以下であることを示す
  - Case 1
    - Ci^ が Ci と等しい場合は、same spacing S を持つ
  - Case 2
    - Case 1 でない場合は、以下の条件を満たす p, q が存在する
      - p, q は共通のクラスタ Ci に属する
      - p, q は異なるクラスタ Ci^, Cj^ に属する
- greedy algorithm の特徴
  - もし 2 点 x, y が直接マージされる場合、d(x, y) <= S
- Easy case: p と q が直接マージされていた場合
  - ここで Case 2 の場合を考える。p と q は Ci にマージされているので、S >= d(p, q)。また、異なるクラスタに属しているので、C1^, ..., Ck^ の spacing 以上の大きさを持つ。つまり、`S >= d(p, q) >= spacing of C1^, ..., Ck^`
- Tricky case: p と q が間接的にマージされた場合
  - p と q は p, a1, a2, ..., al, q のパスで直接マージされているとする
  - key point
    - p ∈ Ci^, q ∉ Ci^ であるため、ある連続する aj, aj+1 について aj ∈ Ci^, aj+1 ∉ Ci^ となる
    - すると以下より、S >= d(aj, aj+1) >= Spacing of C1^, ..., Ck^ が示される
      - S >= d(aj, aj+1) については、aj, aj+1 が直接マージされているため
      - d(aj, aj+1) >= Spacing of C1^, ..., Ck^ については、aj, aj+1 が separated のため
