#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<int, int>;
const int INF = 1e9;

struct Edge {
  int to, cost;
  Edge(int to, int cost): to(to), cost(cost) {}
};

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<Edge>> G(n);
  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    from--; to--;
    G.at(from).emplace_back(to, cost);
    G.at(to).emplace_back(from, cost);
  }

  vector<bool> reached(n, false);

  priority_queue<P, vector<P>, greater<P>> q;
  q.push(P(0, 0));

  ll ans = 0;
  while (!q.empty()) {
    P p = q.top();
    q.pop();

    int v = p.second;

    if (reached.at(v)) continue;
    reached.at(v) = true;
    ans += p.first;

    for (Edge e : G.at(v)) {
      if (reached.at(e.to)) continue;
      q.push(P(e.cost, e.to));
    }
  }
  cout << ans << endl;
  return 0;
}