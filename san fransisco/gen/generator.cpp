#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <functional>
#include <limits.h>

using namespace std;
using Edge = tuple<int, int, int>;

const int MAX_N = numeric_limits<int>::max() / 2;

#define dbg(x) cerr << #x << " = " << x << "\n";

void generate_good_edges(const int N, vector<Edge>& edges, const int M) {
  int added_edges = 0;
  for (int delta = 1; added_edges < M; delta++) {
    dbg(added_edges);
    for (int i = 0; i < N - delta && added_edges < M; i++) {
      edges.emplace_back(i, i + delta, delta);
      added_edges++;
    }
  }
}

void generate_bad_edges(const int N, vector<Edge>& edges, const int M) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> nodes_distr(0, N - 1);
  uniform_int_distribution<int> values_distr(MAX_N / 2, MAX_N);
  for (int i = 0; i < M; i++) {
    int u = nodes_distr(gen), v = nodes_distr(gen);
    while (u != v) {
      v = nodes_distr(gen);
    }
    int c = values_distr(gen);
    edges.emplace_back(u, v, c);
  }
}

void replace_root_with_0(vector<Edge>& edges, const int root) {
  function<void(int&, int)> replace_values = [&](int& a, int root) -> void {
    if (a == 1) {
      a = root;
    } else if (a == root) {
      a = 1;
    }
  };
  for (auto& [a, b, c] : edges) {
    replace_values(a, root);
    replace_values(b, root);
  }
}

int main(int argc, char** argv) {
  int N = atoi(argv[1]), M = atoi(argv[2]), R = atoi(argv[3]);

  vector<Edge> edges;
  edges.reserve(M + R);
  generate_good_edges(N, edges, M);
  generate_bad_edges(N, edges, R);
  replace_root_with_0(edges, N - 1);

  cout << N << " " << M + R << "\n";
  for (const auto& [a, b, c] : edges) {
    cout << a + 1 << " " << b + 1 << " " << c << "\n";
  } 

  return 0;
}