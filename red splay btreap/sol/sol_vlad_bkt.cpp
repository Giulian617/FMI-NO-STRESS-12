#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include <fstream>
#include <limits>

using namespace std;
using Graph = vector<vector<int>>;

const int INF = 100'000'000;

enum Color {
  BLACK = true, 
  RED = false
};

Graph read_input(istream& in) {
  int N;
  in >> N;
  Graph G(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    in >> u >> v;
    u--, v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  return G;
}

Graph init_tree(const Graph& G) {
  int N = G.size();
  Graph T(N);
  function<void(int, int)> dfs = [&](int u, int parrent) -> void {
    for (const int v : G[u]) {
      if (v != parrent) {
        T[u].push_back(v);
        dfs(v, u);
      }
    }
  };
  dfs(0, -1);
  return T;
}

pair<int, int> find_black_h(const Graph& T, const vector<Color>& color, int u) {
  pair<int, int> answer = {-INF, INF};
  if (T[u].empty()) {
    return {color[u] == BLACK, color[u] == BLACK};
  }
  for (const int v : T[u]) {
    auto const [max_h, min_h] = find_black_h(T, color, v);
    answer.first = max(answer.first, max_h);
    answer.second = min(answer.second, min_h);
  }
  if (color[u] == BLACK) {
    answer.first++, answer.second++;
  }
  return answer;
}

bool dfs(const Graph& T, const vector<Color>& color, int u) {
  if (T[u].empty()) {
    return color[u] == BLACK;
  }
  bool answer = true;
  const int a = T[u].front(), b = T[u].back();
  if (color[u] == RED && (color[a] == RED || color[b] == RED)) {
    return false;
  }
  answer &= dfs(T, color, a) & dfs(T, color, b);
  const auto [a_h_max, a_h_min] = find_black_h(T, color, a);
  const auto [b_h_max, b_h_min] = find_black_h(T, color, b);
  int max_h = max(a_h_max, b_h_max), min_h = min(a_h_min, b_h_min);
  if (abs(max_h - min_h) > 1) {
    return false;
  }
  return answer;
}

bool check_solution(const Graph& T, const vector<Color>& color, bool print_sol = false) {
  if (color[0] == RED) {
    return false;
  }
  bool can_color = dfs(T, color, 0);
  const auto [h_max, h_min] = find_black_h(T, color, 0);
  can_color &= (h_max == h_min + 1);
  if (print_sol) {
    if (can_color) {
      // cerr << h_max << " " << h_min << "\n";
      for (const Color c : color) {
        cerr << (c ? "B" : "R");
      }
      cerr << "\n";
    }
  }
  return can_color;
}

int count_solutions(const Graph& T) {
  int N = T.size(), answer = 0;
  for (int mask = 0; mask < (1 << N); mask++) {
    vector<Color> colors(N);
    for (int i = 0; i < N; i++) {
      Color bit = (mask & (1 << i)) ? RED : BLACK;
      colors[i] = bit;
    }
    answer += check_solution(T, colors, true);
  }
  return answer;
}

int main() {
  auto G = read_input(std::cin);
  G = init_tree(G);

  cout << count_solutions(G) << "\n";

  return 0;
}