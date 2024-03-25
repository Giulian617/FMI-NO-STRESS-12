// Ilie "The-Winner" Dumitru
#include<cstdio>
#include<vector>
const int NMAX=100001;

int N;
int v[NMAX];
int cnt, sol[NMAX];

int main()
{
	int i;

	scanf("%d", &N);
	++N;
	for(i=1;i<N;++i)
		scanf("%d", v+i);

	for(i=1;i<N;++i)
		if(v[i]!=v[i-1])
			sol[cnt++]=i;

	printf("%d\n", cnt);
	for(i=0;i<cnt;++i)
		printf("%d ", sol[i]);
	return 0;
}