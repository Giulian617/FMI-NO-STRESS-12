// Daniel O(N^2 * log)
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;


template <typename T>
class Fenwick {
private:
    vector <T> bit;
    int n;
public:
    Fenwick(int n) : n(n), bit(1 + n, 0) {}
    void add(int pos, T val) {
        while (pos <= n) {
            bit[pos] += val;
            pos += pos & -pos;
        }
    }
    T get(int pos) {
        T ans = 0;
        while (pos > 0) {
            ans += bit[pos];
            pos -= pos & -pos;
        }
        return ans;
    }
    T get(int l, int r) {
        return get(r) - get(l - 1);
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    assert(N <= 5000);
    vector <vector <int>> A(N, vector <int>(N));
       vector<vector <pair <int, int>>> values(N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
            assert(1 <= A[i][j] && A[i][j] <= N * N);
            A[i][j]--;
            values[A[i][j]].emplace_back(i, j);
        }
    i64 answer = 0;
    Fenwick <int> DS(N);


    auto solve = [&](int val) {
        auto& v = values[val];
        int sz = (int)v.size();
        for (int i = 0; i < sz; i++) {
            int j = i;
            while (j < sz && v[j].first == v[i].first) {
                answer += j - i + 1;
                answer += DS.get(v[j].second + 1);
                j++;
            }
            for (int k = i; k < j; k++)
                DS.add(v[k].second + 1, +1);
            i = j - 1;
        }
        for (auto& it : v) {
            DS.add(it.second + 1, -1);
        }
    };

    for (int i = 0; i < N * N; i++) {
        solve(i);
    }

    cout << answer << "\n";
    return 0;
}