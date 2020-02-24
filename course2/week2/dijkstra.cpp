#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;
const int INF = 1e9;

struct Edge {
  int to, cost;
  Edge(int to, int cost): to(to), cost(cost) {}
};

int n = 200;
vector<vector<Edge>> G(n);

struct Dijkstra {
  vector<int> d;

  Dijkstra(int s) {
    d.resize(n, INF);
    d.at(s) = 0;

    priority_queue<P, vector<P>, greater<P>> q;
    q.push(make_pair(0, s));

    while (!q.empty()) {
      P p = q.top();
      q.pop();
      int v = p.second;
      if (d.at(v) < p.first) continue;

      for (Edge e : G.at(v)) {
        if (d.at(e.to) > d.at(v) + e.cost) {
          d.at(e.to) = d.at(v) + e.cost;
          q.push(make_pair(d.at(e.to), e.to));
        }
      }
    }
  }

  int fare(int x) {
    if (d.at(x) == INF) return 1000000;
    return d.at(x);
  }
};

int main() {
  ifstream ifs("dijkstraData.txt");
  string line;
  for (int row = 0; getline(ifs, line); row++) {
    istringstream stream(line);
    string data;
    for (int col = 0; stream >> data; col++) {
      if (col == 0) continue;
      int pos = data.find(',');
      int to = stoi(data.substr(0, pos));
      to--;
      int cost = stoi(data.substr(pos + 1));
      G.at(row).emplace_back(to, cost);
    }
  }

  Dijkstra di(0);
  vector<int> v = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
  for (int i = 0; i < (int)v.size(); i++) {
    int t = v.at(i) - 1;
    if (i != (int)v.size() - 1) {
      cout << di.fare(t) << ",";
    } else {
      cout << di.fare(t) << endl;
    }
  }
  return 0;
}