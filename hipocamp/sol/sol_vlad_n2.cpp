#include <iostream>
#include <vector>

using namespace std;
using i64 = int64_t;

int main() {
  int N, K;
  cin >> N >> K;

  const int MOD = 998'244'353;

  vector<vector<int>> S(N + 1, vector<int>(K + 1));
  S[1][1] = 1;
  for (int i = 2; i <= N; i++) {
    for (int j = 1; j <= K; j++) {
      S[i][j] = (i64)S[i - 1][j] * (i - 1) % MOD + S[i - 1][j - 1];
      if (S[i][j] >= MOD) {
        S[i][j] -= MOD;
      }
    }
  }

  int answer = 0;
  for (int i = 1; i <= K; i++) {
    answer += S[N][i];
    if (answer >= MOD) {
      answer -= MOD;
    }
  }

  cout << answer << "\n";

  return 0;
}