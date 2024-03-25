// Ilie "The-Winner" Dumitru
#include<cstdio>
#include<algorithm>

const int NMAX=200005, MOD=666013;

struct segTree
{
	int N;
	int v[NMAX<<2];

	void init(int _N, int val)
	{
		N=_N;
		init(0, 0, N-1, val);
	}
	void init(int node, int l, int r, int val)
	{
		if(l==r)
			v[node]=val;
		else
		{
			int mid=l+((r-l)>>1);

			init((node<<1)|1, l, mid, val);
			init((node<<1)+2, mid+1, r, val);

			v[node]=v[(node<<1)|1]+v[(node<<1)+2];
		}
	}

	void update(int pos, int val)
	{
		update(0, 0, N-1, pos, val);
	}
	void update(int node, int l, int r, int pos, int val)
	{
		if(l==r)
			v[node]=val;
		else
		{
			int mid=l+((r-l)>>1);

			if(pos<=mid)
				update((node<<1)|1, l, mid, pos, val);
			else
				update((node<<1)+2, mid+1, r, pos, val);

			v[node]=(v[(node<<1)|1]+v[(node<<1)+2])%MOD;
		}
	}

	int query(int l, int r)
	{
		return query(0, 0, N-1, l, r);
	}
	int query(int node, int l, int r, int a, int b)
	{
		if(a<=l && r<=b)
			return v[node];

		int mid=l+((r-l)>>1);

		if(a<=mid && mid<b)
			return (query((node<<1)|1, l, mid, a, b)+query((node<<1)+2, mid+1, r, a, b))%MOD;
		if(a<=mid)
			return query((node<<1)|1, l, mid, a, b);
		return query((node<<1)+2, mid+1, r, a, b);
	}

	int findKth1(int k)
	{
		return findKth1(0, 0, N-1, k);
	}
	int findKth1(int node, int l, int r, int k)
	{
		if(l==r)
			return l;

		int mid=l+((r-l)>>1);

		if(v[(node<<1)|1]>k)
			return findKth1((node<<1)|1, l, mid, k);
		return findKth1((node<<1)+2, mid+1, r, k-v[(node<<1)|1]);
	}
};

struct query
{
	int op, idx, pos, val;
};

int N, M;
segTree S;
query Q[NMAX];

int main()
{
	int i, last[2]={-1, -1}, ans=0;

	scanf("%d", &N);
	for(i=0;i<N;++i)
	{
		scanf("%d", &Q[i].op);
		Q[i].idx=i;
		if(Q[i].op!=3)
		{
			scanf("%d%d", &Q[i].pos, &Q[i].val);
			++M;
		}
	}

	S.init(M, 1);
	for(i=N-1;i>-1;--i)
		if(Q[i].op!=3)
		{
			Q[i].pos=S.findKth1(Q[i].pos);
			S.update(Q[i].pos, 0);
		}

	for(i=0;i<N;++i)
	{
		if(Q[i].op==3)
			(ans+=S.query(std::min(last[0], last[1]), std::max(last[0], last[1])))%=MOD;
		else
		{
			S.update(Q[i].pos, Q[i].val);
			last[Q[i].op-1]=Q[i].pos;
		}
	}

	printf("%d\n", ans);

	return 0;
}