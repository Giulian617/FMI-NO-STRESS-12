#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> A(N);
  for (int& x : A) {
    cin >> x;
  }

  function<pair<int, int>(int)> get_personality = [&](int N) -> pair<int, int> {
    vector<pair<int, int>> factors;
    for (int d = 2; d * d <= N; d++) {
      int e = 0;
      while (N % d == 0) {
        e++;
        N /= d;
      }
      if (e > 0) {
        factors.push_back({e, d});
      }
    }
    if (N > 1) {
      factors.push_back({1, N});
    }
    return *max_element(factors.begin(), factors.end());
  };

  // (exponenet, prime, value)
  cout << *max_element(A.begin(), A.end(), [&](const int& lhs, const int& rhs) {
    const auto [exp_lhs, prime_lhs] = get_personality(lhs);
    const auto [exp_rhs, prime_rhs] = get_personality(rhs);
    tuple<int, int, int> lhs_compare = {exp_lhs, prime_lhs, lhs}, rhs_compare = {exp_rhs, prime_rhs, rhs};
    return lhs_compare < rhs_compare;
  }) << "\n";

  return 0;
}