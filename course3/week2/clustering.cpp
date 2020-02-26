#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int from, to, cost;
  Edge(int from, int to, int cost): from(from), to(to), cost(cost) {}
};

bool compare_by_cost(Edge a, Edge b) {
  if(a.cost == b.cost){
    return a.from < b.from;
  } else {
    return a.cost < b.cost;
  }
}

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
  int n;
  cin >> n;
  UnionFind u(n);

  int k = 4;

  int m = n * (n - 1) / 2;
  vector<Edge> e;
  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    from--; to--;
    e.emplace_back(from, to, cost);
  }
  sort(e.begin(), e.end(), compare_by_cost);

  int ans = 0;
  int i;
  for (i = 0; i < m; i++) {
    int x = e.at(i).from;
    int y = e.at(i).to;
    u.unite(x, y);
    if (u.size() <= k) break;
  }
  for (int j = i; j < m; j++) {
    int x = e.at(j).from;
    int y = e.at(j).to;
    if (u.find(x) != u.find(y)) {
      ans = e.at(j).cost;
      break;
    }
  }
  cout << ans << endl;
  return 0;
}