#include <bits/stdc++.h>
using namespace std;
const double INF = 1e12;

bool compare_by_bitcount(int a, int b) {
  if (__builtin_popcount(a) != __builtin_popcount(b)) {
    return __builtin_popcount(a) < __builtin_popcount(b);
  } else {
    return a < b;
  }
}

int main() {
  int n;
  cin >> n;

  vector<double> X(n, 0.0);
  vector<double> Y(n, 0.0);
  for (int i = 0; i < n; i++) {
    cin >> X.at(i) >> Y.at(i);
  }

  vector<int> Z;
  for (int i = 0; i < (1 << n); i++) {
    if (i % 2 == 0 || __builtin_popcount(i) <= 1) continue;
    Z.push_back(i);
  }
  sort(Z.begin(), Z.end(), compare_by_bitcount);

  vector<vector<double>> A(1 << n, vector<double>(n, INF));
  A.at(1).at(0) = 0;
  for (int bits : Z) {
    vector<int> S;
    for (int i = 0; i < n; i++) {
      if ((bits >> i) & 1) {
        S.push_back(i);
      }
    }
    for (int j : S) {
      if (j == 0) continue;
      for (int k : S) {
        if (k == j) continue;
        double d = pow((X.at(k) - X.at(j)), 2) + pow((Y.at(k) - Y.at(j)), 2);
        d = sqrt(d);
        A.at(bits).at(j) = min(A.at(bits).at(j), A.at(bits - (1 << j)).at(k) + d);
      }
    }
  }

  double ans = INF;
  for (int i = 1; i < n; i++) {
    double d = pow((X.at(i) - X.at(0)), 2) + pow((Y.at(i) - Y.at(0)), 2);
    d = sqrt(d);
    ans = min(ans, A.at((1 << n) - 1).at(i) + d);
  }
  cout << (int)ans << endl;
  return 0;
}