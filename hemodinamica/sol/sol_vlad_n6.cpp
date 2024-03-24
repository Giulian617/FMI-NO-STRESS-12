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
  for (int x_low = 0; x_low < N; x_low++) {
    for (int y_low = 0; y_low < M; y_low++) {
      for (int x_high = x_low; x_high < N; x_high++) {
        for (int y_high = y_low; y_high < M; y_high++) {
          for (int i = x_low; i <= x_high; i++) {
            for (int j = y_low; j <= y_high; j++) {
              if (A[i][j] != B[i][j]) {
                answer++;
              }
            }
          }
        }
      }
    }
  }
  cout << answer << "\n";
  
  return 0;
}