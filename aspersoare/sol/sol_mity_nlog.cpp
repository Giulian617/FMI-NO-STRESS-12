// Mity O(N*logN)
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
const int NMAX=100005;

struct d_intv
{
	double l, r;

	friend bool operator<(d_intv a, d_intv b)
	{
		return a.l<b.l || (a.l==b.l && a.r>b.r);
	}
};

int L, W, N;
d_intv u[NMAX];

int main()
{
	int i, j, x, r;
	double d;

	scanf("%d%d%d", &N, &L, &W);
	for(i=0;i<N;++i)
	{
		scanf("%d%d", &x, &r);
		if(r*2>=W)
		{
			d=sqrt(r*(double)r-W*(double)W*0.25);
			u[i].l=std::max(0., x-d);
			u[i].r=std::min((double)L, x+d);
		}
		else
		{
			--N;
			--i;
		}
	}

	std::sort(u, u+N);
	for(i=1, j=0;i<N;++i)
		if(u[i].r>u[j].r)
			u[++j]=u[i];
	N=j+1;

	if(u[0].l || L!=u[N-1].r)
		printf("Imposibil\n");
	else
	{
		for(i=1;i<N;++i)
			if(u[i].l>u[i-1].r)
				i=N;
		if(i==N)
		{
			std::vector<d_intv> intv;
			intv.push_back(u[0]);
			for(i=1;i<N;++i)
			{
				while(intv.size()>1u && intv.end()[-2].r>=u[i].l)
					intv.pop_back();
				intv.push_back(u[i]);
			}
			printf("%d\n", (int)intv.size());
		}
		else
			printf("Imposibil\n");
	}
	return 0;
}