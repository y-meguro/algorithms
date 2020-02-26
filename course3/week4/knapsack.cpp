#include <bits/stdc++.h>
using namespace std;

int main() {
  int W, n;
  cin >> W >> n;
  vector<int> v(n + 1);
  vector<int> w(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> v.at(i) >> w.at(i);
  }

  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= W; j++) {
      if (j >= w.at(i)) {
        dp.at(i).at(j) = max(dp.at(i - 1).at(j), dp.at(i - 1).at(j - w.at(i)) + v.at(i));
      } else {
        dp.at(i).at(j) = dp.at(i - 1).at(j);
      }
    }
  }
  cout << dp.at(n).at(W) << endl;
  return 0;
}