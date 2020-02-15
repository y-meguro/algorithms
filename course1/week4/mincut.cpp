#include <bits/stdc++.h>
using namespace std;

int mincut(map<int, vector<int>>& graph) {
  while ((int)graph.size() > 2) {
    // 1つ目の頂点をランダムに選択
    int a = rand() % graph.size();
    auto itr = next(graph.begin(), a);
    int u = itr->first;

    // 2つ目の頂点は、1つ目の頂点とつながっているものから選択(厳密にはランダムでないが、これでランダムに辺を選んだことにする)
    int v = graph.at(u).at(rand() % graph.at(u).size());

    // 2つを統合する
    for (int x : graph.at(v)) {
      auto itr = find(graph.at(x).begin(), graph.at(x).end(), v);
      *itr = u;
    }
    graph.at(u).insert(graph.at(u).end(), graph.at(v).begin(), graph.at(v).end());
    graph.at(u).erase(remove(graph.at(u).begin(), graph.at(u).end(), u), graph.at(u).end());
    graph.erase(v);
  }

  int res;
  for (auto e : graph) {
    res = e.second.size();
    break;
  }
  return res;
}

int main() {
  int N = 200; // 試行回数
  srand((unsigned int)time(NULL));

  map<int, vector<int>> G;

  ifstream ifs("input.txt");
  string line;
  for (int row = 0; getline(ifs, line); row++) {
    istringstream stream(line);
    int data;
    for (int col = 0; stream >> data; col++) {
      data--;
      if (data == row) continue;
      G[row].push_back(data);
    }
  }

  int ans = 1e9;
  for (int i = 0; i < N; i++) {
    map<int, vector<int>> tmpG = G;
    int tmp = mincut(tmpG);
    ans = min(ans, tmp);
  }
  cout << ans << endl;
  return 0;
}