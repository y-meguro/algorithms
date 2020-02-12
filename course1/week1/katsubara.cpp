#include <bits/stdc++.h>
using namespace std;

string add(string x, string y) {
  int len = max(x.size(), y.size());
  int carry = 0;
  string ans = "";

  while ((int)x.size() < len) x = "0" + x;
  while ((int)y.size() < len) y = "0" + y;

  for (int i = len - 1; i >= 0; i--) {
    int num1 = x[i] - '0';
    int num2 = y[i] - '0';
    int res = num1 + num2 + carry;
    if (res >= 10) {
      carry = 1;
      res -= 10;
    } else {
      carry = 0;
    }
    ans = to_string(res) + ans;
  }
  if (carry == 1) ans = "1" + ans;
  while (ans[0] == '0') ans.erase(ans.begin()); // 最上位の桁が0の場合は削除する
  return ans;
}

// x - y を計算する。答えが正の結果となるような入力しか与えられないとする
string subtract(string x, string y) {
  int len = x.size();
  int borrow = 0;
  string ans = "";

  while ((int)y.size() < len) y = "0" + y;

  for (int i = len - 1; i >= 0; i--) {
    int num1 = x[i] - '0';
    int num2 = y[i] - '0';
    int res = num1 - num2 - borrow;
    if (res < 0) {
      borrow = 1;
      res += 10;
    } else {
      borrow = 0;
    }
    ans = to_string(res) + ans;
  }

  while (ans[0] == '0') ans.erase(ans.begin()); // 最上位の桁が0の場合は削除する
  return ans;
}

string karatsuba(string x, string y) {
  int len = max(x.size(), y.size());
  while ((int)x.size() < len) x = "0" + x;
  while ((int)y.size() < len) y = "0" + y;

  if (len <= 1) {
    return to_string(stoi(x) * stoi(y));
  }
  string a = x.substr(0, len/2);
  string b = x.substr(len/2, len - len/2);
  string c = y.substr(0, len/2);
  string d = y.substr(len/2, len - len/2);

  string p = karatsuba(a, c);
  string q = karatsuba(add(a, b), add(c, d));
  string r = karatsuba(b, d);

  q = subtract(q, p);
  q = subtract(q, r);

  for (int i = 0; i < (len - len/2) * 2; i++) p += "0";
  for (int i = 0; i < len - len/2; i++) q += "0";

  string res = add(p, q);
  res = add(res, r);
  while (res[0] == '0') res.erase(res.begin()); // 最上位の桁が0の場合は削除する
  return res;
}

int main() {
  string x, y;
  cin >> x >> y;
  cout << karatsuba(x, y) << endl;
  return 0;
}