#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<int, int>;
const ll INF = 1e15;

struct Edge {
  int from;
  int to;
  ll cost;
  Edge(int from, int to, ll cost): from(from), to(to), cost(cost) {}
};

int n, m;
vector<vector<Edge>> G;
vector<Edge> es;
vector<ll> d;

bool bellmanFord(int s) {
  d.at(s) = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      Edge e = es.at(j);
      if (d.at(e.from) != INF && d.at(e.to) > d.at(e.from) + e.cost) {
        if (i == n) {
          return true;
        } else {
          d.at(e.to) = d.at(e.from) + e.cost;
        }
      }
    }
  }
  return false;
}

struct Dijkstra {
  vector<ll> d;

  Dijkstra(int s) {
    d.resize(n, INF);
    d.at(s) = 0;

    priority_queue<P, vector<P>, greater<P>> q;
    q.push(make_pair(0, s));

    while (!q.empty()) {
      P p = q.top();
      q.pop();
      int v = p.second;
      if (d.at(v) < p.first) continue;

      for (Edge e : G.at(v)) {
        if (d.at(e.to) > d.at(v) + e.cost) {
          d.at(e.to) = d.at(v) + e.cost;
          q.push(make_pair(d.at(e.to), e.to));
        }
      }
    }
  }

  ll minval() {
    ll res = INF;
    for (int i = 0; i < n; i++) {
      res = min(res, d.at(i));
    }
    return res;
  }
};

int main() {
  cin >> n >> m;
  G.resize(n);
  d.resize(n, INF);

  for (int i = 0; i < m; i++) {
    int x, y, c;
    cin >> x >> y >> c;
    x--; y--;
    G.at(x).emplace_back(x, y, c);
    es.emplace_back(x, y, c);
  }

  cout << "aaa" << endl;

  bool hasNegativeCycle = bellmanFord(0);
  if (hasNegativeCycle) {
    cout << "graph has a negative cycle" << endl;
    return 0;
  }

  cout << "bbb" << endl;

  for (int i = 0; i < n; i++) {
    for (Edge e : G.at(i)) {
      e.cost += d.at(e.from) - d.at(e.to);
    }
  }

  cout << "ccc" << endl;

  ll ans = INF;
  for (int i = 0; i < n; i++) {
    Dijkstra di(i);
    ans = min(ans, di.minval());
  }
  cout << ans << endl;
  return 0;
}