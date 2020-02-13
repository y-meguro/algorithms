各授業で習ったことの抜粋、および自分で調べたことや感じたことのメモを書いています

# Part 5: Quicksort Algorithm

## Overview

- 平均実行時間 `O(n * log n)`
- additional storage がとても小さくて済む
- key
  - pivot を使って分割する
- やり方
  - 配列から 1 つの要素を選んで pivot とする
  - 配列を再配置する
    - pivot の左には pivot より小さい要素が来るようにする
    - pivot の右には pivot より大きい要素が来るようにする
- 2 cool facts about partition
  - Linear O(n) time, no extra memory
    - 後述の「Partition Subroutine」で extra memory が不要なやり方を説明
  - Reduces problem size
- High-Level Description
  - QuickSort(array A, length n)
    - If n=1 return
    - p = ChoosePivot(A,n)
    - Partition A around p
    - Recursively sort 1st part
    - Recursively sort 2nd part

## Partition Subroutine

- O(n) の extra memory を使えば簡単。O(n) 時間で partition できる
- In-Place Implementation
  - extra memory を使わずにやる
- 仮定
  - 配列の先頭の要素を pivot とする(先頭以外を pivot とする場合、pivot と先頭の要素を swap すれば同じ)
- Higl-Level Idea
  - pivot, p より小さい要素, p より大きい要素(ここまで partition 済み), まだ partition されていない要素 となるようにする
  - p より大きい要素が開始するインデックス i と、まだ partition されていない要素が開始するインデックス j を記憶しておく
    - pivot: 1
    - p より小さい要素 [2, i)
    - p より大きい要素 [i, j)
    - まだ partition されていない要素 [j, end]
  - j 番目の要素(まだ partition されていない最も左側の要素)が p より小さい場合は、i 番目の要素と swap、i と j を共にインクリメントする。p より大きい場合は、j をインクリメントする
  - 上の操作を最後まで行った後、ピボットを i 番目の要素と交換すれば、pivot の左側は pivot より小さい要素、右側は pivot より大きい要素となる
- Pseudocode

```
Partition(A, l, r)
p = A[l]
i = l + 1
for j = l + 1 to r
  if A[j] < p
    swap A[j] and A[i]
    i = i + 1
swap A[l] and A[i - 1]
```

- 上記の実行時間は O(n)

## Chosing a Good Pivot

- QuickSort の実行時間は pivot の質に左右される
  - 常に 1 番小さいものを選んでしまうと `θ(n^2)`
  - 常に真ん中のものを選べれば `θ(n * log n)`
- Random Pivots
  - すべての recursive call でランダムに pivot を選ぶ
  - もしすべての pivot が 25-75% の間にある要素であれば実行時間は `O(n * log n)` になる
  - また、半分の pivot が 25-75% の間にある要素であれば実行時間は `O(n * log n)` になる
- QuickSort の平均実行時間
  - `O(n * log n)`
