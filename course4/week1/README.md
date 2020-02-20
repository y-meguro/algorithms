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
