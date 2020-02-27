#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

int n;
vector<vector<int>> G;
vector<vector<int>> Grev;

void addEdge(int a, int b) {
  G.at(-a + n).push_back(b + n);
  G.at(-b + n).push_back(a + n);
  Grev.at(b + n).push_back(-a + n);
  Grev.at(a + n).push_back(-b + n);
}

vector<bool> explored1;
vector<bool> explored2;
vector<P> f;
vector<int> leader;
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
  leader.at(v) = num;
  for (int u : G.at(v)) {
    if (explored2.at(u)) continue;
    dfs2(u);
  }
}

int main() {
  cin >> n;
  int m = n * 2 + 1;

  G.resize(m);
  Grev.resize(m);

  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    addEdge(a, b);
  }

  explored1.resize(m, false);
  explored2.resize(m, false);
  f.resize(m);
  leader.resize(m);

  for (int i = m - 1; i >= 0; i--) {
    if (explored1.at(i)) continue;
    dfs1(i);
  }

  sort(f.begin(), f.end());
  reverse(f.begin(), f.end());

  for (int i = 0; i < m; i++) {
    int j = f.at(i).second;
    if (explored2.at(j)) continue;
    dfs2(j);
    num++;
  }

  for (int i = 1; i <= n; i++) {
    if (leader.at(n - i) == leader.at(n + i)) {
      cout << 0 << endl;
      return 0;
    }
  }
  cout << 1 << endl;
  return 0;
}