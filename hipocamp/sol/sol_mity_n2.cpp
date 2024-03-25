// Ilie Dumitru
#include<cstdio>
#pragma GCC optimize("unroll-loops")
typedef long long ll;
const int NMAX = 200005;
const ll MOD = 998244353;

int N, K;
ll dp[NMAX];

int main()
{
	int i, j;
	ll ans = 0;

	scanf("%d%d", &N, &K);

	dp[1] = 1;
	for(i = 1;i < N;++i)
	{
		for(j = i;j > 0;--j)
		{
			dp[j + 1] = (dp[j + 1] + dp[j]) % MOD;
			dp[j] = dp[j] * i % MOD;
		}
	}

	for(i = 1;i <= K;++i)
		ans = (ans + dp[i]) % MOD;
	printf("%lld\n", ans);
}