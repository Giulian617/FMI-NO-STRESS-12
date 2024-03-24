#include <iostream>
#include <vector>
#include <utility>

using namespace std;
using Point = pair<int, int>;
using i64 = int64_t;

class BIT2D {
public:
  BIT2D(int N, int M) : N(N), M(M), bit(N + 1, vector<int>(M + 1)) {}
  void update(int x, int y, int val) {
    for (int i = x + 1; i <= N; i += i & -i) {
      for (int j = y + 1; j <= M; j += j & -j) {
        bit[i][j] += val;
      }
    }
  }
  int query(int x, int y) {
    int res = 0;
    for (int i = x + 1; i > 0; i -= i & -i) {
      for (int j = y + 1; j > 0; j -= j & -j) {
        res += bit[i][j];
      }
    }
    return res;
  }

private:
  int N, M;
  vector<vector<int>> bit;
};

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

  vector<vector<Point>> where(N * N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      where[A[i][j]].emplace_back(i, j);
    }
  }

  BIT2D bit(N, N);
  i64 answer = 0;
  for (int val = 0; val < N * N; val++) {
    for (const auto &[x, y] : where[val]) {
      bit.update(x, y, 1);
    }
    for (const auto &[x, y] : where[val]) {
      answer += bit.query(x, y) - 1;
    }
    for (const auto &[x, y] : where[val]) {
      bit.update(x, y, -1);
    }
  }

  cout << answer << "\n";

  return 0;
}