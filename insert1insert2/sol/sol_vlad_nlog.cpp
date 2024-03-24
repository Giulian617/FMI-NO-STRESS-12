#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = int64_t;

struct Query {
  short type;
  int pos, value;
};

template<class T>
class FenwickTree {
public:
  FenwickTree(int N_, T init_value = 0) : N(N_ + 1), tree(N_ + 1, init_value) {
    for (int i = 1; i <= N; i++) {
      int nxt = i + (i & (-i));
      if (nxt <= N) {
        tree[nxt] += tree[i];
      }
    }
  }
  T query(int pos) {
    T answer = 0;
    for (int i = ++pos; i > 0; i -= (i & (-i))) {
      answer += tree[i];
    }
    return answer;
  }
  void update(int pos, T value) {
    for (int i = ++pos; i <= N; i += (i & (-i))) {
      tree[i] += value;
    } 
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
  int find_kth(T k) {
    int pos = 0;
    for (int i = find_next_power_of_two(N); i > 0; i >>= 1) {
      if (pos + i <= N && tree[pos + i] < k) {
        k -= tree[pos + i];
        pos += i;
      }
    }
    return pos + 1;
  }
private:
  int N;
  vector<T> tree;

  static int find_next_power_of_two(const int x) {
    int answer = 1;
    while (answer < x) {
      answer <<= 1;
    }
    return answer;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<Query> queries(N);
  for (auto& [type, pos, value] : queries) {
    cin >> type;
    if (type != 3) {
      cin >> pos >> value;
    }
  }

  FenwickTree<i64> positions(N, +1);
  reverse(queries.begin(), queries.end());
  for (auto& [type, pos, value] : queries) {
    if (type != 3) {
      pos = positions.find_kth(pos + 1) - 1;
      positions.update(pos, -1);
    }
  }
  reverse(queries.begin(), queries.end());
  FenwickTree<i64> values(N);
  int last_op_1 = 0, last_op_2 = 0;
  i64 answer = 0;
  for (const auto& [type, pos, value] : queries) {
    if (type == 1) {
      values.update(pos, value);
      last_op_1 = pos;
    } else if (type == 2) {
      values.update(pos, value);
      last_op_2 = pos;
    } else {
      int l = min(last_op_1, last_op_2), r = max(last_op_1, last_op_2);
      answer += values.query(l, r);
    }
  }

  const int MOD = 666'013;
  cout << answer % MOD << '\n';

  return 0;
}