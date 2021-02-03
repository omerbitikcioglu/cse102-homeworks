#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define HOW_MANY_RANDOM 10000
#define MAX_VALUE 128

int main(void)
{
    int a, i;
    FILE *fp = fopen("input.txt","w");

    srand(time(NULL));
    a = rand()%MAX_VALUE;

    fprintf(fp, "%d\n", 0);

    for(i=0; i<HOW_MANY_RANDOM; ++i)
    {
        a = rand()%MAX_VALUE;

        fprintf(fp, "%d ", 1);
    }

}
