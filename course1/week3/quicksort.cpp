#include <bits/stdc++.h>
using namespace std;

int choosePivot1(vector<int>& input, int l, int r) {
  return input.at(l);
}

int choosePivot2(vector<int>& input, int l, int r) {
  swap(input.at(l), input.at(r));
  return choosePivot1(input, l, r);
}

int choosePivot3(vector<int>& input, int l, int r) {
  int first = input.at(l);
  int middle = input.at((l + r) / 2);
  int final = input.at(r);

  int maxNum = max(max(first, middle), final);
  int minNum = min(min(first, middle), final);

  if (middle != maxNum && middle != minNum) {
    swap(input.at(l), input.at((l + r) / 2));
  } else if (final != maxNum && final != minNum) {
    swap(input.at(l), input.at(r));
  }
  return choosePivot1(input, l, r);
}

int partition(vector<int>& input, int l, int r) {
  if (l >= r) return 0;

  // コメントアウトを外して、1つだけ有効にする
  // int pivot = choosePivot1(input, l, r); // question1
  // int pivot = choosePivot2(input, l, r); // question2
  int pivot = choosePivot3(input, l, r); // question3
  int i = l + 1;
  for (int j = l + 1; j <= r; j++) {
    if (input.at(j) < pivot) {
      swap(input.at(i), input.at(j));
      i++;
    }
  }
  swap(input.at(l), input.at(i - 1));
  int num1 = partition(input, l, i - 2);
  int num2 = partition(input, i, r);
  return num1 + num2 + (r - l);
}

int main() {
  int n = 10000;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a.at(i);
  }
  cout << partition(a, 0, n - 1) << endl;
  return 0;
}