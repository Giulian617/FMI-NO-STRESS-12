#include <iostream>
#include <vector>
#include <utility>

using namespace std;
using Point = pair<int, int>;
using i64 = int64_t;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<vector<int>> A(N, vector<int>(N));
  for (auto& row : A) {
    for (auto& x : row) {
      cin >> x;
    }
  }

  i64 answer = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int i_low = 0; i_low <= i; i_low++) {
        for (int j_low = 0; j_low <= j; j_low++) {
          if (A[i][j] == A[i_low][j_low]) {
            answer++;
          }
        }
      }
    }
  }

  cout << answer << '\n';

  return 0;
}