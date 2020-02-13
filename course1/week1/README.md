# Part 1: Introduction

## イントロ

- アルゴリズムを学ぶ意味
  - important for all other branches of computer science
  - plays a key role in modern technological innovation
  - provides novel "lens" on processes outside of computer science and technology
  - challenging
  - fun
- The Algorithm Designer's Mantra
  - Perhaps the most important principle for the good algorithm designer is to refuse to be content.
  - (明白なやり方と比べて) "Can we do better?" を考えるのが大事

## Karatsuba Multiplication

- 普通に(筆算をするように)整数のかけ算をすると、n^2 の定数倍回の処理を必要とする
- Karatsuba Multiplication では、より効率のよい処理を目指す
  - 2 つの整数を x, y として、`x = 10^n/2 * a + c` `y = 10^n/2 * b + d` と考えると `x * y = 10^n * ac + 10^n/2 * (ad + bc) + bd` となる
  - これで再帰的に解けるわけだが、ac, ad, bc, bd の 4 つに分解するのではなく、ac, ad + bc, bd の 3 つに分解することを考えるのがポイント
    - ad + bc の求め方は、`(a + b) * (c + d) - ac - bd`。これによって 3 回のかけ算(と複数回の加減算)に分解できる
    - これによって、乗算の回数を 3/4 にすることができる。加減算の回数は増加するが、乗算のコストのほうが大きいため、結果として演算コスト全体もほぼ 3/4 になる

## コースについて

### 本コースのトピック

- Vocabulary for design and analysis of algorithms
- Divide and conquer algorithm design paradigm
- Randomization in algorithm design
- Primitives for reasoning about graphs
- Use and implementation of data structures

### この後のコースのトピック

- Greedy algorithm design paradigm
- Dynamic programming algorithm design paradigm
- NP-complete problems and what to do about them
- Fast heuristics with provable guarantees
- Fast exact algorithms for special cases
- Exact algorithms that beat brute-force search

### Skills You'll Learn

- Become a better programmer
  - なりたい笑
- Sharpen your mathematical and analytical skills
- Start "thinking algorithmically"
- Literacy with computer science's "greatest hits"
- Ace your technical interviews

## Merge Sort

### 他のソートアルゴリズム

- Selection Sort
  - [選択ソート : アルゴリズム](https://www.codereading.com/algo_and_ds/algo/selection_sort.html)
- Insertion Sort
  - [挿入ソート : アルゴリズム](https://www.codereading.com/algo_and_ds/algo/insertion_sort.html)
- Bubble Sort
  - [バブルソート : アルゴリズム](https://www.codereading.com/algo_and_ds/algo/bubble_sort.html)

### Merge Sort

- [マージソート : アルゴリズム](https://www.codereading.com/algo_and_ds/algo/merge_sort.html)
- Pseudocode
  - C = output (length = n)
  - A = 1st sorted array (n/2)
  - B = 2nd sorted array (n/2)
  - i = 1
  - j = 1

```
for k = 1 to n
  if A(i) < B(j)
    C(k) = A(i)
    i++
  else
    C(k) = B(j)
    j++
end
// ignores end cases
```

- Running Time
  - まず、マージする時のサブルーチンについて考える(上の Pseudocode の部分)
    - 初期化で 2 操作
    - 各 k について以下の操作(計 4 操作)
      - A と B の比較
      - C への代入
      - i (または j) のインクリメント
      - k のインクリメント
    - 以上より、計 m 個の数字が与えられ、マージする場合は 4m + 2 回以下の操作、m >= 1 なのですなわち、6m 回以下の操作となる
  - 次に全体での処理の回数を考える
    - `6n * log2 n + 6n` 以下となることを証明する
      - 2 分割を続けていくと、log2 n 回の分割で n 個の要素は 1 つの要素まで分割できる
      - もともとの配列をレベル 0、2 分割したものをレベル 1、というように考えていくと、レベル log2 n の時にすべての要素は 1 つになる
        - 各レベル j = 0, 1, ..., log2(n) について、subproblems の個数は 2^j、各サイズは n/2^j となる
      - つまり各レベルについて、操作の回数は 2^j * (6 * n/2^j) = 6n 回以下とわかる
      - 全レベル合計すると 6n(log2 n + 1) 以下となり、証明された

## Analysis of Algorithms の原則

- worst-case analysis を考えること
  - average-case analysis や benchmarks(typical input に対する解析) ではなく worst-case を考える
- constant factors や lower-order terms にあまり注意を払わないこと
  - 理由
    - Way easier
    - Constants depend on architecture / compiler / programmer anyways
    - Lose very little predictive power
- asymptotic analysis を考えること
  - インプットサイズが大きくなった時の実行時間にフォーカスする
- What is a "Fast" Algorithm?
  - このコースでは fast algorithm を worst-case running time grows slowly with input size と考える

# Part 2: Asymptotic Analysis

## Motivation

- "Sweet spot" for high-level reasoning about algorithms.
- Coarse enough to suppress architecture / language / compiler-dependent details.
- Sharp enough to make useful comparisons between different algorithms, especially on large inputs.

## Asymptotic Analysis の概要

- High-level idea
  - constant factors と lower-order terms を隠すこと
- 例
  - `6n * log2 n + 6n` は `n * log n` となる
- 実行時間は big-Oh 記法を使って表す
  - `O(n * log n)` ただし n は input size

## Big-Oh Definition

- T(n) を n = 1,2,3... における最悪実行時間の関数とする
- T(n) = O(f(n)) となる必要十分条件は、すべての n >= n0 について `T(n) <= c * f(n)` を満たす定数 c, n0 > 0 が存在すること

## Omega Notation

- T(n) = Ω(f(n)) となる必要十分条件は、`T(n) >= c * f(n) ∀n >= n0` となる定数 c, n0 が存在すること

## Theta Notation

- T(n) = θ(f(n)) となる必要十分条件は、T(n) = O(f(n)) かつ T(n) = Ω(f(n)) であること

## Little-Oh Notation

- T(n) = o(f(n)) となる必要十分条件は、任意の定数 c > 0 について `T(n) <= c * f(n) ∀n >= n0` を満たす定数 n0 が存在すること
