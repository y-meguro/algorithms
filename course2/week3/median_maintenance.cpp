#include <bits/stdc++.h>
using namespace std;
const int mod = 10000;

struct HeapLow {
  vector<int> val;
  vector<int> parent;

  void setRoot(int root) {
    val.push_back(root);
    parent.push_back(0);
  }

  void insert(int x) {
    if ((int)val.size() == 0) {
      setRoot(x);
      return;
    }
    val.push_back(x);
    int currentIdx = val.size() - 1;
    parent.push_back((currentIdx - 1) / 2);

    // Bubble-Up
    int parentIdx = parent.at(currentIdx);
    while (val.at(currentIdx) > val.at(parentIdx) && currentIdx != parentIdx) {
      swap(val.at(currentIdx), val.at(parentIdx));
      currentIdx = parentIdx;
      parentIdx = parent.at(currentIdx);
    }
  }

  int extractMax() {
    int res = val.at(0);
    int n = val.size();
    val.at(0) = val.at(n - 1);

    val.pop_back();
    parent.pop_back();

    if ((int)val.size() > 0) {
      // Bubble-Down
      int currentIdx = 0;
      int lastIdx = (int)val.size() - 1;

      int childIdx1, childIdx2;
      while (true) {
        childIdx1 = currentIdx * 2 + 1;
        childIdx2 = currentIdx * 2 + 2;

        // 子どもが1つもない場合
        if (childIdx1 > lastIdx) break;

        // 子どもが1つだけある場合
        if (childIdx2 > lastIdx) {
          if (val.at(currentIdx) < val.at(childIdx1)) {
            swap(val.at(currentIdx), val.at(childIdx1));
          }
          break;
        }

        // 子どもが2つある場合
        if (val.at(currentIdx) < val.at(childIdx1) && val.at(childIdx1) > val.at(childIdx2)) {
          swap(val.at(currentIdx), val.at(childIdx1));
          currentIdx = childIdx1;
        } else if (val.at(currentIdx) < val.at(childIdx2)) {
          swap(val.at(currentIdx), val.at(childIdx2));
          currentIdx = childIdx2;
        } else {
          break;
        }
      }
    }
    return res;
  }
};

struct HeapHigh {
  vector<int> val;
  vector<int> parent;

  void setRoot(int root) {
    val.push_back(root);
    parent.push_back(0);
  }

  void insert(int x) {
    if ((int)val.size() == 0) {
      setRoot(x);
      return;
    }
    val.push_back(x);
    int currentIdx = val.size() - 1;
    parent.push_back((currentIdx - 1) / 2);

    // Bubble-Up
    int parentIdx = parent.at(currentIdx);
    while (val.at(currentIdx) < val.at(parentIdx) && currentIdx != parentIdx) {
      swap(val.at(currentIdx), val.at(parentIdx));
      currentIdx = parentIdx;
      parentIdx = parent.at(currentIdx);
    }
  }

  int extractMin() {
    int res = val.at(0);
    int n = val.size();
    val.at(0) = val.at(n - 1);

    val.pop_back();
    parent.pop_back();

    if ((int)val.size() > 0) {
      // Bubble-Down
      int currentIdx = 0;
      int lastIdx = (int)val.size() - 1;

      int childIdx1, childIdx2;
      while (true) {
        childIdx1 = currentIdx * 2 + 1;
        childIdx2 = currentIdx * 2 + 2;

        // 子どもが1つもない場合
        if (childIdx1 > lastIdx) break;

        // 子どもが1つだけある場合
        if (childIdx2 > lastIdx) {
          if (val.at(currentIdx) > val.at(childIdx1)) {
            swap(val.at(currentIdx), val.at(childIdx1));
          }
          break;
        }

        // 子どもが2つある場合
        if (val.at(currentIdx) > val.at(childIdx1) && val.at(childIdx1) < val.at(childIdx2)) {
          swap(val.at(currentIdx), val.at(childIdx1));
          currentIdx = childIdx1;
        } else if (val.at(currentIdx) > val.at(childIdx2)) {
          swap(val.at(currentIdx), val.at(childIdx2));
          currentIdx = childIdx2;
        } else {
          break;
        }
      }
    }
    return res;
  }
};

int main() {
  int n = 10000;
  int x1, x2;
  int ans = 0;

  cin >> x1 >> x2;
  ans += x1;
  if (x1 > x2) swap(x1, x2);
  ans += x1;
  ans %= mod;

  HeapLow hl;
  hl.insert(x1);
  HeapHigh hh;
  hh.insert(x2);

  for (int i = 2; i < n; i++) {
    int x;
    cin >> x;

    int a;
    if (i % 2 == 0) {     // HeapLowの要素が1つ増える
      a = hh.extractMin();
    } else {              // HeapHighの要素が1つ増える
      a = hl.extractMax();
    }
    hl.insert(min(x, a));
    hh.insert(max(x, a));

    int median = hl.extractMax();
    hl.insert(median);
    ans += median;
    ans %= mod;
  }
  cout << ans << endl;
  return 0;
}