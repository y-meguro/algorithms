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

# Part 23: Advanced Union-Find

## Lazy Unions

- 概要
  - new idea
    - update only one pointer each merge!
      - 既存の leader から 新しい leader を指すようにする
      - 資料の図がわかりやすい
  - マージ方法
    - 2 つのグループをマージする時、片方のグループの leader をもう片方の leader の子どもにする
  - Pro
    - union 処理が、たった 1 つの pointer を更新するだけで済む
  - Con
    - leader を探すために、parent pointer の path を辿る必要がある
- 実装
  - 各 object x ∈ X は親を持つ
  - 不変条件
    - parent pointers は X の中で有向木を導く (x is a root <=> parent[x] = x)
  - 初期化
    - 最初はすべての x について、parent[x] = x
  - find(x)
    - root にたどり着くまで、x から parent pointers をたどっていく
  - union(x, y)
    - s1 = find(x), s2 = find(y) として、どちらかの親をもう片方のものにする
- Union by Rank
  - 各 x ∈ X について、rank[x] を維持するようにする
  - 不変条件
    - すべての x ∈ X について、rank[x] = maximum number of hops from leaf to x
  - 不揃いな木にしないために rank を使う
    - s1 = find(x), s2 = find(y) として、rank[s1] > rank[s2] の場合、parent[s2] を s1 にする。逆の場合、parent[s1] を s2 にする
  - todo
    - update ranks to restore invariant
      - もし s1 と s2 が異なる場合は何も変わらない。等しい場合は s2 の rank を 1 つあげる
      - root の rank のみ大きくなっていく(root じゃない場合は変わらない)
- rank lemma
  - 任意の順番での union(+find) 操作を考える
  - rank r に対して、最大で n/2^r 個のオブジェクトが存在する
- rank lemma の証明
  - claim 1
    - x と y が同じランク r を持つなら、それらの subtree は接続していない
  - claim 2
    - rank r のオブジェクトの subtree のサイズ >= 2^r
  - claim 1 の証明
    - 対偶を示すことを考える
    - x と y の subtree が object z を共通で持つとする
    - => ∃ paths z → x, z → y が存在する
    - => x と y のどちらかがどちらかの祖先になる
    - => その祖先は、もう片方より大きい rank となる
    - よって対偶が示された
  - claim 2
    - base case
      - すべての rank は 0、すべての subtree のサイズは 1
    - inductive step
      - なにかのオブジェクトの rank が変更しない限り、subtree のサイズが大きくなるだけなので、何も示すことはない
    - interesting case
      - union(x, y) をする時、s1 = find(x), s2 = find(y), rank[s1] = rank[s2] = r => s2 の new rank = r + 1 となる
      - => s2 の subtree のサイズ = s2's old subtree size + s1's old subtree size
      - これは両方とも 2^r 以上のサイズなので、合計は 2^r+1 以上のサイズとなる

## Path Compression

- Path Compression
  - idea
    - なぜ何度も leaf-root path を辿らなければならないのか
  - path compression
    - find(x) を行ったあと、root までの shortcut を保持しておく
  - Pro
    - find のスピードアップ
  - Con
    - Constant-factor overhead to find
- Hopcroft-Ullman Theorem
  - path compression を使うと、m Union + Find operation が `O(m log* n)` 時間で実行できる
  - ここで `log* n` は n に対して、result <= 1 となるまで log をかける回数。例えば `log* 2^65536 = 5` となる
    - `log* (2^2..(t times)..^2) = t`
- Measuring Progress
  - intuition
    - shortcut を利用することで、Finds + Unions がスピードアップする
  - question
    - How to track this progress and quantify the benefit?
  - idea
    - non-root object x を考える(rank[x] は固定されることを思い出す)
  - progress measure
    - rank[parent[x]] - rank[x]
    - この progress measure が増えると path compression が増える
- 証明
  - rank blocks
    - {0}, {1}, {2, 3, 4}, {5, ..., 2^4}, {17, ..., 2^16}, {65537, ..., 2^65536}, ..., {..., n}
    - `O(log* n)` 個の異なる rank block がある
  - semantics
    - Traversal x → parent(x) が "fast progress" <=> rank[parent[x]] in larger block than rank[x]
  - definition
    - object x が good ならば以下のどちらかを満たす
      - x または x's parent が root
      - rank[parent[x]] in larger block than rank[x]
    - bad の場合は上記以外の場合
  - point
    - good nodes のみなら、find で探索するのは `O(log* n)` 個(parent は自身のブロックと異なるため)
  - upshot
    - m 回の操作を合計すると `O(m log* n) + total # of visits to bad nodes`
  - もし bad node を訪れてしまった場合、good nodes に辿りつくまでに何回かの操作が必要
    - bad node に含まれる node は各 rank block について最大でも n 個
    - rank block の数は `O(log* n` なので、total work は `O((m + n)log* n)`

## The Ackermann Function

- base case
  - すべての r >= 1 に対して A0(r) = r + 1
- in general
  - k, r >= 1 に対して Ak(r) = Apply Ak-1 r times to r = (Ak-1・Ak-1・...・Ak-1)(r)
    - A1(r) だと `(A0 ❍ A0 ❍ ... ❍ A0)(r) = ((r + 1) + 1) + ... + 1 = 2r`
    - A2(r) だと `(A1 ❍ A1 ❍ ... ❍ A1)(r) = ((r * 2) * 2) * ... * 2 = r * 2^r`
    - なので例えば A3(2) だと A2(r) を 2 回適用することになる。つまり `2 * 2^2 = 8` なので `A3(2) = 8 * 2^8 = 2048`
    - A4(2) だと A3(A3(2)) = A3(2048) >= 2^2^2...^2 (2048回) となり、A4(r) は巨大な数字となる
- The Inverse Ackermann Function
  - 定義
    - すべての n >= 4 に対して、α(n) = minimum value of k such that Ak(2) >= n
      - A1(2) = 4, A2(2) = 8, A3(2) = 2048
  - α(n)
    - α(n) = 1 となるのは n = 4
    - α(n) = 2 となるのは n = 5, ..., 8
    - α(n) = 3 となるのは n = 9, ..., 2048
    - α(n) = 4 となるのは n = 2049, ...

## Tarjan's Analysis

- Tarjan's Bound
  - With Union by Rank and path compression で、m 回の union + find の操作を O(mα(n)) 時間で実行できる
    - α(n) はアッカーマンの逆関数
- Building Blocks of Hopcroft-Ullman Analysis
  - block 1
    - Rank Lemma
      - rank r には最大 n/2^r 個のオブジェクト
  - block 2
    - path compression => もし x の親が p から p' に更新されるならば rank(p') >= rank(p) + 1
  - new idea
    - block 2 で rank(p) + 1 を 1 ではなく、より大きくすることを考える
- Quantifying Rank Gaps
  - non-root object x を考える
  - 定義
    - δ(x) = max value of k such that rank[parent[x]] >= Ak(rank[x])
  - 例
    - δ(x) = 1 <=> rank[parent[x]] >= 2・rank[x]
    - δ(x) = 2 <=> rank[parent[x]] >= rank[x]・2^rank[x]
  - note
    - すべての object x の rank[x] >= 2 に対して δ(x) <= α(n) となる
      - Aα(n) (2) >= n >= rank[parent[x]] >= Aδ(x) (rank[x])、ここで rank[x] >= 2 なので、α(n) >= δ(x) となる
- Good and Bad objects
  - 再定義する
  - object x が bad であれば以下のすべてを満たす
    - x が root でない
    - parent(x) が root でない
    - rank(x) >= 2
    - x が祖先 y を持ち、δ(y) = δ(x)
  - その他の場合、x は good
- Tarjan's Bound の証明
  - upshot
    - m 回の操作の合計処理は `O(mα(n)) + total # of visits to bad objects`
  - path compression
    - bad object x に訪問した場合を考える。x → p → ... → y → p' → ... → new parent とする
    - rank[x's new parent] >= rank[p'] >= Ak(rank[y]) >= Ak(rank[p])
      - x は bad object なので δ(x) = δ(y) = k とする
  - point
    - path compression は Ak function を rank[x's parent] まで適用する
    - なので rank[x's parent] >= (Ak ❍ ... r times ... ❍ Ak)(r) = Ak+1(r)
  - thus
    - while x is bad, every r visits increases δ(x) => <= rα(n) visits to x while it's bad
  - 以上より、`O(mα(n)) + total # of visits to bad objects <= Σ rank[x]α(n) = α(n)Σ(r>=0) r` これは # of objects with rank r
  - `= nα(n)Σ(r>=0) r/2^r`
  - ここで `Σ(r>=0) r/2^r = O(1)` なので `nα(n)Σ(r>=0) r/2^r = O(nα(n))`
