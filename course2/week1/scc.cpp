#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

vector<vector<int>> G;
vector<vector<int>> Grev;

vector<bool> explored1;
vector<bool> explored2;
vector<P> f;

int t = 0;
int num = 0;

void dfs1(int v) {
  if (explored1.at(v)) return;
  explored1.at(v) = true;
  for (int u : Grev.at(v)) {
    if (explored1.at(u)) continue;
    dfs1(u);
  }
  t++;
  f.at(v) = P(t, v);
}

void dfs2(int v) {
  if (explored2.at(v)) return;
  explored2.at(v) = true;
  num++;
  for (int u : G.at(v)) {
    if (explored2.at(u)) continue;
    dfs2(u);
  }
}

int main() {
  int n = 875714;
  G.resize(n);
  Grev.resize(n);
  while (true) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    G.at(a).push_back(b);
    Grev.at(b).push_back(a);
    if (cin.eof()) break;
  }

  explored1.resize(n, false);
  explored2.resize(n, false);
  f.resize(n);

  // Grevをdfsしてf(i)を得る
  for (int i = n - 1; i >= 0; i--) {
    if (explored1.at(i)) continue;
    dfs1(i);
  }

  sort(f.begin(), f.end());
  reverse(f.begin(), f.end());

  // f(i)の降順で調べていき、sccのサイズを得る
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    int j = f.at(i).second;
    if (explored2.at(j)) continue;
    num = 0;
    dfs2(j);
    ans.push_back(num);
  }

  sort(ans.begin(), ans.end());
  reverse(ans.begin(), ans.end());

  for (int i = 0; i < 5; i++) {
    cout << ans.at(i) << endl;
  }

  return 0;
}