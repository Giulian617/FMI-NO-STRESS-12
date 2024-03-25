// Ilie "The-Winner" Dumitru
#include<bits/stdc++.h>

std::mt19937 rng;

// [low, high]
int genNr(int low, int high)
{
	return std::uniform_int_distribution<>(low, high)(rng);
}

std::vector<int> sol;

int main(int argc, char* argv[])
{
	int seed, i, N=5, a, prev=0, opt=0;
	FILE* g=fopen((std::string(argv[1])+".in").c_str(), "w");
	FILE* f=fopen((std::string(argv[1])+".ok").c_str(), "w");

	sscanf(argv[2], "%d", &seed);
	rng=std::mt19937(seed);

	if(argc>3)
		sscanf(argv[3], "%d", &N);
	if(N==-1)
		N=genNr(100, 100000);

	if(argc>4)
		sscanf(argv[4], "%d", &opt);

	fprintf(g, "%d\n", N);
	++N;
	for(i=1;i<N;++i)
	{
		a=genNr(0, 1);
		if(a!=prev)
			sol.push_back(i);
		prev=a;
		fprintf(g, "%d%c", a, " \n"[i==N-1]);
	}
	fprintf(f, "%d\n", (int)sol.size());
	for(i=0;i<(int)sol.size();++i)
		fprintf(f, "%d%c", sol[i], " \n"[i+1==(int)sol.size()]);

	fclose(f);
	fclose(g);
	return 0;
}