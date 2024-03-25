// Ilie Dumitru
#include<cstdio>
#include<set>
const int VMAX = 100005;

struct personalitate
{
	int baza, exp, x;

	friend bool operator<(personalitate p, personalitate q)
	{
		if(p.exp != q.exp)
			return p.exp < q.exp;
		if(p.baza != q.baza)
			return p.baza < q.baza;
		return p.x < q.x;
	}
};

int N;
int divs[VMAX];

void precalc()
{
	int i, j;

	for(i = 2;i < VMAX;++i)
		if(!divs[i])
			for(j = i;j < VMAX;j += i)
				divs[j] = i;
}

personalitate factorize(int x)
{
	personalitate p;
	int d, e;

	p.x = x;
	p.exp = 0;
	p.baza = 1;
	while(x != 1)
	{
		d = divs[x];
		e = 0;
		do
		{
			++e;
			x /= d;
		}while(divs[x] == d);

		if(e > p.exp)
		{
			p.exp = e;
			p.baza = d;
		}
	}

	return p;
}

int main()
{
	int i, x;
	personalitate pers, max;

	precalc();
	max.exp = 0;

	scanf("%d", &N);
	for(i = 0;i < N;++i)
	{
		scanf("%d", &x);
		pers = factorize(x);
		if(max < pers)
			max = pers;
	}

	printf("%d\n", max.x);

	return 0;
}