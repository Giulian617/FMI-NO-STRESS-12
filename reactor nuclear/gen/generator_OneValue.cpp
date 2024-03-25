#include "testlib.h"
#include <bits/stdc++.h>

int main(int argc, char *argv[])
{
	int N, i, j, x;

    registerGen(argc, argv, 1);

    sscanf(argv[1], "%d", &N);
    printf("%d\n", N);
    x=rnd.next(1, N*N);
    for(i=0;i<N;++i)
	{
		for(j=0;j<N;++j)
		{
			printf("%d", x);
			if(j+1==N)
				printf("\n");
			else
				printf(" ");
		}
	}

	return 0;
}