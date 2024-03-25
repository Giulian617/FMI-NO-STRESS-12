// Ilie "The-Winner" Dumitru
#include<bits/stdc++.h>

std::mt19937 rng;

// [low, high]
int genNr(int low, int high)
{
	return std::uniform_int_distribution<>(low, high)(rng);
}

int main(int argc, char* argv[])
{
	int seed, i, N=7, a, b, c, ans=0;
	FILE* g=fopen((std::string(argv[1])+".in").c_str(), "w");
	FILE* f=fopen((std::string(argv[1])+".ok").c_str(), "w");

	sscanf(argv[2], "%d", &seed);
	rng=std::mt19937(seed);

	if(argc>3)
		sscanf(argv[3], "%d", &N);
	if(N==-1)
		N=genNr(100, 100000);

	fprintf(g, "%d\n", N);
	for(i=0;i<N;++i)
	{
		a=genNr(0, 24);
		b=genNr(a, 24);
		c=genNr(0, 1);
		ans+=(c+1)*(b-a);
		fprintf(g, "%d %d %d\n", a, b, c);
	}
	fprintf(f, "%d\n", ans);

	fclose(f);
	fclose(g);
	return 0;
}