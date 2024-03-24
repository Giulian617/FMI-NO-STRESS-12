#include <vector>
#include <iostream>

using namespace std;
using i64 = int64_t;

namespace Combinatorics {
  constexpr int MOD = 1e9 + 9;

  vector<int> factorial, inverse_factorial;

  int lg_pow(int a, int b) {
    int answer = 1;
    while (b > 0) {
      if (b % 2 > 0) {
        answer = (i64)answer * a % MOD;
      }
      a = (i64)a * a % MOD;
      b /= 2;
    }
    return answer;
  }

  void init(int N) {
    factorial.resize(N + 1);
    inverse_factorial.resize(N + 1);
    factorial[0] = factorial[1] = 1;
    for (int i = 2; i <= N; i++) {
      factorial[i] = (i64)i * factorial[i - 1] % MOD;
    }
    inverse_factorial[N] = lg_pow(factorial[N], MOD - 2);
    for (int i = N - 1; i >= 0; i--) {
      inverse_factorial[i] = (i64)inverse_factorial[i + 1] * (i + 1) % MOD;
    }
  }

  int nCk(int N, int K) {
    return (i64)factorial[N] * inverse_factorial[K] % MOD * inverse_factorial[N - K] % MOD;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, K;
  cin >> N >> K;
  vector<int> color(N);
  for (int& x : color) {
    cin >> x;
  }

  int must_remove = 0;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    if (color[u] != color[v]) {
      must_remove++;
    }
  }

  K -= must_remove + 1;
  int M = N - 1 - must_remove;

  Combinatorics::init(N);
  int answer = 0;
  for (int take = 0; take <= K; take++) {
    answer += Combinatorics::nCk(M, take);
    if (answer >= Combinatorics::MOD) {
      answer -= Combinatorics::MOD;
    }
  }

  cout << answer << "\n";
  
  return 0;
}