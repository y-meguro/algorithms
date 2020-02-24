# Part 31: NP-Complete Problems

## Polynomial-Time Solvable Problems

- Ubiquitous Intractability
  - sad fact
    - 多くの重要な問題は効率的に解くことができない
  - next
    - NP-completeness(NP完全性) を利用して、computational intractability について扱う
- Polynomial-Time Solvability
  - 定義
    - ある定数 k を用いて O(n^k) でアルゴリズムの実行時間が表せる場合、polynomial-time solvable という
- The Class P
  - 定義
    - P = 多項式時間で解決可能な問題の集合
  - 例
    - ここまでにこのコースで見てきたアルゴリズムすべて
- Traveling Salesman Problem
  - input
    - 負のコストを持たない完全無向グラフ
  - output
    - min-cost tour(すべての頂点に 1 度ずつ訪れる)
  - conjecture
    - この問題を多項式時間で解けるアルゴリズムは存在しない

## Recuctions and Completeness

- Reductions
  - 相対的な複雑さについてはたくさん言及されている
- 定義
  - Problem Π1 が problem Π2 に帰着する場合、もし Π2 を多項式時間で解けるなら、Π1 も多項式時間で解ける
- Completeness
  - 上の「Π2 を多項式時間で解けるなら、Π1 も多項式時間で解ける」の対偶をとると「Π1 が P でなければ、Π2 も P ではない」となる
  - つまり Π2 は少なくとも Π1 と同程度の難しさを持つ
  - 定義
    - C を問題の集合とする
    - Π を C-Complete とするならば以下が共に当てはまる
      - 1: Π ∈ C
      - 2: C に含まれる全ては Π に帰着する
    - Π は C の中で最も難しい問題
- Choice of the Class C
  - idea
    - TSP は C-complete であることを示したい
  - contrast
    - TSP definitely solvable in finite time
  - refined idea
    - TSP は全ての brute-force-solvable problems と同じくらい難しい

## Definition and Interpretation

- The Class NP
  - refined idea
    - TSP は brute-force-solvable 問題と同じくらい困難であることを示す
  - definition
    - 以下を満たす場合、その問題は NP であるとする
      - 1: input size の多項式長の解となる
      - 2: 多項式時間で解が検証可能
- Interpretation of NP-Completeness
  - note
    - すべての NP 問題は brute-force 探索で指数時間で解くことが可能
  - 完全性の定義
    - 1 つの NP 完全問題が多項式時間で解ければ、すべての NP 問題が多項式時間で解ける
  - upshot
    - NP 完全性は intractability の strong evidence となる
- NP-Completeness User's Guide
  - 問題 Π が NP-Complete を示すためにやること
    - 既知の NP 完全な問題 Π' を見つける
    - Π' が Π に帰着することを示す
      - これは Π が少なくとも Π' 程度には困難であるということ
    - Π も同様に NP 完全である

## The P vs NP Question

- The P vs NP Question
  - question
    - Is P = NP ?
  - widely conjectured
    - P と NP は異なる
    - しかし、これは示されていない
  - What's In A Name
    - NP は Nondeterministic Polynomial から来ている
    - not polynomial ではない

## Algorithmic Approaches to NP-Complete Problems

- NP-Completeness: The Beginning, Not the End
  - important
    - NP 完全性は death sentence ではない
    - しかし適切な戦略が必要
  - 3 useful strategies
    - 1: 計算的に簡単な special case にフォーカスする
    - 2: 発見的手法 fast algorithms that are not always correct
    - 3: 指数時間かかるが brute-force search よりは速いやりかたで解く

# Part 32: Faster Exact Algorithms for NP-Complete Problems

## The Vertex Cover Problem

- The Vertex Cover Problem
  - input
    - 無向グラフ G = (V, E) が与えられる
  - goal
    - 最小点被覆を求める
      - G の全辺の endpoint について少なくとも 1 つは含むような subset S ⊆ V
  - 参考
    - [二部グラフの最小点被覆、最大安定集合 (最大独立集合)、最小辺被覆を総整理！ - Qiita](https://qiita.com/drken/items/7f98315b56c95a6181a4)
- Strategies for NP-Complete Problems
  - 計算可能な特殊な case を特定する
  - Heuristics
  - brute-force search より良い指数時間の解法を考える

## Smarter Search for Vertex Cover

- The Vertex Cover Problem
  - suppose
    - 正の整数 k が与えられ、サイズ k 以下の vertex cover があるかチェックするやり方はどうか
  - note
    - すべての可能性をチェックすると θ(n^k) 時間かかる
    - これよりよくできるか？
- A Substructure Lemma
  - Substructure Lemma
    - グラフ G, edge(u, v) ∈ G, 整数 k >= 1 が与えられる
    - Gu を G から頂点 u と u に接する辺が削除されたグラフとする
    - G が size k の vertex cover を持つ <=> Gu or Gv (or both) は size (k - 1) の vertex cover を持つ
  - 証明
    - <= について示す
      - Gu がサイズ k - 1 の vertex cover S を持つとする
      - E = Eu(inside Gu) ∪ Fu(incident to u) とする
      - Eu の各辺の endpoint を S は含むので、S ∪ {u} はサイズ k の G の vertex cover となる
    - => について示す
      - S = サイズ k の vertex cover of G
      - (u, v) は G の辺なので、u と v の少なくとも 1 つは S に含まれる(ここでは u が含まれるとする)
      - Eu の中に u と接する辺はないので、S - {u} はサイズ k - 1 の vertex cover of Gu となる
- A Search Algorithm
  - 任意の辺 (u, v) ∈ E を選ぶ
  - サイズ k - 1 の vertex cover S を Gu の中から探す
    - 見つかれば S ∪ {u} を返す
  - サイズ k - 1 の vertex cover S を Gv の中から探す
    - 見つかれば S ∪ {v} を返す
  - FAIL を返す(サイズ k の vertex cover は存在しない)
- Analysis of Search Algorithm
  - correctness
    - substructure lemma より、各ステップが正しいことがわかる
  - 実行時間
    - recursive call の合計回数は O(2^k)
    - 各 recursive call で O(m) work を行うとすると、実行時間は O(2^k・m) となり、これは O(n^k) より改善されている

## The Traveling Salesman Problem

- Traveling Salesman Problem
  - input
    - 負のコストを持たない完全無向グラフ
  - output
    - min-cost tour(すべての頂点に 1 度ずつ訪れる)
  - brute-force search
    - 約 n! 時間かかる
    - n ≒ 12, 13 くらいまで tractable
  - dynamic programming
    - O(n^2・2^n) 時間
    - n ≒ 30 くらいまで tractable
  - A Optimal Substructure Lemma?
    - idea
      - Bellman-Ford algorithm のフォーマットを使う
    - proposed subproblems
      - i ∈ {0, 1, ..., n}, j ∈ {0, 1, ..., n} とする
      - Lij を最大 i edges での 1 から j への shortest path の長さとする
    - しかし、これだと subproblem を解いても、オリジナルの問題を解くことにならない
  - これを optimal substructure lemma にするには、最大 i edges ではなく「ちょうど i edges」、繰り返し頂点を訪れていないことも条件に含める必要がある
  - つまり、Lij = length of shortest path from 1 to j with exactly i edges and no repeated vertices とする
    - しかし、これだと効率よく計算できない
    - hope
      - 本当は Lij = min(k!=1,j) {Li-1,k + ckj} としたい
    - problem
      - これだと Li-1,k は j を含まないようにしないといけない
      - つまり subproblem がどの頂点を訪れているか覚えておき、それぞれの値を保持している必要がある

## A Dynamic Programming Algorithm for TSP

- The Subproblems
  - すべての destination j ∈ {1, 2, ..., n} と、すべての subset S ⊆ {1, 2, ..., n} (1 と j は含む)に対して LS,j = 1 から j への最短パスの長さ that visits precisely the vertices of S (exactly once each)
- Optimal Substructure
  - optimal substructure lemma
    - P を 1 から j への最短パスとし、S の各頂点をちょうど 1 回ずつ通るとする
    - もし P の last hop が (k, j) とすると P' は 1 から k への最短パスで、S - {j} をちょうど 1 回ずつ通る
  - corresponding recurrence
    - LS,j = min(k∈S,k!=j) {LS-{j},k + ckj}
      - subproblem は |S| 個となる
- A Dynamic Programming Algorithm
  - A を 2 次元配列とし、subset S ⊆ {1, 2, ..., n} として、S は 1 と destination j ∈ {1, 2, ..., n} を含む
  - base case
    - A[S, 1] = 0 (if S = {1}), +∞ (otherwise)

```
for m = 2, 3, ..., n  // m = subproblem size
  for each set S ⊆ {1, 2, ..., n} of size m で 1 を含む
    for each j ∈ S, j != 1
      A[S, j] = min(k∈S,k!=j) {A[S - {j}, k] + ckj}
Return min(j=2 to n) {A[{1, 2, ..., n}, j] + cj1}
```

- 実行時間
  - m の選択に O(n)、S の選択に O(2^n)、j の選択に O(n)
  - 合計で O(n^2・2^n) とわかる
