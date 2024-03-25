#include <bits/stdc++.h>
using namespace std;
ifstream f("text.in");
ofstream g("text.out");
#define f cin
#define g cout
const int nmax = 200009, mod = 9 + 1e9;
int n, k, col[nmax], ans, tot;
int fact[nmax], invfact[nmax];

int inverse(int x)
{
    int p = mod - 2, ans = 1;
    while (p)
    {
        if (p & 1)
            ans = (1LL * ans * x) % mod;
        x = (1LL * x * x) % mod;
        p >>= 1;
    }
    return ans;
}
int nchoosek(int n, int k)
{
    return (1LL * fact[n] * inverse((1LL * fact[k] * fact[n - k]) % mod)) % mod;
}
int main()
{
    ios_base::sync_with_stdio(false);
    f.tie(0);

    fact[0] = 1;
    for (int i = 1; i < nmax; i++)
        fact[i] = 1LL * fact[i - 1] * i % mod;

    f >> n >> k;
    for (int i = 1; i <= n; i++)
        f >> col[i];
	tot=n-1;
	k--;
    for (int i = 1, x, y; i < n; i++)
    {
        f >> x >> y;
        if (col[x] != col[y])
            tot--,k--;
    }

    for (int t = 0; t <= min(tot, k); t++)
        (ans += nchoosek(tot, t)) %= mod;

    g << ans;
    return 0;
}
