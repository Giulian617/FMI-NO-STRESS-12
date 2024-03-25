#include "testlib.h"
#include <bits/stdc++.h>

int main(int argc, char *argv[])
{
	int N, i, j, x;

    registerGen(argc, argv, 1);

    N=2000;
    std::vector<int> vals;
    printf("%d\n", N);
    for(i=0;i<N;++i)
	{
		vals=rnd.perm(N);
		for(j=0;j<N;++j)
		{
			x=vals[j];
			printf("%d", x+1);
			if(j+1==N)
				printf("\n");
			else
				printf(" ");
		}
	}

	return 0;
}