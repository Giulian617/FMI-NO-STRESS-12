// Ilie Dumitru
#include<cstdio>
#include<vector>
typedef long long ll;
const int NMAX = 100005, LOG = 40;
const ll MOD = 1000000007;

int N;
std::vector<int> G[NMAX];
enum colors{BLACK, RED, COLMAX};
enum DIFFERENCE{SAME, DIFF, DIFFMAX};
ll dp[NMAX][COLMAX][DIFFMAX][LOG];

void dfs(int node, int tt = -1)
{
	if(node == -1 || G[node].size() == 0u || (G[node].size() == 1u && G[node][0] == tt))
	{
		dp[node][BLACK][SAME][0] = 1;
		return;
	}

	int l = -1, r = -1, i;

	for(i = 0;i < (int)G[node].size();++i)
		if(G[node][i] != tt)
		{
			if(l == -1)
				l = G[node][i];
			else if(r == -1)
				r = G[node][i];
		}

	dfs(l, node);
	dfs(r, node);

	for(i = 0;i < LOG;++i)
	{
		// All depth is i or i + 1
		if(i + 1 < LOG)
			dp[node][BLACK][SAME][i + 1] = (dp[l][RED][SAME][i] + dp[l][BLACK][SAME][i]) % MOD * ((dp[r][RED][SAME][i] + dp[r][BLACK][SAME][i]) % MOD) % MOD;
		dp[node][RED][SAME][i] = dp[l][BLACK][SAME][i] * dp[r][BLACK][SAME][i] % MOD;

		// There is both depth i and i - 1 (or i + 1 and i)
		if(i + 1 < LOG)
		{
			dp[node][BLACK][DIFF][i + 1] = (dp[l][RED][SAME][i] + dp[l][BLACK][SAME][i]) % MOD * ((i > 0 ? dp[r][RED][SAME][i - 1] + dp[r][BLACK][SAME][i - 1] : 0) % MOD) % MOD
										 + (i > 0 ? dp[l][RED][SAME][i - 1] + dp[l][BLACK][SAME][i - 1] : 0) % MOD * ((dp[r][RED][SAME][i] + dp[r][BLACK][SAME][i]) % MOD) % MOD
										 + (dp[l][RED][DIFF][i] + dp[l][BLACK][DIFF][i]) % MOD * ((dp[r][RED][DIFF][i] + dp[r][RED][SAME][i] + dp[r][BLACK][DIFF][i] + dp[r][BLACK][SAME][i] + (i > 0 ? dp[r][RED][SAME][i - 1] + dp[r][BLACK][SAME][i - 1] : 0 )) % MOD) % MOD
										 + (dp[l][RED][SAME][i] + dp[l][BLACK][SAME][i] + (i > 0 ? dp[l][RED][SAME][i - 1] + dp[l][BLACK][SAME][i - 1] : 0)) % MOD * ((dp[r][RED][DIFF][i] + dp[r][BLACK][DIFF][i]) % MOD) % MOD;
		}
		dp[node][RED][DIFF][i] = dp[l][BLACK][SAME][i] % MOD * ((i > 0 ? dp[r][BLACK][SAME][i - 1] : 0) % MOD) % MOD
							   + (i > 0 ? dp[l][BLACK][SAME][i - 1] : 0) % MOD * dp[r][BLACK][SAME][i] % MOD
							   + (dp[l][BLACK][DIFF][i]) % MOD * ((dp[r][BLACK][DIFF][i] + dp[r][BLACK][SAME][i] + (i > 0 ? dp[r][BLACK][SAME][i - 1] : 0 )) % MOD) % MOD
							   + (dp[l][BLACK][SAME][i] + (i > 0 ? dp[l][BLACK][SAME][i - 1] : 0)) % MOD * dp[r][BLACK][DIFF][i] % MOD;
	}
}

int main()
{
	int i, a, b;
	ll ans = 0;

	scanf("%d", &N);
	for(i = 1;i < N;++i)
	{
		scanf("%d%d", &a, &b);
		G[--a].push_back(--b);
		G[b].push_back(a);
	}

	dfs(0);
	for(i = 0;i < LOG;++i)
		ans = (ans + dp[0][BLACK][DIFF][i]) % MOD;

	printf("%lld\n", ans);

	return 0;
}