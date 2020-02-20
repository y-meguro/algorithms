# Part 29: The Bellman-Ford Algorithm

## The Single-Source Shortest Path Problem

- input
  - 有向グラフ G = (V, E)、各辺 e ∈ E に対するコスト ce、開始点 s ∈ V が与えられる
- goal
  - すべての到達点 v ∈ V に対して、最短となる s-v path の長さを計算する
- On Dijkstra's Algorithm
  - good news
    - ヒープを使って、O(m log n) で実行できる (n は頂点の数、m は辺の数)
  - bad news
    - 負の辺がある場合、正しくならない
    - あまり分散していない
  - solution
    - Bellman-Ford algorithm
- On Negative Cycles
  - question
    - G が負のサイクルを持っている時、どう shortest path を定義するか
  - solution 1
    - 巡回があっても shortest s-v path を計算する
    - problem
      - undefined や -∞ をどう扱うか
  - solution 2
    - サイクルのない s-v path を計算する
    - problem
      - NP-hard で多項式時間で解けない
  - solution 3
    - インプットのグラフが negative cycle を持たないと仮定する
- Single-Source Shortest Path Problem, Revisited
  - goal は以下のどちらかとする
    - すべての destination v ∈ V に対して、shortest s-v path の長さを計算する
    - negative cycle があることを出力する
- Optimal Substructure(Informal)
  - intuition
    - shortest path の subpath も最短となる
  - issue
    - subproblem が "smaller" か "larger" かどう決定すべきか不明瞭
  - key idea
    - path に含まれる辺の数を制限する
    - subproblem size <=> number of permitted edges
- Optimal Substructure(Formal)
  - lemma
    - 有向グラフ G = (V, E) が、各辺の長さ ce と開始点 s と共に与えられる
    - すべての v ∈ V, i ∈ {1, 2, ...}, let P = shortest s-v path with at most i edges とする
    - case 1
      - もし P has <= (i - 1) edges の場合は shortest s-v path も (i - 1) edges 以下
    - case 2
      - もし P が last hop (w, v) も含めて i edges であるとすると、P' は (i - 1) edges 以下でできる s-w の 最短パス
  - 到達点 v から考えて、含まれる subproblem の数は 1 + in-degree(v)
    - 1 は case 1 の場合

## The Basic Algorithm

- The Recurrence
  - notation
    - Li,v を i edges 以下の s-v path の最短の長さとする
    - 巡回も許す
    - i edges 以下の s-v path がない場合は +∞ と定義する
  - recurrence
    - すべての v ∈ V, i ∈ {1, 2, ...} に対して Li,v = min{L(i-1),v, min(w,v)∈E{L(i-1,w) + cwv}}
- If No Negative Cycles
  - now
    - グラフ G は no negative cycle とする
    - ならば、shortest path は cycle を持たない
    - すると n - 1 edges 以下となる
  - point
    - negative cycle がない場合、解くべき subproblems は n - 1 以下
  - subproblems
    - Li,v をすべての i ∈ {0, 1, ..., n - 1} とすべての v ∈ V について計算する
- The Bellman-Ford Algorithm
  - A を 2 次元配列とする
  - base case
    - A[0, s] = 0, またすべての v != s となる v で A[0, v] = +∞ とする
  - algorithm

```
for i = 1, 2, ..., n - 1
  for each v ∈ V
    A[i, v] = min{A[i - 1, v], min(w,v)∈E{A[i - 1, w] + cwv}}
```

- 実行時間
  - O(n・Σin-deg(v)) = O(mn)
- Stopping Early
  - もし j < n - 1 で A[j, v] = A[j - 1, v] とすべての点 v でなった場合は、もうそこから変化しないので、終了してよい

## Detecting Negative Cycles

- Checking for a Negative Cycle
  - claim
    - G が negative-cost cycle を持たない(s から届く範囲で) <=> Bellman-Ford algorithm で、A[n - 1, v] = A[n, v] for all v ∈ V となる
  - なので、iteration を 1 回多くしてチェックすればいい
- 証明
  - => は証明済みなので、<= を示す
  - A[n, v], A[n - 1, v] の代わりに d(v) を使う
  - すると A[i, v] = min{A[i - 1, v], min(w,v)∈E{A[i - 1, w] + cwv}} なので d(v) <= d(w) + cwv <=> d(v) - d(w) <= cwv
  - ここで任意の cycle C を考えると上記より
    - Σ(w,v)∈C cwv >= Σ(w,v)∈C (d(v) - d(w)) = 0 となるので、負の cycle がないことが示された

## Space Optimization

- Bellman-Ford で必要となる空間は O(n^2)
- Predecessor Pointers
  - note
    - A[i, v] を計算するために必要なのは A[i-1, v] のみ
    - O(n) だけ覚えていれば次の計算はできる
  - concern
    - table が全て埋まっていなくても shortest path を再構築できるか
- Computing Predecessor Pointers
  - idea
    - 2 つ目のテーブル B を計算し、B[i, v] には、i edges 以下の s-v path の最後から 2 番目の頂点(v の前)を入れるようにする
  - これが計算できるのであれば、B[n - 1, v] からはじめて、s にたどりつくまで辿っていけば s-v path がわかる
  - base case
    - すべての v ∈ V について B[0, v] = NULL
  - i > 0 の場合
    - case 1
      - B[i, v] = B[i - 1, v]
    - case 2
      - B[i, v] = the vertex w achieving the minimum

## Internet Routing

- From Bellman-Ford to Internet Routing
  - source-driven ではなく destination-driven で考える
    - すべての頂点 v で、目的地 t への最短パスにつながる first hop を覚えておく
  - A[i, v] を計算するには A[i - 1, v] を計算しておく必要があるが、internet scale でこれを同期的に解くのは難しい
    - なので pull-based ではなく、push-based で計算しておく
  - static network でない限り収束することが保証されない
    - 各 v は next hop だけでなく、entire shortest path を覚えておくようにする
    - Pro
      - More robust to failures
      - Permits more sophisticated route selection
    - Con
      - More space required

# Part 30: All-Pairs Shortest Paths

## Problem Definition

- input
  - 有向グラフ G = (V, E) が各辺 e ∈ E のコスト ce と共に与えられる
- goal
  - 以下のどちらかを出力する
    - すべての u, v ∈ V のペアに対して、最短の u-v path の長さ
    - negative cycle を含んでいること

## Optimal Substructure

- Motivation
  - Floyd-Warshall algorithm
    - O(n^3) 時間かかる
    - negative edge length があっても大丈夫
- Optimal Substructure
  - G は negative cycle を持たないとする
  - 任意の source i ∈ V, destination j ∈ V, k ∈ {1, 2, ..., n} を定める
  - V(k) = {1, 2, ..., k} とする
  - ここで P = shortest (cycle-free) i-j path with all internal nodes in V(k)
  - P のすべての internal nodes は V(k) に含まれていなければならない
  - case 1
    - k が P の internal node に含まれない場合
    - P は V(k - 1) で構成される shortest (cycle-free) i-j
  - case 2
    - k が P の internal node に含まれる場合
    - P1 = V(k - 1) で構成される shortest (cycle-free) i-k
    - P2 = V(k - 1) で構成される shortest (cycle-free) k-j

## The Floyd-Warshall Algorithm

- The Floyd-Warshall Algorithm

```
Let A = 3-D array(indexed by i, j, k)
base cases: すべての i, j ∈ V に対して
A[i, j, 0] = 0 if i == j
           = cij if (i, j) ∈ E
           = +∞ if i != j and (i, j) ∉ E
for k = 1 to n
  for i = 1 to n
    for j = 1 to n
      A[i, j, k] = min{A[i, j, k - 1], A[i, k, k - 1] + A[k, j, k - 1]}
```

- 実行時間
  - 各 subproblem に対して O(1)
  - 全部で O(n^3)
- Odds and Ends
  - question 1
    - G が negative cycle を含む場合はどうなるか？
      - A[i, i, n] < 0 となる i ∈ V が少なくとも 1 つはある
  - question 2
    - どうやって最短の i-j path を再構築するか？
      - すべての i, j に対して B[i, j] = max label of an internal node on a shortest i-j path を計算しておく
        - もし B[i, j] = k だったら再帰的に A[i, j, k] を計算すれば良い

## A Reweighting Technique

- Motivation
  - recall
    - APSP(All-Pairs Shortest Paths) は SSSP(Single-Source Shortest Path) を n 回実行するまで実行時間を減らすことができる
    - つまり、nonnegative edge length の場合の Dijkstra だと O(m・n・log n)
    - general edge length の場合の Bellman-Ford だと O(m・n^2)
  - Johnson's algorithm
    - APSP を 1 回の Bellman-Ford(O(m・n)) と n 回の Dijkstra(O(m・n・log n)) まで減らすことができる
  - つまり実行時間は O(m・n) + O(m・n・log n) = O(m・n・log n)
- Quiz
  - 各点 v ∈ V に対して、実数 pv をそれぞれ設定するとする
  - すべての辺 e = (u, v) のコスト ce を変形して、ce' = ce + pu - pv とする
  - この時 s-t path P の長さを L とする(ce を利用した時)。ce' を利用した場合の長さはどうなるか
    - ce' を利用した場合、L + ps - pt となる
- Reweighting
  - summary
    - vertex weights {pv} を使って reweighting する
    - すべての s-t path に同じ量 (ps - pt) を加算する
  - この操作を行っても、選ばれる shortest path 自体は変わらない
    - 値はこれまでの値 + ps - pt となる
  - Why useful?
    - G が negative edge length を持っているとする
    - some {pv} を利用して reweighting すると、すべての edge length を nonnegative にできる
      - このような pv は Bellman-Ford を利用して計算できる
      - すると、このグラフに対して Dijkstra を適用できる

## Johnson's Algorithm

- input
  - 有向グラフ G = (V, E) が 辺の長さ ce と共に与えられる
- 手順
  - 1: 以下のように G' を作成する
    - new vertex s を追加
    - すべての v ∈ G に対して、new edge (s, v) を length 0 で追加
  - 2: Bellman-Ford を G' の source s に対して実行する
    - もし negative-cost cycle を見つけたら、終了する
  - 3: すべての v ∈ G に対して pv = length of a shortest s-v path in G' とする
    - そして各辺 edge e = (u, v) ∈ G について ce' = ce + pu - pv とする
  - 4: G の各頂点 u を source にして Dijkstra を実行する(この時の length は ce' を使う)
    - これにより、shortest-path distance d'(u, v), v ∈ G を計算する
  - 5: 各ペア u, v ∈ G に対して、最短距離 d(u, v) = d'(u, v) - pu + pv
- Analysis of Johnson's Algorithm
  - 実行時間は手順ごとに以下のようになる
    - 1: O(n)
    - 2: O(mn)。これは Bellman-Ford の実行時間
    - 3: O(m)
    - 4: O(nm・log n)
    - 5: O(n^2)
  - これらの合計 O(mn・log n) がこのアルゴリズムの実行時間となる
    - これは O(n^3) と比べて、疎グラフの場合、改善されている(m の値が n^2 より n に近い場合)
- Correctness of Johnson's Algorithm
  - 以下を証明する
    - すべての辺 e = (u, v) に対して、reweighted length ce' = ce + pu - pv が nonnegative となること
  - 証明
    - 以下のように定義する
      - pu = G' での s-u の shortest path の長さ
      - pv = G' での s-v の shortest path の長さ
      - P = a shortest s-u path in G'
    - すると P + (u, v) = an s-v path with length pu + cuv
    - => shortest s-v path の pv が最も小さいので pv <= pu + cuv
    - => cuv' = cuv + pu - pv >= 0
    - よって、nonnegative であることが示された
