// Ilie "The-Winner" Dumitru
#include<bits/stdc++.h>

void result(const char* msg, float pts)
{
    printf("%f", pts);
    fprintf(stderr, "%s", msg);
	exit(0);
}

int main(int argc, char* argv[])
{
	int i;
	std::ifstream ok(argv[2]), out(argv[3]);

    int N_concurent, N_comisie;

    out>>N_concurent;
	ok>>N_comisie;

	if(N_comisie!=N_concurent)
		result("translate:wrong", 0);

    std::vector<int> v_concurent(N_concurent);
    for(i=0;i<N_concurent;++i)
		out>>v_concurent[i];
	std::vector<int> v_comisie(N_comisie);
	for(i=0;i<N_comisie;++i)
		ok>>v_comisie[i];

    std::sort(v_comisie.begin(), v_comisie.end());
    std::sort(v_concurent.begin(), v_concurent.end());

    for(i=0;i<N_comisie;++i)
		if(v_comisie[i]!=v_concurent[i])
			result("translate:wrong", 0);

	std::string str;
	if(out>>str)
		result("translate:wrong", 0);

	result("translate:success", 1);
}