#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;

  vector<int> w(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> w.at(i);
  }

  vector<ll> dp(n + 1, 0);
  dp.at(0) = 0;
  dp.at(1) = w.at(1);
  for (int i = 2; i <= n; i++) {
    dp.at(i) = max(dp.at(i - 1), dp.at(i - 2) + w.at(i));
  }

  set<int> IS;
  int k = n;
  while (k >= 2) {
    if (dp.at(k - 1) >= dp.at(k - 2) + w.at(k)) {
      k -= 1;
    } else {
      IS.insert(k);
      k -= 2;
    }
  }
  if (k == 1) IS.insert(1);

  vector<int> target = {1, 2, 3, 4, 17, 117, 517, 997};
  string ans = "";
  for (int i = 0; i < (int)target.size(); i++) {
    int x = target.at(i);
    if (IS.count(x)) {
      ans += "1";
    } else {
      ans += "0";
    }
  }
  cout << ans << endl;
  return 0;
}