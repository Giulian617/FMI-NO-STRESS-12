#include <iostream>
#include <vector>
using namespace std;
using i64 = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> A(N, vector<int>(M)), B(N, vector<int>(M));
  for (auto& row : A) {
    for (auto& x : row) {
      cin >> x;
    }
  }
  for (auto& row : B) {
    for (auto& x : row) {
      cin >> x;
    }
  }

  i64 answer = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (A[i][j] != B[i][j]) {
        answer += (i64)(i + 1) * (j + 1) * (N - i) * (M - j);
      }
    }
  }
  cout << answer << "\n";

  return 0;
}