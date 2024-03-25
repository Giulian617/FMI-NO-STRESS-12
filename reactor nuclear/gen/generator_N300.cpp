#include "testlib.h"
#include <bits/stdc++.h>

int main(int argc, char *argv[])
{
	int N, i, j, x;

    registerGen(argc, argv, 1);

    N=rnd.wnext(100, 300, 5);
    printf("%d\n", N);
    for(i=0;i<N;++i)
	{
		for(j=0;j<N;++j)
		{
			x=rnd.next(1, N*N);
			printf("%d", x);
			if(j+1==N)
				printf("\n");
			else
				printf(" ");
		}
	}

	return 0;
}