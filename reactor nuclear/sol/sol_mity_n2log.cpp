// Mity O(N*N*log)
#include<cstdio>
#include<vector>
typedef long long ll;
const int NMAX=2048, BLKSZ=20;

struct pos
{
	int i, j;
};

struct bit
{
	int N;
	int v[NMAX];

	void init(int _N)
	{
		int i;

		N=_N+1;
		for(i=0;i<N;++i)
			v[i]=0;
	}

	void update(int pos, int x)
	{
		++pos;
		while(pos<N)
		{
			v[pos]+=x;
			pos+=pos&-pos;
		}
	}

	int query(int pos)
	{
		int s=0;

		++pos;
		while(pos)
		{
			s+=v[pos];
			pos-=pos&-pos;
		}

		return s;
	}
};

int N;
std::vector<pos> ap[NMAX*NMAX];
ll ans;
bit B;

void processSmall(int val)
{
	int i, j;

	for(i=0;i<(int)ap[val].size();++i)
		for(j=i;j<(int)ap[val].size();++j)
			if(ap[val][i].j<=ap[val][j].j)
				++ans;
}

void processBig(int val)
{
	int i;

	for(i=0;i<(int)ap[val].size();++i)
	{
		B.update(ap[val][i].j, 1);
		ans+=B.query(ap[val][i].j);
	}
	for(i=0;i<(int)ap[val].size();++i)
	{
		B.update(ap[val][i].j, -1);
	}
}

int main()
{
	int i, j, x;

	scanf("%d", &N);
	B.init(N);
	for(i=0;i<N;++i)
		for(j=0;j<N;++j)
		{
			scanf("%d", &x);
			ap[--x].push_back({i, j});
		}

	for(i=0;i<N*N;++i)
		if(ap[i].size()>=BLKSZ)
			processBig(i);
		else
			processSmall(i);

	printf("%I64d\n", ans);
	return 0;
}