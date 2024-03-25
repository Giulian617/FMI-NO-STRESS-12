// Ilie "The-Winner" Dumitru
#include<bits/stdc++.h>

std::mt19937 rng;

int getNext(int low, int high)
{
	return std::uniform_int_distribution<int>(low, high)(rng);
}

int main(int argc, char* argv[])
{
	int seed;
	int N, M, H, _0, _1;
	int i;
	int x[2], y[2], z[2], val;
	int maxVal=1e5;

	if(argc<4)
	{
		printf("Too few arguments\n");
		return 0;
	}

	sscanf(argv[1], "%d%d%d", &N, &M, &H);
	sscanf(argv[2], "%d%d", &_0, &_1);
	sscanf(argv[3], "%d", &seed);
	if(argc>4)
		sscanf(argv[4], "%d", &maxVal);

	rng=std::mt19937(seed);

	printf("%d %d %d %d %d\n", N, M, H, _0, _1);
	for(i=0;i<_0;++i)
	{
		x[0]=getNext(1, N);
		y[0]=getNext(1, M);
		z[0]=getNext(1, H);

		x[1]=getNext(x[0], N);
		y[1]=getNext(y[0], M);
		z[1]=getNext(z[0], H);

		val=getNext(1, maxVal);

		printf("%d %d %d %d %d %d %d\n", x[0], y[0], z[0], x[1], y[1], z[1], val);
	}

	for(i=0;i<_1;++i)
	{
		x[0]=getNext(1, N);
		y[0]=getNext(1, M);
		z[0]=getNext(1, H);

		x[1]=getNext(x[0], N);
		y[1]=getNext(y[0], M);
		z[1]=getNext(z[0], H);

		printf("%d %d %d %d %d %d\n", x[0], y[0], z[0], x[1], y[1], z[1]);
	}

	return 0;
}
