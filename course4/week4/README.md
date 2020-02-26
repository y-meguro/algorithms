# Part 34: Local Search Algorithms

## The Maximum Cut Problem

- The Maximum Cut Problem
  - input
    - 無向グラフ G = (V, E)
  - goal
    - 交差する辺の数を最大化するような cut(A, B) を出力する
  - sad fact
    - NP-Complete
  - computationally tractable special case
    - bipartite graphs(二部グラフ)
- A Local Search Algorithm
  - notation
    - cut(A, B) と 頂点 v に対して
      - cv(A, B) を v に接し、A と B を交差する辺の数とする
      - dv(A, B) を v に接し、A と B を交差しない辺の数とする
  - local search algorithm
    - 1: (A, B) を任意の G の cut とする
    - 2: ある頂点 v について dv(A, B) > cv(A, B) の間 v をもう片方のサイドに移す
    - 3: 最終的な cut(A, B) を返す
  - note
    - nC2 回の iteration で終わる(つまり多項式時間で終わる)
- Performance Guarantees
  - theorem
    - local search algorithm はいつでも、maximum possible の値に対して、最低 50% 以上の値を返す
  - 注意点
    - random cut の場合の平均 crossing edge 数も 1/2・|E| とする
  - 上記の証明
    - random cut(A, B) を考える。すべての edge e ∈ E に対して
      - Xe = 1 (if e crosses (A, B)), 0 (otherwise)
      - E[Xe] = Pr[Xe = 1] = 1/2
      - よって E[# crossing edges] = E[ΣXe] = ΣE[Xe] = |E|/2 となり証明終わり
- Proof of Performance Guarantee
  - A, B を locally optimal cut とする
  - すると、すべての頂点 v について dv(A, B) <= cv(A, B) なので Σ(v∈V)dv(A, B) <= Σ(v∈V)cv(A, B) (ここでは両辺とも、各辺が二重にカウントされている)
  - すると 2・[# of non-crossing edges] <= 2・[# of crossing edges]
  - 両辺に 2・[# of crossing edges] を足すと 2・|E| <= 4・[# of crossing edges]
  - なので [# of crossing edges] >= 1/2・|E| となる。証明終わり
- The Weighted Maximum Cut Problem
  - generalization
    - 各辺 e ∈ E は負ではない weight we を持つ。crossing edges の total weight を最大化する
  - notes
    - 1: Local search still well defined
    - 2: こちらの場合でも locally optimal cuts は 50% 以上のパフォーマンスが保証される
      - random cut でも同様
    - 3: 多項式時間で収束することは保証されない

## Principles of Local Search

- Neighborhoods
  - X をある問題に対する candidate solution の集合とする
  - key ingredient
    - すべての x ∈ X に対して、特定の y ∈ X を "neighbors" とする
  - 例
    - x と y が neighboring cuts <=> 1 つの頂点だけ集合が異なる
    - x と y が neighboring variable assignments <=> 1 つの変数の値だけ異なる
    - x と y が neighboring TSP tours <=> 2 つの辺だけ異なる
- A Generic Local Search Algorithm
  - 1: x を initial solution とする
  - 2: x が superior neighboring solution y を持っている間、x = y とする
  - 3: final solution x を返す
- FAQ
  - question 1
    - How to pick initial solution x?
    - answer
      - 1: random solution を使う
      - 2: best heuristic を使う
  - question 2
    - 複数の superior neighboring y がある場合、どれを選ぶ？
    - answer
      - 1: ランダムに選ぶ
      - 2: 改善する量が大きいものを選ぶ
      - 3: 最も複雑な heuristic を選ぶ
  - question 3
    - How to define neighborhoods?
    - answer
      - 解の質と効果的な探索との間の "sweet spot" を見つける
  - question 4
    - local search は終わることが保証されている？
    - answer
      - X が有限で、すべての local step が目的関数を改善する場合は保証されている
  - question 5
    - local search は素早く収束することが保証されている？
    - answer
      - Usually not.
  - question 6
    - Are locally optimal solutions generally good approximations to globally optimal ones?
    - answer
      - No.
      - そのため複数のランダムな local search を行って、最も良いものを記憶したりする

## The 2-SAT Problem

- 2-SAT
  - SAT は Satisfactability Problem(充足可能性問題) からきている
  - input
    - n 個の Boolean 変数 x1, x2, ..., xn
    - m 個の clauses(節)。各節は 2 つの literal でできており、各 literal は xi または not xi
  - 例
    - (x1 ∨ x2) ∧ (not x1 ∨ x3) ∧ (x3 ∨ x4) ∧ (not x2 ∨ not x4)
  - output
    - 同時にすべての節を満たせるような assignment が存在するなら "Yes"
    - そうでなければ "No"
  - 例
    - 上記の例の場合は "Yes"
    - 例えば x1 と x3 が True、x2 と x4 が False の場合は条件を満たす
- (In)Tractability of SAT
  - 2-SAT
    - 多項式時間で解くことができる、また様々な方法で解ける
      - 強連結成分の計算に帰着できる
      - "Backtracking" でも多項式時間で解ける
      - randomized local search も使える
  - 3-SAT
    - 典型的な NP-Complete 問題
    - brute-force search は約 2^n 時間かかる
    - randomized local search を利用すると (4/3)^n 時間でできる
- Papadimitriou's 2-SAT Algorithm
  - アルゴリズム
    - log2 n 回、以下を繰り返す
      - random initial assignment を選ぶ
      - 2・n^2 回、以下を繰り返す
        - もし現在の assignment がすべての節を満たすなら、終了させ、その結果を返す
        - 満たさない場合は、任意の unsatisfied clause を選び、その中の 1 つの変数の値を反対にする
    - "unsatisfiable" を返す
  - key question
    - もし、satisfying assignment がある場合、アルゴリズムはそれを見つけられるのか？
  - obvious good points
    - 多項式時間で実行できる
    - unsatisfiable instances に対して正しく判定できる

## Random Walks on a Line

- Random Walks
  - key to analyzing Papadimitriou's algorithm
    - 負でない整数の上をランダムに歩くことを考える
  - setup
    - 最初(time 0 の時)は position 0 にいる
  - 各 time step で、50% の確率で 1 つ進むか 1 つ戻る
    - ただし position 0 にいる時は、100% の確率で 1 に進む
  - ここで n >= 0、Tn = number of steps until random walk reaches position n とすると E[Tn] = θ(n^2)
- Analysis of Tn
  - Let Zi = number of random walk steps to get to n from i
  - つまり Z0 = Tn
  - edge cases
    - E[Zn] = 0, E[Z0] = 1 + E[Z1]
  - for i ∈ {1, 2, ..., n - 1}
    - E[Zi] = Pr[go left]・E[Zi | go left] + Pr[go right]・E[Zi | go right]
      - ここで E[Zi | go left] = 1 + E[Zi-1], E[Zi | go right] = 1 + E[Zi+1]
    - = 1 + 1/2・E[Zi+1] + 1/2・E[Zi-1]
  - rearranging
    - Z[Zi] - E[Zi+1] = E[Zi-1] - E[Zi] + 2
- Finishing the Proof of Claim
  - E[Z0] - E[Z1] = 1
  - E[Z1] - E[Z2] = 3
  - ...
  - E[Zn-1] - E[Zn] = 2n - 1
  - 上記を合計すると E[Z0] - E[Zn] = E[Z0] = n^2。よって E[Tn] = n^2
- A Corollary
  - corollary
    - Pr[Tn > 2n^2] <= 1/2
  - 証明
    - p は Pr[Tn > 2n^2] を表すとする
    - n^2 = E[Tn]
    - = Σ(k=0 to 2n^2) k・Pr[Tn = k] + Σ(k=2n^2 + 1 to ∞) k・Pr[Tn = k]
      - ここで Σ(k=0 to 2n^2) k・Pr[Tn = k] は >= 0
      - また k >= 2n^2 なので Σ(k=2n^2 + 1 to ∞) k・Pr[Tn = k] >= 2n^2・Σ(k=2n^2 + 1 to ∞) Pr[Tn = k] = 2n^2・Pr[Tn > 2n^2]
    - >= 2n^2・Pr[Tn > 2n^2]
    - = 2n^2・p
    - よって、p <= 1/2 であることが示された

## Analysis of Papadimitriou's Algorithm

- Papadimitriou's Algorithm
  - n を変数の数とする
  - アルゴリズム(再掲)
    - log2 n 回、以下を繰り返す
      - random initial assignment を選ぶ
      - 2・n^2 回、以下を繰り返す
        - もし現在の assignment がすべての節を満たすなら、終了させ、その結果を返す
        - 満たさない場合は、任意の unsatisfied clause を選び、その中の 1 つの変数の値を反対にする
    - "unsatisfiable" を返す
- Satisfiable Instances
  - theorem
    - n 個の変数で充足可能な 2-SAT に対して、Papadimitriou's algorithm は 1 - 1/n 以上の確率で充足する解を見つけることができる
  - 証明
    - 外側のループの最初の iteration に注目する
    - ある任意の satisfying assignment を a' とする
    - at = algorithm's assignment after inner iteration t とする(t = 0, 1, ..., 2n^2)
    - Xt = at と a' で一致する変数の数 (Xt ∈ {0, 1, ..., n})
  - note
    - もし Xt = n ならば、解 a' を得て、アルゴリズムは終了する
- Proof of Theorem
  - key point
    - at が条件を満たさず、アルゴリズムは変数 xi, xj からなる unsatisfied clause を選ぶとする
  - note
    - a' が条件を満たすので、xi または xj (もしくは両方) が a' のものと異なっている
  - consequence of algorithm's random variable flip
    - 1: a' と at が xi と xj 両方で異なる場合 Xt+1 = Xt + 1
      - xi と xj のどちらを選んだ場合でも、一致する数は増える
    - 2: もし a' と at が xi と xj のどちらかのみで異なる場合
      - Xt+1 = Xt + 1 (50% probability)
      - Xt+1 = Xt - 1 (50% probability)
    - これは random walks での挙動と似ている
- Completing the Proof
  - consequence
    - outer loop の 1 回の iteration で satisfying assignment を見つける確率 >= Pr[Tn <= 2・n^2] >= 1/2
  - thus
    - Pr[algorithm fails] <= Pr[all log2 n independent trails fail]
    - <= (1/2)^log2 n
    - = 1/n となり証明終わり

# Part 35: The Wider World of Algorithms

## Stable Matching

- Stable Matchings(安定マッチング)
  - 2 つの node set U と V を考える
  - for simplicity
    - |U| = |V| = n と仮定する
    - 各 node はもう片方の全 nodes に対する ranked order を持つ
  - stable matching
    - 以下を満たすマッチング
      - もし u ∈ U, v ∈ V がマッチしていないならば、u は v より良い v' とマッチしているまたは、v は u' より良い u とマッチしている
- Gale-Shapley Proposal Algorithm
  - while there is an unattached man u
    - u がまだ断られていない中で、最も好みの woman v に対して申し込む
    - 各 woman は best proposal を受け入れる
  - theorem
    - n^2 iterations 以内に終了する
- Gale-Shapley Theorem
  - 1: 各 man は n 回以下の proposal をする => n^2 iterations 以下となる
  - 2: perfect matching で終了する
    - perfect matching(完全マッチング)
      - 無向グラフ G のマッチングとは、辺部分集合 M ⊆ E で、M のどの 2 辺も同じ頂点に接続しないもの
      - G の完全マッチングとは、G のマッチング M ⊆ E で、G の任意の頂点に M のある辺が接続しているもの
      - [数理解析 第 11回 マッチング](http://dopal.cs.uec.ac.jp/okamotoy/lect/2012/graphtheory/lect11.pdf)
  - 3: stable matching で終了する。マッチしていないある u, v を考える
    - case 1: u never proposed to v
      - u は v よりも良い人とマッチしている
    - case 2: u proposed to v
      - v はより良い offer をもらっている

## Bipartite Matching (二部マッチング)

- input
  - 二部グラフ G = (U, V, E)
  - 各 e ∈ E は U と V それぞれに 1 つ endpoint を持つ
- goal
  - 最大サイズとなるようなマッチング M ⊆ E を計算する
- fact
  - 最大フロー問題に帰着できる
- The Maximum Flow Problem
- input
  - 有向グラフ G = (V, E)
  - 開始点 s と終了点 t
  - 各辺 e は capacity ue を持つ
- goal
  - 可能な限りたくさんの flow を流せる s-t flow を計算する
- fact
  - 多項式時間で解ける

## Selfish Flow

- 家から職場までどのルートで行くのが早いか
- flow network を考える
- 各辺は delay function を持つ。例えば 100% の車が来ると 1 時間かかるが、50% の車の場合、30 分でつくというようなもの
- 例
  - 以下のグラフが与えられたとする
    - s → v が delay(x) = x
    - s → w が delay(x) = 1
    - v → t が delay(x) = 1
    - w → t が delay(x) = x
  - steady state
    - s → v と s → w は 50% ずつにわかれ、commute time は 1.5 hours
  - Braess's Paradox
    - もし v と w をテレポートできるとすると、すべての車は s → v → w → t と進むので、commute time は 2 時間かかるようになってしまう

## Linear Programming (線形計画法)

- 参考
  - [線形計画法超入門 - Qiita](https://qiita.com/Dason08/items/e1bafb9ddc766d1c8fd0)
  - [線形計画法の問題の解き方を詳しく解説！例題つき｜高校生向け受験応援メディア「受験のミカタ」](https://juken-mikata.net/how-to/mathematics/linear-programming.html)
- The general problem
  - いくつかの 1 次不等式および 1 次等式を満たす変数の値の中で、ある 1 次式を最大化または最小化する値を求める
  - この問題は、最大フロー問題など多くの問題を一般化したものとなる
- fact
  - very powerful "black-box" subroutine を使って、効率よく解くことができる
- extensions
  - convex programming(凸計画問題)
  - integer programming(整数計画問題)

## Other Topics and Models

- Geometric algorithms
- Algorithms that run forever
  - caching や routing など
- Bounded memory ("streaming algorithms")
- parallelism の開発
  - Map-Reduce / Hadoop
