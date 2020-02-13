#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mergeAndCountSplitInv(vector<int>& left, vector<int>& right, vector<int>& input) {
  int lenL = left.size();
  int lenR = right.size();
  int i = 0;  // left の index
  int j = 0;  // right の index
  ll res = 0;
  vector<int> sorted;

  for (int k = 0; k < lenL + lenR; k++) {
    if (i >= lenL) {
      sorted.push_back(right.at(j));
      j++;
    } else if (j >= lenR) {
      sorted.push_back(left.at(i));
      i++;
    } else if (left.at(i) < right.at(j)) {
      sorted.push_back(left.at(i));
      i++;
    } else {
      sorted.push_back(right.at(j));
      j++;
      res += lenL - i;
    }
  }
  input = sorted;
  return res;
}

ll sortAndCount(vector<int>& input) {
  int n = input.size();
  if (n == 1) return 0;

  vector<int> left(input.begin(), input.begin() + n/2);
  vector<int> right(input.begin() + n/2, input.end());

  ll x = sortAndCount(left);
  ll y = sortAndCount(right);
  ll z = mergeAndCountSplitInv(left, right, input);
  return x + y + z;
}

int main() {
  int n = 100000;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a.at(i);
  }
  cout << sortAndCount(a) << endl;
  return 0;
}