#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
  vector<int> parent;
  vector<int> height;

  UnionFind(int n) {
    height.resize(n, 0);
    for (int i = 0; i < n; i++) {
      parent.push_back(i);
    }
  }

  int find(int x) {
    if (parent.at(x) == x) {
      return x;
    } else {
      parent.at(x) = find(parent.at(x));
      return parent.at(x);
    }
  }

  void unite(int x, int y) {
    int p = find(x);
    int q = find(y);
    if (p == q) return;

    if (height.at(p) < height.at(q)) {
      parent.at(p) = q;
    } else {
      parent.at(q) = p;
      if (height.at(p) == height.at(q)) height.at(p)++;
    }
  }

  int size() {
    set<int> s;
    for (int i = 0; i < (int)parent.size(); i++) {
      s.insert(find(i));
    }
    return s.size();
  }
};

int main() {
  int n, codeLen;
  cin >> n >> codeLen;
  UnionFind u(n);

  vector<vector<int>> nodes(n, vector<int>(codeLen));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < codeLen; j++) {
      cin >> nodes.at(i).at(j);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i >= j) continue;
      int diff = 0;
      for (int k = 0; k < codeLen; k++) {
        if (diff >= 3) break;
        if (nodes.at(i).at(k) != nodes.at(j).at(k)) diff++;
      }
      if (diff < 3) u.unite(i, j);
    }
  }
  cout << u.size() << endl;
  return 0;
}