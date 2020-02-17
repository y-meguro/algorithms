# Part 17: Two Motivating Applications

## Distributed Shortest-Path Routing

- Graphs and the Internet
  - Internet はグラフ
    - end hosts と routers が頂点。direct physical or wireless connections が辺
- Internet Routing
  - Stanford の gateway router から Cornell の gateway router にデータを送ることを考える
  - question
    - どのようなルートで送るか？
  - idea
    - shortest-path を探す
  - Dijkstra's algorithm で計算すればよい？
    - しかしこの場合、Stanford の gateway router は Internet 全体を知る必要が出てしまう
  - solution
    - Bellman-Ford algorithm で解決する
      - また、これは netgative edge costs も扱える

## Sequence Alignment

- Motivation
  - ゲノムの計算における基本的な問題
  - input
    - {A, C, G, T} からなる 2 つの文字列
  - problem
    - 2 つの文字列がどのくらい似ているか判定したい
- Similarity の測定
  - question
    - similar が意味するのは何か
  - intuition
    - "AGGGCT" と "AGGCA" はうまく並べることができるので似ている
  - idea
    - Measure similarity via quality of "best" alignment
      - AGGGCT と AGG-CA とすると 1 mismatch(AGGCA に 1 つ "gap" (-) を挿入した)
  - 仮定
    - gap と mismatch から penalties を決定することができる
- Problem Statement
  - input
    - {A, C, G, T} からなる 2 つの文字列
    - Penalty pen gap はそれぞれの gap を表し、0 以上となる
    - Penalty pen AT は A と T のミスマッチを表し、0 以上となる
  - output
    - Needleman-Wunsch score と呼ばれる total penalty を最小化させたもの
    - NW score が小さい ≒ Similar Strings となる
- Algorithms are Fundamental
  - 効率的に best alignment を探すアルゴリズムがないと、genome similarity の測定は役に立たない
  - brute-force search
    - すべての alignments を試し、最も良いものを記憶する
    - これだと長さが 500 の場合、2^500 >= 10^125 の操作が必要となってしまい、現実的でない
  - solution
    - dynamic programming を使う
