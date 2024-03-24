#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <assert.h>
#include <fstream>
using namespace std;
using i64 = int64_t;

const int MOD = 998'244'353;

enum Color {
  BLACK = 1, 
  RED = 0
};

enum State {
  EQUAL = 1, 
  NOT_EQUAL = 0
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<vector<int>> G(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  vector<vector<int>> tree(N);
  function<void(int, int)> init = [&](int u, int parrent) -> void {
    for (const int& v : G[u]) {
      if (v != parrent) {
        init(v, u);
        tree[u].push_back(v);
      }
    }
  };
  init(0, -1);

  function<int(int, int)> mlt = [&](int a, int b) -> int {
    return (i64)a * b % MOD;
  };

  int H = 2 * ceil(log2(N)) + 2;
  vector<vector<vector<vector<int>>>> dp(N, vector<vector<vector<int>>>(H + 1, vector<vector<int>>(2, vector<int>(2))));
  function<void(int)> dfs = [&](int u) -> void {
    for (const int& v : tree[u]) {
      dfs(v);
    }
    if (tree[u].empty()) {
      dp[u][0][BLACK][EQUAL] = 1;
      return;
    }

    assert(tree[u].size() == 2);
    int v1 = tree[u].front(), v2 = tree[u].back();

    for (int h = 0; h <= H; h++) {
      // Case when I want the subtree to be a RBT
      (dp[u][h][RED][EQUAL] += mlt(dp[v1][h][BLACK][EQUAL], 
                                    dp[v2][h][BLACK][EQUAL])) %= MOD;
      if (h > 0) {
        for (const auto& v1_color : {RED, BLACK}) {
          for (const auto& v2_color : {RED, BLACK}) {
            (dp[u][h][BLACK][EQUAL] += mlt(dp[v1][h - 1][v1_color][EQUAL], 
                                          dp[v2][h - 1][v2_color][EQUAL])) %= MOD;
          }
        }
      }

      // I do not wait the subtree to be a RBT
      // RED first
      if (h > 0) {
        (dp[u][h][RED][NOT_EQUAL] += mlt(dp[v1][h][BLACK][EQUAL], 
                                        dp[v2][h - 1][BLACK][EQUAL])) %= MOD;
        (dp[u][h][RED][NOT_EQUAL] += mlt(dp[v1][h - 1][BLACK][EQUAL], 
                                        dp[v2][h][BLACK][EQUAL])) %= MOD;

        (dp[u][h][RED][NOT_EQUAL] += mlt(dp[v1][h][BLACK][NOT_EQUAL], 
                                        dp[v2][h - 1][BLACK][EQUAL])) %= MOD;
        (dp[u][h][RED][NOT_EQUAL] += mlt(dp[v1][h - 1][BLACK][EQUAL], 
                                        dp[v2][h][BLACK][NOT_EQUAL])) %= MOD;
      }
      (dp[u][h][RED][NOT_EQUAL] += mlt(dp[v1][h][BLACK][NOT_EQUAL], 
                                      dp[v2][h][BLACK][EQUAL])) %= MOD;
      (dp[u][h][RED][NOT_EQUAL] += mlt(dp[v1][h][BLACK][EQUAL], 
                                      dp[v2][h][BLACK][NOT_EQUAL])) %= MOD;
      (dp[u][h][RED][NOT_EQUAL] += mlt(dp[v1][h][BLACK][NOT_EQUAL], 
                                      dp[v2][h][BLACK][NOT_EQUAL])) %= MOD;

      // Now BLACK
      if (h > 1) {
        for (const auto& v1_color : {RED, BLACK}) {
          for (const auto& v2_color : {RED, BLACK}) {
            (dp[u][h][BLACK][NOT_EQUAL] += mlt(dp[v1][h - 1][v1_color][EQUAL], 
                                        dp[v2][h - 2][v2_color][EQUAL])) %= MOD;
            (dp[u][h][BLACK][NOT_EQUAL] += mlt(dp[v1][h - 2][v1_color][EQUAL], 
                                        dp[v2][h - 1][v2_color][EQUAL])) %= MOD;
            
            (dp[u][h][BLACK][NOT_EQUAL] += mlt(dp[v1][h - 1][v1_color][NOT_EQUAL], 
                                        dp[v2][h - 2][v2_color][EQUAL])) %= MOD;
            (dp[u][h][BLACK][NOT_EQUAL] += mlt(dp[v1][h - 2][v1_color][EQUAL], 
                                        dp[v2][h - 1][v2_color][NOT_EQUAL])) %= MOD;
          }
        }
      }
      if (h > 0) {
        for (const auto& v1_color : {RED, BLACK}) {
          for (const auto& v2_color : {RED, BLACK}) {
            (dp[u][h][BLACK][NOT_EQUAL] += mlt(dp[v1][h - 1][v1_color][EQUAL], 
                                        dp[v2][h - 1][v2_color][NOT_EQUAL])) %= MOD;
            (dp[u][h][BLACK][NOT_EQUAL] += mlt(dp[v1][h - 1][v1_color][NOT_EQUAL], 
                                        dp[v2][h - 1][v2_color][EQUAL])) %= MOD;
            (dp[u][h][BLACK][NOT_EQUAL] += mlt(dp[v1][h - 1][v1_color][NOT_EQUAL], 
                                        dp[v2][h - 1][v2_color][NOT_EQUAL])) %= MOD;
          }
        }
      }
    }
  };
  dfs(0);

  int answer = 0;
  for (int h = 0; h <= H; h++) {
    (answer += (dp[0][h][BLACK][NOT_EQUAL])) %= MOD;
  }

  cout << answer << "\n";

  return 0;
}