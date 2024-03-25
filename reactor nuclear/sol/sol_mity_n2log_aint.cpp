// Mity O(N*N*log)
#include<cstdio>
#include<vector>
typedef long long ll;
const int NMAX=4096;

struct aint
{
	int v[NMAX<<2];
	short N;

	void init(short _N)
	{
		N=_N;
	}

	void update(short pos, short x)
	{
		update(0, 0, N-1, pos, x);
	}

	void update(short node, short l, short r, short pos, short x)
	{
		v[node]+=x;
		if(l!=r)
		{
			short mid=(l+r)/2;
			if(pos<=mid)
				update((node<<1)|1, l, mid, pos, x);
			else
				update((node<<1)+2, mid+1, r, pos, x);
		}
	}

	int query(short pos)
	{
		return query(0, 0, N-1, pos);
	}

	int query(short node, short l, short r, short p)
	{
		if(r<=p)
			return v[node];
		short mid=(l+r)/2;
		if(p<=mid)
			return query((node<<1)|1, l, mid, p);
		return v[(node<<1)|1] + query((node<<1)+2, mid+1, r, p);
	}
};

int N;
std::vector<short> ap[NMAX*NMAX];
ll ans;
aint B;

int main()
{
	int i, j, x, val;

	scanf("%d", &N);
	B.init(N);
	for(i=0;i<N;++i)
		for(j=0;j<N;++j)
		{
			scanf("%d", &x);
			ap[--x].push_back(j);
		}

	for(val=0;val<N*N;++val)
	{
		for(i=0;i<(int)ap[val].size();++i)
		{
			B.update(ap[val][i], 1);
			ans+=B.query(ap[val][i]);
		}
		for(i=0;i<(int)ap[val].size();++i)
		{
			B.update(ap[val][i], -1);
		}
	}

	printf("%I64d\n", ans);
	return 0;
}