#include <bits/stdc++.h>
using namespace std;
const double INF = 1e12;

int main() {
  int n;
  cin >> n;

  vector<double> X(n, 0.0);
  vector<double> Y(n, 0.0);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x >> X.at(i) >> Y.at(i);
  }

  vector<bool> used(n, false);
  int before = 0;
  used.at(0) = true;
  double ans = 0;
  for (int i = 1; i < n; i++) {
    double d = INF;
    int idx;
    for (int j = 1; j < n; j++) {
      if (used.at(j) || j == before) continue;
      double tmp = pow((X.at(j) - X.at(before)), 2) + pow((Y.at(j) - Y.at(before)), 2);
      if (d > tmp) {
        d = tmp;
        idx = j;
      }
    }
    d = sqrt(d);
    ans += d;
    used.at(idx) = true;
    before = idx;
  }
  double d = pow((X.at(0) - X.at(before)), 2) + pow((Y.at(0) - Y.at(before)), 2);
  ans += sqrt(d);
  cout << (int)ans << endl;
  return 0;
}