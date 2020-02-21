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
    - 2: 経験則として fast algorithms that are not always correct
    - 3: 指数時間かかるが brute-force search よりは速いやりかたで解く
