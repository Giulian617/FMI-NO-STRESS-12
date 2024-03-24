#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int count_max_changes(const std::vector<int>& P) {
  int max_value = 0, count = 0;
  for (const int value : P) {
    if (value > max_value) {
      max_value = value;
      count++;
    }
  }
  return count;
}

int main() {
  int N, K;
  cin >> N >> K;

  vector<int> P(N);
  iota(P.begin(), P.end(), 1);
  int answer = 0;

  do {
    answer += count_max_changes(P) <= K;
  } while (next_permutation(P.begin(), P.end()));

  cout << answer << "\n";

  return 0;
}