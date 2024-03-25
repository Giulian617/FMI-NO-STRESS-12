// Ilie Dumitru
#include<cstdio>
#include<vector>
#include<algorithm>
const int NMAX = 1024, oo = NMAX;

struct edge
{
	int node, cap, otherId;
};

int N[3], src, dst;
std::vector<edge> G[NMAX];
int last[NMAX], curr;

void addEdge(int u, int v, int cap)
{
	int lenv = (int)G[v].size(), lenu = (int)G[u].size();

	G[u].push_back({v, cap, lenv});
	G[v].push_back({u, cap, lenu});
}

void pushFlow(int src, int idx, int flow)
{
	int dst = G[src][idx].node;
	int dstIdx = G[src][idx].otherId;

	G[src][idx].cap -= flow;
	G[dst][dstIdx].cap += flow;
}

int dfs(int node, int maxPush = oo * NMAX)
{
	if(node == dst)
		return maxPush;

	int i, x, total = 0;
	last[node] = curr;

	for(i = 0;i < (int)G[node].size() && maxPush;++i)
		if(last[G[node][i].node] < last[node] && G[node][i].cap)
		{
			x = dfs(G[node][i].node, std::min(maxPush, G[node][i].cap));
			maxPush -= x;
			total += x;
			if(x)
				pushFlow(node, i, x);
		}

	return total;
}

int FF()
{
	++curr;
	return dfs(src);
}

int main()
{
	int i, a, b, tip, cap, x, _, flux = 0;

	scanf("%d%d%d", N, N + 1, N + 2);
	src = (N[0] + N[1] + N[2]) * 2;
	dst = src + 1;
	for(i = 0;i < N[0];++i)
	{
		scanf("%d", &cap);
		addEdge(i, i + N[0], cap);
		addEdge(src, i, oo * NMAX);
	}
	for(i = 0;i < N[1];++i)
	{
		scanf("%d", &cap);
		addEdge(i + N[0] * 2, i + N[0] * 2 + N[1], cap);
	}
	for(i = 0;i < N[2];++i)
	{
		scanf("%d", &cap);
		addEdge(i + N[0] * 2 + N[1] * 2, i + N[0] * 2 + N[1] * 2 + N[2], cap);
		addEdge(i + N[0] * 2 + N[1] * 2 + N[2], dst, oo * NMAX);
	}

	scanf("%d", &_);
	do
	{
		scanf("%d%d%d%d", &tip, &a, &b, &cap);
		--a;
		--b;
		if(tip == 1)
			addEdge(a + N[0], b + N[0] * 2, cap);
		else
			addEdge(a + N[0] * 2 + N[1], b + N[0] * 2 + N[1] * 2, cap);
	}while(--_);

	while((x = FF()))
		flux += x;

	printf("%d\n", flux);

	return 0;
}