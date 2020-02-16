# Part 10: Graph Search and Connectivity

## Generic Graph Search

- goals
  - find everything findable from a given start vertex
  - don't explore anything twice
- generic algorithm
  - graph G とスタートとなる頂点 s が与えられる
  - 最初 s を explored とし、他のすべての点は unexplored の状態
  - while possible:
    - edge (u, v) を選択する (u は explored、v は unexplored)
    - v を explored とする
- claim
  - algorithm が終了する時、v explored ⇔ G は s から v へのパスを持つ

## BFS vs DFS

- Breadth-First Search(BFS)
  - FIFO で計算(queue)
  - explored nodes in "layers"
  - can compute shortest paths
  - can compute connected components of an undirected graph
    - DFS でもできるのでは？
  - 実行時間は O(m + n) で線形時間
- Depth-First Search(DFS)
  - LIFO で計算(stack)
  - explore aggressively like a maze, backtrack only when necessary
  - compute connected ordering of a directed acyclic graph
  - compute connected components in a directed graph
    - BFS でもできるのでは？
  - 実行時間は O(m + n) で線形時間

## BFS

- コード

```
BFS(graph G, start vertex s)
// 全ての頂点は開始時に unexplored の状態
mark s as explored
let Q = queue data structure (FIFO), initialized with s
while Q = φ:
  remove the first node of Q, call it v
  for each edge(v, w)
    if w unexplored
      mark w as explored
      add w to Q
```

- Basic BFS Properties
  - BFS の終了時、v explored ⇔ G は s から v へのパスを持つ
  - while loop の中の実行時間は O(ns + ms)。ns は s から到達可能な頂点の数、ms は s から到達可能な辺の数
    - for loop は辺の数だけ、explored のチェックは頂点の数だけ
- Shortest Paths
  - goal
    - dist(v) の計算。s から v へ到達するまでの最小の辺数
  - 先程のコードに以下を追加する
    - initialize dist(v) = 0 (if v = s), ∞ (if v != s)
    - when considering edge(v, w)
      - if w unexplored, then set dist(w) = dist(v) + 1
  - dist(v) = i ということは v が i 番目の layer にいるということ
- Undirected Connectivity
  - G(V, E) を無向グラフとする
  - Connected components: the "pieces" of G
    - connected components に含まれる 2 頂点間にはパスが存在する。なければ別の component
  - goal
    - すべての connected components を計算する
- Connected Components via BFS
  - initialize all nodes as unexplored
  - for i = 1 to n
    - if i not yet explored
      - BFS(G, i) // これで頂点 i の connected component が見つかる
  - 実行時間は O(m + n)

## DFS

- コード

```
DFS(graph G, start vertex s)
mark s as explored
for every edge(s, v)
  if v unexplored
    DFS(G, v)
```

- Basic DFS Properties
  - DFS の終了時、v explored ⇔ G は s から v へのパスを持つ
  - 実行時間は O(ns + ms)。ns は s から到達可能な頂点の数、ms は s から到達可能な辺の数
    - 各頂点は最大 1 回、各辺は最大 2 回登場する
- Topological Sort
  - 有向グラフ G のトポロジカルオーダーとは、以下のように G の各頂点をラベル付けすることである
    - The f(v)'s are the set {1, 2, ..., n}
    - (u, v) ∈ G => f(u) < f(v)
  - もし G が巡回グラフだと、G はトポロジカルオーダーを持たない
  - トポロジカルオーダーの計算時間は O(m + n)
- solution
  - どんな有向非巡回グラフでも sink vertex を持つ
    - sink vertex: そこから他の点への辺を持たないもの(他の点から向かってくる辺のみ)
  - トポロジカルソートの計算方法
    - let v be a sink vertex of G
    - set f(v) = n
    - recurse on G-{v}
  - DFS でのトポロジカルソートの実装

```
DFS-Loop(graph G)
mark all nodes unexplored
current_label = n
for each vertex
  if v not yet explored
    DFS(G, v)

DFS(graph G, start vertex s)
for every edge(s, v)
  if v not yet explored
    mark v explored
      DFS(G, v)
set f(s) = current_label            // ここは帰りがけ順でセットされる
current_label = current_label - 1
```

- 実行時間は O(m + n)

## Strongly Connected Components (SCCs, 強連結成分分解)

- 有向グラフ G の SCCs とは以下の関係を持つグループのこと
  - u から v へのパスを持ち、v から u へのパスも持つ
  - [強連結成分分解の意味とアルゴリズム | 高校数学の美しい物語](https://mathtrain.jp/kyorenketsu)
- Kosaraju's Two-Pass Algorithm
  - SCCs の計算を O(m + n) で実行できる
  - algorithm
    - 有向グラフ G が与えられるとする
    - Let Grev = G with all arcs reversed
    - Run DFS-Loop on Grev
    - Run DFS-Loop on G
      - この時、最初の DFS-Loop on Grev で f(i) が大きいものから順に DFS していく
      - leader が同じものが同じ強連結成分

```
DFS-Loop(graph G)
Global variable t = 0
Grobal variable s = NULL
Assume nodes labeled 1 to n
for i = n down to 1
  if i not yet explored
    s = i
    DFS(G, i)

DFS(graph G, node i)
mark i as explored
set leader(i) = node s
for each arc(i, j) in G
  if j not yet explored
    DFS(G, j)
t++
set f(i) = t
```

- 観察
  - 有向グラフ G の強連結成分分解は、非巡回の "meta-graph" を想起させる
  - meta-nodes は SCCs の C1, ..., Ck
  - ∃ arc C → C' <=> ∃ arc(i, j) ∈ G with i ∈ C, j ∈ C'
- key lemma
  - lemma
    - 2 つの隣接する SCCs を考える
      - G において C1 → C2 とする
    - let f(v) = finishing times of DFS-Loop in Grev
      - すると C1 に含まれる f(v) の最大値より、C2 に含まれる f(v) の最大値のほうが大きくなる
  - corollay
    - maximum f-value of G must lie in a "sink SCC"

## Structure of the Web

- The Web graph
  - 頂点は web pages、(有向)辺はハイパーリンク
  - サイズは ~200 million nodes, ~1billion edges
- The Bow Tie
  - 蝶ネクタイのように、中心に giant SCC(core of the web)、両脇に IN(new web pages など) と OUT(corporate websites など)があり、giant SCC の他に IN と OUT を結ぶものとして tubes があり、また IN から giant SCC 以外に出ていくもの・OUT に giant SCC 以外から入っていくものとして tendrils がある(資料の図がわかりやすいから見ること)
- main findings
  - All 4 parts(giant, IN, OUT, tubes + tendrils) はだいたい同じサイズ
  - Within CORE, very well connected
  - Outside, surprisingly poorly connected
