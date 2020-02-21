#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e15;

int n, m;
vector<vector<ll>> dp;

ll floydWarshall() {
  for (int i = 0; i < n; i++) {
    dp.at(i).at(i) = 0;
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        dp.at(i).at(j) = min(dp.at(i).at(j), dp.at(i).at(k) + dp.at(k).at(j));
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (dp.at(i).at(i) < 0) {
      return -INF;
    }
  }

  ll res = INF;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res = min(res, dp.at(i).at(j));
    }
  }
  return res;
}

int main() {
  cin >> n >> m;
  dp.resize(n, vector<ll>(n, INF));

  for (int i = 0; i < m; i++) {
    int x, y, c;
    cin >> x >> y >> c;
    x--; y--;
    dp.at(x).at(y) = c;
  }

  ll ans = floydWarshall();
  if (ans == -INF) {
    cout << "graph has a negative cycle" << endl;
  } else {
    cout << ans << endl;
  }
  return 0;
}