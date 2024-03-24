#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <numeric>

using namespace std;
using i64 = int64_t;
using Edge = pair<int, int>;
using WeightedEdge = tuple<int, int, int>;
using Graph = vector<vector<Edge>>;

const int MOD = 998'244'353;
const i64 INF = numeric_limits<i64>::max() / 3;

pair<int, vector<WeightedEdge>> read_input(istream& in) {
  int N, M;
  in >> N >> M;
  vector<WeightedEdge> edges(M);
  for (auto& [u, v, c] : edges) {
    in >> u >> v >> c;
    u--, v--;
  }
  return {N, edges};
}

Graph build_graph(const int N, const vector<WeightedEdge>& edges) {
  Graph G(N);
  for (const auto& [u, v, c] : edges) {
    G[u].emplace_back(v, c);
    G[v].emplace_back(u, c);
  }
  return G;
}

pair<vector<i64>, vector<int>> Dijkstra(const vector<vector<Edge>> &G, int source) {
  int N = G.size();
  vector<i64> dist(N, INF);
  vector<int> cnt_paths(N);
  cnt_paths[source] = 1;
  dist[source] = 0;
  priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> Q;
  Q.push({0, source});
  while (!Q.empty()) {
    auto [u_dist, u] = Q.top();
    Q.pop();
    if (dist[u] < u_dist) {
      continue;
    }
    for (const auto& [v, w] : G[u]) {
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        cnt_paths[v] = cnt_paths[u];
        Q.push({dist[v], v});
      } else if (dist[v] == dist[u] + w) {
        (cnt_paths[v] += cnt_paths[u]) %= MOD;
      }
    }
  }
  return {dist, cnt_paths};
}

vector<int> count_for_each_edge(const vector<i64>& dist_1, const vector<i64>& dist_2, const vector<int>& cnt_1, 
                                const vector<int>& cnt_2, const vector<WeightedEdge>& edges, const i64 target) {
  vector<int> answer(edges.size());
  for (size_t i = 0; i < edges.size(); i++) {
    const auto [u, v, c] = edges[i];
    if (dist_1[u] + c + dist_2[v] == target) {
      (answer[i] += (i64)cnt_1[u] * cnt_2[v] % MOD) %= MOD;
    }
    if (dist_1[v] + c + dist_2[u] == target) {
      (answer[i] += (i64)cnt_1[v] * cnt_2[u] % MOD) %= MOD;
    }
  }
  return answer;
}

void print_sol(ostream& out, const vector<int>& answer) {
  int result = accumulate(answer.begin(), answer.end(), 0, [&](const int acc, const int x) {
    return (acc + x) % MOD;
  });
  out << result << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  auto [N, edges] = read_input(std::cin);
  auto G = build_graph(N, edges);

  auto [distance_from_sink, cnt_paths_from_sink] = Dijkstra(G, 0);
  auto [distance_from_source, cnt_paths_from_source] = Dijkstra(G, 1);

  auto answer = count_for_each_edge(distance_from_sink, distance_from_source, cnt_paths_from_sink, 
                                    cnt_paths_from_source, edges, distance_from_sink[1]);

  print_sol(std::cout, answer);

  return 0;
}