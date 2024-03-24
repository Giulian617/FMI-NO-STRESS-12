#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using i64 = int64_t;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M, H, U, Q;
  cin >> N >> M >> H >> U >> Q;

  vector<vector<vector<i64>>> S(N, vector<vector<i64>>(M, vector<i64>(H)));
  function<void(int, int, int, int, int, int, int)> range_update = [&](int x1, int y1, int z1, int x2, int y2, int z2, int val) -> void {
    S[x1][y1][z1] += val;
    if (z2 < H - 1) {
      S[x1][y1][z2 + 1] -= val;
    }
    if (y2 < M - 1) {
      S[x1][y2 + 1][z1] -= val;
    }
    if (x2 < N - 1) {
      S[x2 + 1][y1][z1] -= val;
    }
    if (y2 < M - 1 && z2 < H - 1) {
      S[x1][y2 + 1][z2 + 1] += val;
    }
    if (x2 < N - 1 && z2 < H - 1) {
      S[x2 + 1][y1][z2 + 1] += val;
    }
    if (x2 < N - 1 && y2 < M - 1) {
      S[x2 + 1][y2 + 1][z1] += val;
    }
    if (x2 < N - 1 && y2 < M - 1 && z2 < H - 1) {
      S[x2 + 1][y2 + 1][z2 + 1] -= val;
    }
  };

  for (int i = 0; i < U; i++) {
    int x1, y1, z1, x2, y2, z2, val;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> val;
    x1--, y1--, z1--, x2--, y2--, z2--;
    range_update(x1, y1, z1, x2, y2, z2, val);
  }

  for (int rep = 0; rep < 2; rep++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) { 
        for (int k = 0; k < H; k++) {
          if (i > 0) {
            S[i][j][k] += S[i - 1][j][k];
          }
          if (j > 0) {
            S[i][j][k] += S[i][j - 1][k];
          }
          if (k > 0) {
            S[i][j][k] += S[i][j][k - 1];
          }
          if (i > 0 && j > 0) {
            S[i][j][k] -= S[i - 1][j - 1][k];
          }
          if (i > 0 && k > 0) {
            S[i][j][k] -= S[i - 1][j][k - 1];
          }
          if (j > 0 && k > 0) {
            S[i][j][k] -= S[i][j - 1][k - 1];
          }
          if (i > 0 && j > 0 && k > 0) {
            S[i][j][k] += S[i - 1][j - 1][k - 1];
          }
        }
      }
    }
  }

  function<i64(int, int, int, int, int, int)> query = [&](int x1, int y1, int z1, int x2, int y2, int z2) -> i64 {
    i64 answer = S[x2][y2][z2];
    if (x1 > 0) {
      answer -= S[x1 - 1][y2][z2];
    }
    if (y1 > 0) {
      answer -= S[x2][y1 - 1][z2];
    }
    if (z1 > 0) {
      answer -= S[x2][y2][z1 - 1];
    }
    if (x1 > 0 && y1 > 0) {
      answer += S[x1 - 1][y1 - 1][z2];
    }
    if (x1 > 0 && z1 > 0) {
      answer += S[x1 - 1][y2][z1 - 1];
    }
    if (y1 > 0 && z1 > 0) {
      answer += S[x2][y1 - 1][z1 - 1];
    }
    if (x1 > 0 && y1 > 0 && z1 > 0) {
      answer -= S[x1 - 1][y1 - 1][z1 - 1];
    }
    return answer;
  };

  for (int q = 0; q < Q; q++) {
    int x1, y1, z1, x2, y2, z2;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    x1--; y1--; z1--; x2--; y2--; z2--;
    cout << query(x1, y1, z1, x2, y2, z2) << '\n';
  }

  return 0;
}