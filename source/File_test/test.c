#include <stdio.h>
#define NUMELEMENTS 100

int main()
{
    int elements[NUMELEMENTS];
    int idx;
    FILE *fp;

    fp = fopen("output.txt", "w");

    for(idx = 0; idx < NUMELEMENTS; idx++){
        *(elements+idx)=idx;
    }

    for(idx = 0; idx < NUMELEMENTS; idx++){
        fprintf(fp, "%d\t", elements[idx]);
    }

    fclose(fp);
    return 0;
}