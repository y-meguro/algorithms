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

# Part 13: Balanced Binary Search Trees

## Sorted Arrays

- 各操作に対する実行時間は以下の通り
  - 探索
    - θ(log n)
  - 選択(i 番目のもの)
    - O(1)
  - min/max
    - O(1)
  - Pred/Succ
    - O(1)
  - Rank(数字が与えられ、それ以下の数が何個あるか)
    - O(log n)
  - Output in sorted order
    - O(n)
- しかし、挿入と削除には θ(n) 時間かかってしまう
  - これを速くするために、Balanced Search Tree を考える

## Balanced Search Tree (概要)

- sorted array + 挿入と削除を速くしたもの
  - [平衡二分探索木 - Wikipedia](https://ja.wikipedia.org/wiki/%E5%B9%B3%E8%A1%A1%E4%BA%8C%E5%88%86%E6%8E%A2%E7%B4%A2%E6%9C%A8)
- 各操作に対する実行時間
  - 探索
    - O(log n) (最小は O(1))
  - 選択(i 番目のもの)
    - O(log n) (最小は O(1))
  - min/max
    - O(log n) (最小は O(1))
  - Pred/Succ
    - O(log n) (最小は O(1))
  - Rank(数字が与えられ、それ以下の数が何個あるか)
    - O(log n)
  - Output in sorted order
    - O(n)
  - 挿入
    - O(log n) ← new!
  - 削除
    - O(log n) ← new!

## Binary Search Tree

- Binary Search Tree Structure (Balanced の前にこっちに触れる)
  - 1 つの key に対して 1 つのノード
  - most basic version では
    - 各ノードは以下を持つ
      - left chiled pointer
      - right chiled pointer
      - parent pointer
  - 特性
    - key x の左側にある子どもはすべて x 未満、右側にある子どもはすべて x より大きい
  - The Height of a Binary Search Tree
    - ここで height とは、longest root-leaf path のこと
    - best case では log2 n、worst case では n なる
  - Binary Search Tree で探索(または挿入)を行う時の実行時間は θ(height)
  - Min, Max, Pred, and Succ
    - minimum key を計算する場合
      - root から開始する
      - left child の pointer をたどっていく(maximum を探す場合は right child pointer)
    - key k の predecessor(1 つ前のもの)を探す場合
      - Easy case: k の left subtree がから出ない場合は、left subtree の最大値を返す
      - Otherwise: k より小さい key を見つけるまで parent pointers をたどっていく
    - これらの処理は最悪の場合、θ(height) の実行時間
  - 昇順で key の出力をする処理
    - r を探索木の root、左側の subtree を TL、右側の subtree を TR とする
    - 処理
      - 1: recurse on TL
      - 2: print out r's key
      - 3: recurse on TR
  - 削除
    - key k を削除する
    - 処理
      - k を探索する
      - Easy case: k が子どもを持たない場合は、ただ削除する
      - Medium case: k が 1 つだけ子どもを持つ場合。もともと k があった場所に子どもを置けばよい
      - Difficult case: k が子どもを 2 つ持つ場合
        - k の predecessor の l を計算する
        - k と l を swap
        - k を削除する
  - Select and Rank
    - idea
      - 自身の木について、追加情報を各ノードに持たせておく
    - size(x) として、x を root とする subtree のノード数を格納する
      - もし x が y と z という子どもを持つとすると、size(x) = size(y) + size(z) + 1
    - i 番目の要素を選択する場合
      - start at root x, with children y and z
      - let a = size(y)
      - if a == i - 1, return x's key
      - if a >= i, y を root とする木から i 番目のものを探す
      - if a < i - 1, (i - a - 1) 番目のものを z を root とする木から探す
      - 実行時間は θ(height)

## Balanced Search Trees (詳細)

- Balanced Search Trees
  - idea
    - height を O(log n) にできれば、Search / Insert / Delete / Min / Max / Pred / Succ がすべて O(log n) で実行できる
- Red-Black Invariants (赤黒木の不変条件)
  - 1: Each node red or black
  - 2: Root is black
  - 3: No 2 reds in a row
    - 赤いノードは黒の子しか持たない
  - 4: Every root-NULL path has same number of black nodes
    - 末端が NULL ノード
    - ルートから辿るどのパスも同じ数の黒ノードがある
- 例
  - length 3 の赤黒木が存在しないことを考える
    - ノード 1 が root、片側にノード 2 と 3 が連続してつながる形
  - この場合、ノード 1 から両側の黒ノードの数が同じにならなければいけないが、ノード 2 と 3 がある方は必ず黒ノードが 2 つ以上になってしまい、数が揃わない。よってこのような赤黒木は存在しない
- Height Guarantee
  - 以下を証明する
    - すべての n ノードからなる赤黒木の高さは `2 * log2(n + 1)` 以下
      - 例えばノード数 7 の場合、高さは 3 以下
  - 証明
    - n >= 2^k - 1 の時、k を root-NULL path にある最小ノード数とする => k <= log2(n + 1)
    - よって、n ノードの赤黒木で root-NULL path には最大 `log2(n + 1)` 個の黒ノードがある
    - 不変条件 4 より、すべての root-NULL path は `log2(n + 1)` 個以下の黒ノードを持つ
    - 不変条件 3 より、すべての root-NULL path は `2 * log2(n + 1)` 個以下のノードを持つ
- Left Rotations
  - idea
    - locally rebalance subtrees at a node in O(1) time
  - parent x と right child y を回転させる
- Right Rotations
  - parent x と left child y を回転させる
- Insert / Delete
  - idea
    - proceed as in a normal binary search tree, then recolor and/or perform rotations until invariants are restored
  - insert(x)
    - 1: 通常通り x を挿入する
    - 2: try coloring x red
    - 3: x の親 y が黒であったら終了
    - 4: y が赤であったら、y の親 w は黒である
      - Case 1: もし w のもう 1 つの子の z が赤の場合
        - y と z を黒にし、w を赤にする
        - これは不変条件 3 も満たす
        - もし w がルートの場合は、赤にしてしまうと不変条件 2 を破ってしまうので、w を黒に戻せばよい
        - これは O(log n) で実行できる
      - Case 2: w のもう 1 つの子の z が黒(もしくは Null)の場合
        - 詳細は省略するが、rotation と recoloring を行うことで、O(1) 時間で不変条件を維持できる
