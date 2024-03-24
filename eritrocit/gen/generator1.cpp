#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include <set>

using namespace std;

vector<int> get_mapping(int N) {
  vector<int> P(N);
  iota(P.begin(), P.end(), 0);

  random_device rd;
  mt19937 g(rd());
  shuffle(P.begin(), P.end(), g);
  return P;
}

vector<pair<int, int>> generate_tree(int N, int T_range) {
  random_device rd;
  mt19937 gen(rd());
  
  vector<pair<int, int>> edges;
  for (int i = 1; i < N; i++) {
    uniform_int_distribution<int> distrib(max(0, i - T_range), i - 1);
    int u = distrib(gen);
    edges.push_back({i, u});
  }

  auto mapping = get_mapping(N);
  for (auto &[u, v] : edges) {
    u = mapping[u];
    v = mapping[v];
  }
  return edges;
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " <N> <M>" << endl;
    return 1;
  }

  int N = atoi(argv[1]);
  int K = atoi(argv[2]);
  int T_range = atoi(argv[3]);
  int zones = atoi(argv[4]);

  auto T = generate_tree(N, T_range);

  // get zones - 1 random edges and color the nodes (if not colored)
  // dfs and color each comp now
  // problem for this approach: we have a big probability to get many small components
  // should make a new generator to devide the tree in zones equal zones

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> distrib(0, N - 1);

  set<int> removed_edges;
  while (removed_edges.size() < zones - 1) {
    removed_edges.insert(distrib(gen));
  }

  vector<vector<int>> G(N);
  for (int i = 0; i < N; i++) {
    if (removed_edges.find(i) == removed_edges.end()) {
      const auto& [u, v] = T[i];
      G[u].push_back(v);
      G[v].push_back(u);
    }
  }

  vector<int> color(N);
  function<void(int, int, int)> dfs = [&](int u, int parrent, int color_with) -> void {
    color[u] = color_with;
    for (const int& v : G[u]) {
      if (v != parrent) {
        dfs(v, u, color_with);
      }
    }
  };

  int colors = 0;
  for (int u = 0; u < N; u++) {
    if (color[u] == 0) {
      dfs(u, -1, colors + 1);
      colors++;
    }
  }

  cout << N << " " << K << "\n";
  for (const int& x : color) {
    cout << x << " ";
  }
  cout << "\n";
  for (const auto& [u, v] : T) {
    cout << u + 1 << " " << v + 1 << "\n";
  }

  return 0;
}