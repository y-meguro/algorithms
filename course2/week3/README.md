# Part 12: Heaps

## Data Structures

- Point
  - organize data so that it can be accessed quickly and usefully
- 例
  - lists, stacks, queues, heaps, search trees, hashtables, bloom filters, union-find など
- Why so Many?
  - 異なる data structures は異なる処理をサポートする => タスクのタイプによって適するものが違う
- 重要なポイント
  - choose the "minimal" data structure that supports all the operations that you need
- いまは問題に対して、既存の data structure の中から適しているものを選ぶレベル。この次は自分で作成した data structure を使うレベルとなる

## Heap

- サポートする処理
  - Insert
    - add a new object to a heap. 実行時間は O(log n)
  - Extract-Min
    - remove an object in heap with a minimum key value. 実行時間は O(log n)
  - メインは上の 2 つだが、他にも Heapify(n batched inserts in O(n) time) や Delete(O(log n) time) をサポートする場合も多い
- Application: ソート
  - Heap Sort
    - 1: insert all n array elements into a heap
    - 2: Extract-Min to pluck out elements in sorted order
  - 実行時間
    - 2n heap operations = `O(n * log n)`
    - これは比較ソートの最適解と同じ
- Application: Event Manager
  - Priority Queue(heap の同義語)
  - Objects として event record を入れ、key に event が開始する時間を入れる
  - Extract-Min で次にスケジュールされているイベントを取得できる
- Application: Median Maintenance
  - input
    - x1, ..., xn の値が 1 つずつ渡される
  - output
    - 各ステップ i での {x1, ..., xi} の中央値
  - 制約
    - ステップ i で使える時間は O(log i)
  - Solution
    - maintain heaps H Low: supports Extract Min
      - i/2 smalest elements が H Low の中に入っているようにする
      - H High として大きい要素を入れてもいい
- Application: Speeding Up Dijkstra
  - 普通にやると θ(nm)
  - ヒープを使うと `O(m * log n)` にできる
- 実装
  - Array Implementation
    - 配列の最初の index を 1 とする(0 ではない)
    - parent(i) = i/2 (i が偶数の時)
    - parent(i) = (i - 1)/2 (i が奇数の時)
  - Insert and Bubble Up
    - k を挿入するとする
    - やり方
      - 1: last level に k をくっつける
      - 2: heap の性質が回復するまで k を上にあげていく
    - 実行時間は O(log n)
  - Extract-Min and Bubble Down
    - やり方
      - 1: root を削除する
      - 2: last leaf を新しい root として持ってくる
      - 3: heap の性質が回復するまで下にさげていく
    - 実行時間は O(log n)
