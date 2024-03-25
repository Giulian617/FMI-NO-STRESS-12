#include "testlib.h"
#include <bits/stdc++.h>

int main(int argc, char *argv[])
{
	int N, i, j, x, BLK;

    registerGen(argc, argv, 1);

    N=2000;
    BLK=500;
    std::vector<int> vals;
    printf("%d\n", N);
    for(i=0;i<N*N/BLK;++i)
		vals.push_back(rnd.next(1, N*N));
    for(i=0;i<N;++i)
	{
		for(j=0;j<N;++j)
		{
			x=rnd.any(vals);
			printf("%d", x);
			if(j+1==N)
				printf("\n");
			else
				printf(" ");
		}
	}

	return 0;
}