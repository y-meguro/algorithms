#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Job {
  int weight, length;
  Job(int weight, int length): weight(weight), length(length) {}
};

bool compare_jobs1(Job a, Job b) {
  if(a.weight - a.length == b.weight - b.length){
    return a.weight > b.weight;
  } else {
    return a.weight - a.length > b.weight - b.length;
  }
}

bool compare_jobs2(Job a, Job b) {
  if((double)a.weight / a.length == (double)b.weight / b.length){
    return a.weight > b.weight;
  } else {
    return (double)a.weight / a.length > (double)b.weight / b.length;
  }
}

int main() {
  int n;
  cin >> n;

  vector<Job> a;
  for (int i = 0; i < n; i++) {
    int w, l;
    cin >> w >> l;
    a.emplace_back(w, l);
  }

  // sort(a.begin(), a.end(), compare_jobs1); // for question1
  sort(a.begin(), a.end(), compare_jobs2); // for question2

  ll ans = 0;
  ll time = 0;
  for (int i = 0; i < n; i++) {
    time += a.at(i).length;
    ans += a.at(i).weight * time;
  }
  cout << ans << endl;
  return 0;
}