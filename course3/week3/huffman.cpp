#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

int n;
vector<P> childs;

int minHeight(int s) {
  if (s < n) return 0;
  P p = childs.at(s);
  return min(minHeight(p.first), minHeight(p.second)) + 1;
}

int maxHeight(int s) {
  if (s < n) return 0;
  P p = childs.at(s);
  return max(maxHeight(p.first), maxHeight(p.second)) + 1;
}

int main() {
  cin >> n;

  priority_queue<P, vector<P>, greater<P>> q;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    q.push(P(x, i));
  }

  int m = n * 2 - 1;
  childs.resize(m, P(-1, -1));
  for (int i = n; i < m; i++) {
    P p1 = q.top();
    q.pop();
    P p2 = q.top();
    q.pop();

    q.push(P(p1.first + p2.first, i));
    childs.at(i) = P(p1.second, p2.second);
  }
  cout << "maxHeight " << maxHeight(m - 1) << endl;
  cout << "minHeight " << minHeight(m - 1) << endl;
  return 0;
}