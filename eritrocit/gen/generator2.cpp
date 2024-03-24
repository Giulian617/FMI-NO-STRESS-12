#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>

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

  // Create a tree with zones nodes. 
  // Replace each node in this tree with a tree of size N / zones

  auto T = generate_tree(zones, T_range);

  int avg_size = N / zones;
  vector<int> sizes(zones, avg_size);
  sizes.back() += N % zones;

  vector<vector<pair<int, int>>> t(zones);
  int sum_so_far = 0;
  for (int i = 0; i < zones; i++) {
    t[i] = generate_tree(sizes[i], T_range);
    for (auto &[u, v] : t[i]) {
      u += sum_so_far;
      v += sum_so_far;
    }
    sum_so_far += sizes[i];
  }

  vector<pair<int, int>> edges;
  edges.reserve(N - 1);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> distrib(0, N - 1);
  vector<vector<int>> G(N);
  for (const auto& tree : t) {
    for (const auto& [u, v] : tree) {
      G[u].push_back(v);
      G[v].push_back(u);
      edges.push_back({u, v});
    }
  }
  for (const auto& [u_id, v_id] : T) {
    int u = t[u_id][distrib(gen) % (sizes[u_id] - 1)].first, v = t[v_id][distrib(gen) % (sizes[v_id] - 1)].first;
    G[u].push_back(v);
    G[v].push_back(u);

    edges.push_back({u, v});
  }

  vector<int> color(N);
  for (int i = 0; i < zones; i++) {
    for (const auto& [u, v] : t[i]) {
      color[u] = color[v] = i + 1;
    }
  }

  cerr << "edges count = " << edges.size() << "\n";
  assert(edges.size() == N - 1);
  
  cout << N << " " << K << "\n";
  for (const int& x : color) {
    cout << x << " ";
  }
  cout << "\n";
  for (const auto& [u, v] : edges) {
    cout << u + 1 << " " << v + 1 << "\n";
  }

  return 0;
}