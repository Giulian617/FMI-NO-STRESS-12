#include <bits/stdc++.h>
using namespace std;
const string file_name = "text";
ifstream f(file_name + ".in");
ofstream g(file_name + ".out");
#define f cin
#define g cout
const int mod = 666013;
class FT
{
    vector<int> bit;
    int n;

public:
    FT(int n, int val) : n(n)
    {
        bit.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            bit[i] += val;
            if (i + (i & -i) <= n)
                bit[i + (i & -i)] += bit[i];
        }
    }
    void add(int pos, int val)
    {
        for (int i = pos; i <= n; i += i & -i)
            (bit[i] += val) %= mod;
    }
    int search(int val)
    {
        int sum = 0, pos = 0;
        for (int lg = 1 << 18; lg; lg >>= 1)
            if (pos + lg <= n && sum + bit[pos + lg] < val)
                sum += bit[pos += lg];
        return pos + 1;
    }
    long long sum(int pos)
    {
        long long sum = 0;
        for (int i = pos; i; i -= i & -i)
            (sum += bit[i]) %= mod;
        return sum;
    }
    long long sum(int left, int right)
    {
        return (mod + sum(right) - sum(left - 1)) % mod;
    }
};

struct query
{
    int type, pos, val, real_pos;
};

string ss("");
vector<query> queries;
int q, n, last1, last2, s;
int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    f.tie(0);
    f >> q;
    queries.resize(q);
    for (query &i : queries)
    {
        f >> i.type;
        if (i.type != 3)
            f >> i.pos >> i.val, n++;
    }

    FT ft_p(n, 1);
    FT ft_v(n, 0);
    for (auto it = queries.rbegin(); it != queries.rend(); it++)
        if (it->type != 3)
        {
            it->real_pos = ft_p.search(it->pos + 1);
            ft_p.add(it->real_pos, -1);
        }

    for (query &i : queries)
        if (i.type == 1)
        {
            ft_v.add(i.real_pos, i.val);
            last1 = i.real_pos;
        }
        else if (i.type == 2)
        {
            ft_v.add(i.real_pos, i.val);
            last2 = i.real_pos;
        }
        else
            (s += ft_v.sum(min(last1, last2), max(last1, last2))) %= mod;
    g << s;
    return 0;
}
