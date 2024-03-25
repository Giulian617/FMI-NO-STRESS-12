// Ilie Dumitru
#include<cstdio>
#include<vector>
#include<queue>
typedef long long ll;
const int NMAX = 200005;
const ll MOD = 998244353;

struct edge
{
	int node;
	ll dist;

	friend bool operator<(edge a, edge b)
	{
		return a.dist > b.dist;
	}
};

int N;
std::vector<edge> G[NMAX];
int a[3][NMAX];
ll minDist[2][NMAX], ways[2][NMAX];

void dijkstra(int start, ll* min, ll* w)
{
	int node, i;
	ll len;
	std::priority_queue<edge> pq;

	for(i = 0;i < N;++i)
	{
		min[i] = 1LL << 60;
		w[i] = 0;
	}
	pq.push({start, 0});
	w[start] = 1;
	min[start] = 0;

	do
	{
		node = pq.top().node;
		len = pq.top().dist;
		pq.pop();

		if(len == min[node])
			for(i = 0;i < (int)G[node].size();++i)
			{
				if(min[node] + G[node][i].dist < min[G[node][i].node])
				{
					min[G[node][i].node] = min[node] + G[node][i].dist;
					w[G[node][i].node] = w[node];
					pq.push({G[node][i].node, min[G[node][i].node]});
				}
				else if(min[node] + G[node][i].dist == min[G[node][i].node])
					w[G[node][i].node] = (w[G[node][i].node] + w[node]) % MOD;
			}
	}while(!pq.empty());
}

ll getWays(int a, int b, int c)
{
	if(minDist[0][a] + c + minDist[1][b] == minDist[0][1])
		return (ways[0][a] * ways[1][b]) % MOD;
	if(minDist[1][a] + c + minDist[0][b] == minDist[0][1])
		return (ways[1][a] * ways[0][b]) % MOD;
	return 0;
}

int main()
{
	int i, a, b, c, _;
	ll ans = 0;

	scanf("%d%d", &N, &_);
	for(i = 0;i < _;++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		G[--a].push_back({--b, c});
		G[b].push_back({a, c});
		::a[0][i] = a;
		::a[1][i] = b;
		::a[2][i] = c;
	}

	dijkstra(0, minDist[0], ways[0]);
	dijkstra(1, minDist[1], ways[1]);

	for(i = 0;i < _;++i)
		ans = (ans + getWays(::a[0][i], ::a[1][i], ::a[2][i])) % MOD;
	printf("%lld\n", ans);

	return 0;
}