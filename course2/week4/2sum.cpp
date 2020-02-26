#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n = 1000000;
  map<ll, bool> h;
  for (int i = 0; i < n; i++) {
    ll a;
    cin >> a;
    h[a] = true;
  }

  vector<bool> t(20001, false);
  for (auto e : h) {
    ll x = e.first;
    for (int i = 0; i < 20001; i++) {
      int j = i - 10000;
      if (t.at(i) || j - x == x) continue;
      if (h.count(j - x)) t.at(i) = true;
    }
  }

  int ans = 0;
  for (int i = 0; i < 20001; i++) {
    if (t.at(i)) ans++;
  }
  cout << ans << endl;
  return 0;
}