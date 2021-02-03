#include <stdio.h>
#include <string.h>

#define TERR_SIZE 200
#define MAX_ISLAND 100
#define water -1
#define island -2

void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp, int water_level);
void find_islands(int terr[][TERR_SIZE+2], int i, int j, int *mark, int isFirst);

int main(void)
{
    int water_lvl, mark, i, j, k, terr[TERR_SIZE+2][TERR_SIZE+2];
    FILE *fp, *fop;

    /*Getting water level value and the other inputs from input.txt*/
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &water_lvl);
    fill_in_terr(terr, fp, water_lvl);
    fclose(fp);

    mark = 0;
    find_islands(terr, 1, 1, &mark, 1);

    fop = fopen("output.txt", "w+");
    fprintf(fop, "%d\n", mark);
    for(i=1, k=1; i<=TERR_SIZE; ++i)
    {
        for(j=1; j<=TERR_SIZE; ++j)
        {
            if(terr[i][j]==k-1){
                fprintf(fop, "%d %d\n", i, j);
                k++;
            }
        }
    }
    fclose(fop);

    return(0);
}

/*Fills the TERR_SIZExTERR_SIZE terrain array with the values from input.txt*/
void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp, int water_level)
{
    int i, j, mark = 0;

    for(i=0; i<TERR_SIZE+2; ++i)
    {
        for(j=0; j<TERR_SIZE+2; ++j)
        {
            /*Frame of the terrain initialized as water*/
            if(i == 0 || i == TERR_SIZE+1 || j == 0 || j == TERR_SIZE+1)
                terr[i][j] = water;
            else if(!feof(fp))
            {
                fscanf(fp, "%d", &terr[i][j]);
                if(terr[i][j] > water_level)
                    terr[i][j] = island;
                else
                    terr[i][j] = water;
            }
        }
    }
}

void find_islands(int terr[][TERR_SIZE+2], int i, int j, int *mark, int isFirst)
{
    if(terr[i][j] == island) /*If it is a island*/
    {
        /*  Just marks the first island pixel,
            ignores the rest as seeing them like water  */
        if(isFirst == 1)
            terr[i][j] = *mark;
        else
            terr[i][j] = water;

        /*Check right*/
        if(terr[i][j+1] == island)
            find_islands(terr, i, j+1, mark, 0);

        /*Check down */
        if(terr[i+1][j] == island)
            find_islands(terr, i+1, j, mark, 0);

        /*Check left */
        if(terr[i][j-1] == island)
            find_islands(terr, i, j-1, mark, 0);

        /*Check up   */
        if(terr[i-1][j] == island)
            find_islands(terr, i-1, j, mark, 0);

        /*If all around the pixel is checked*/
        if(isFirst == 1)
        {
            if(*mark < MAX_ISLAND)
            {
                *mark += 1;
                for(; i <= TERR_SIZE; ++i, j=1)
                {
                    for(; j <= TERR_SIZE; ++j)
                    {
                        if(terr[i][j+1] == island){
                            find_islands(terr, i, j+1, mark, 1);
                            return;
                        }
                    }
                }
                return;
            }
            else /*If there is more island than MAX_ISLAND in input, counts them as water*/
            {
                for(; i <= TERR_SIZE; ++i, j=1)
                {
                    for(; j <= TERR_SIZE; ++j)
                        terr[i][j+1] = water;
                }
                return;
            }
        }
        else
            return;
    }
    else if(terr[i][j] == water) /*If it is a water*/
    {
        /*Search for an island*/
        for(; i <= TERR_SIZE; ++i, j=1)
        {
            for(; j <= TERR_SIZE; ++j)
            {
                if(terr[i][j+1] == island){
                    find_islands(terr, i, j+1, mark, 1);
                    return;
                }
            }
        }
        return;
    }
    return;
}
