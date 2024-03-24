#include <iostream>
#include <vector>
#include <utility>
using namespace std;

using Point = pair<int, int>;
using i64 = int64_t;

class BIT {
public:
  BIT(int N_) : N(N_), tree(N + 1) {}
  void update(int pos, int delta) {
    for (int i = pos + 1; i <= N; i += i & -i) {
      tree[i] += delta;
    }
  }
  int query(int pos) {
    int res = 0;
    for (int i = pos + 1; i > 0; i -= i & -i) {
      res += tree[i];
    }
    return res;
  }
private:
  int N;
  vector<int> tree;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;
  vector<vector<int>> A(N, vector<int>(N));
  vector<int> fr(N * N);
  for (auto &row : A) {
    for (auto &x : row) {
      cin >> x;
      x--;
      fr[x]++;
    }
  }

  vector<vector<Point>> where(N * N);
  for (int i = 0; i < N * N; i++) {
    where[i].reserve(fr[i]);
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      where[A[i][j]].emplace_back(i, j);
    }
  }

  BIT bit(N);
  i64 answer = 0;

  for (int val = 0; val < N * N; val++) {
    for (size_t i = 0; i < where[val].size(); i++) {
      size_t j = i;
      while (j < where[val].size() && where[val][j].first == where[val][i].first) {
        answer += j - i + 1;
        answer += bit.query(where[val][j].second);
        j++;
      }
      for (size_t k = i; k < j; k++) {
        bit.update(where[val][k].second, 1);
      }
      i = j - 1;
    }
    for (const auto &[_, y] : where[val]) {
      bit.update(y, -1);
    }
  }

  cout << answer << "\n";

  return 0;
}