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

# Part 18: Introduction to Greedy Algorithms

- Algorithm Design Paradigms
  - Algorithm Design
    - どんな問題にも適用できる単一の "silver bullet" はない
  - Design Paradigms
    - divide & conquer (course1)
    - randomized algorithms (course1)
    - greedy algorithms (本コース)
    - dyamic programming (本コースの後半)

## Greedy Algorithm

- definition
  - "myopic" な(近視眼的な) 決定を繰り返すことで、最終的に望ましい結果を得るアルゴリズム
- 例
  - Dijkstra's shortest path algorithm
- Divide & Conquer との違い
  - 貪欲法は様々な問題に適用できる
  - 実行時間の解析が簡単
  - 正しさを証明するのが難しい
    - 貪欲法は正しくないことも多いので、注意が必要
- Proofs of Correctness
  - 1: 帰納法
  - 2: "Exchange argument"
    - 貪欲法が正しくないと仮定した上で、矛盾を導く
    - 2 つの要素を交換した場合に、最適だと仮定するようなやり方
  - 3: Whatever works!
    - 1 と 2 を組み合わせるやり方だったり、完全に別のものだったり、何らかの正しいやり方でやる
- The Caching Problem
  - キャッシュミスが起きたら、何かをキャッシュから追い出す必要がある。その時にどの要素を追い出せば、キャッシュミスが減るか
- The Optimal Caching Algorithm
  - The "furthest-in-future" algorithm が最適
  - 実際的には Least Recently Used(LRU) を使うことが多いが、理想的なベンチマークとして "furthest-in-future" algorithm の結果を計算することは役に立つ
