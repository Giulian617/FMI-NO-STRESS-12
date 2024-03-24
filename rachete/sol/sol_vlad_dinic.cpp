#include <iostream>
#include <vector>

using namespace std;

#include <queue>
#include <functional>
#include <limits>
struct Edge {
  int to, flow, capacity, reverse;
};

class Network {
private:
  bool bfs() {
    fill(level.begin(), level.end(), -1);
    queue<int> Q;
    Q.push(source);
    level[source] = 0;
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (auto &e : G[u]) {
        if (level[e.to] == -1 && e.flow < e.capacity) {
          level[e.to] = level[u] + 1;
          Q.push(e.to);
        }
      }
    }
    return level[sink] != -1;
  }
  int dfs(int u, int can_push) {
    if (u == sink) {
      return can_push;
    }
    for (int &i = index[u]; i < (int)G[u].size(); ++i) {
      auto &e = G[u][i];
      if (level[e.to] == level[u] + 1 && e.flow < e.capacity) {
        int flow = dfs(e.to, min(can_push, e.capacity - e.flow));
        if (flow > 0) {
          e.flow += flow;
          G[e.to][e.reverse].flow -= flow;
          return flow;
        }
      }
    }
    return 0;
  }
public:
  Network(int N, int source, int sink) : source(source), sink(sink), level(N), index(N), G(N) {}
  void add_edge(int u, int v, int capacity) {
    G[u].push_back({v, 0, capacity, (int)G[v].size()});
    G[v].push_back({u, 0, 0, (int)G[u].size() - 1});
  }
  int max_flow() {
    int flow = 0;
    while (bfs()) {
      fill(index.begin(), index.end(), 0);
      while (int pushed = dfs(source, INF)) {
        flow += pushed;
      }
    }
    return flow;
  }
  vector<int> min_cut() {
    max_flow();
    vector<int> A;
    vector<bool> visited(G.size());
    function<void(int)> dfs = [&](int u) {
      A.push_back(u);
      visited[u] = true;
      for (auto &e : G[u]) {
        if (e.capacity > e.flow && !visited[e.to]) {
          dfs(e.to);
        }
      }
    };
    dfs(source);
    return A;
  }
  vector<vector<Edge>> get_graph() {
    return G;
  }
private:
  const int INF = numeric_limits<int>::max() / 2;
  int source, sink;
  vector<int> level, index;
  vector<vector<Edge>> G;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int motors, capsules, crews;
  cin >> motors >> capsules >> crews;
  vector<int> motors_cnt(motors), capsules_cnt(capsules), crew_cnt(crews);
  for (int& x : motors_cnt) {
    cin >> x;
  }
  for (int& x : capsules_cnt) {
    cin >> x;
  }
  for (int& x : crew_cnt) {
    cin >> x;
  }

  int source = motors + 2 * capsules + crews, sink = source + 1;
  Network network(sink + 1, source, sink);
  for (int i = 0; i < motors; i++) {
    network.add_edge(source, i, motors_cnt[i]);
  }
  for (int i = 0; i < capsules; i++) {
    network.add_edge(motors + i, motors + capsules + i, capsules_cnt[i]);
  }
  for (int i = 0; i < crews; i++) {
    network.add_edge(motors + 2 * capsules + i, sink, crew_cnt[i]);
  }

  int M;
  cin >> M;
  for (int i = 0; i < M; i++) {
    int type, a, b, c;
    cin >> type >> a >> b >> c;
    a--, b--;
    if (type == 1) {
      network.add_edge(a, motors + b, c);
    } else {
      network.add_edge(a + motors + capsules, motors + 2 * capsules + b, c);
    }
  }

  int flow = network.max_flow();
  cout << flow << '\n';

  return 0;
}