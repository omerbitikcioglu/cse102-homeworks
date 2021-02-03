#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TERR_SIZE 512
#define MAX_ISLAND 100
#define water -1
#define island -2
#define checked -3

void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp, int water_level);
void find_islands(int terr[][TERR_SIZE+2], int i, int j);

int main(void)
{
    int water_lvl, i, j, k, terr[TERR_SIZE+2][TERR_SIZE+2];
    FILE *fp, *fop;

    /*Getting water level value and the other inputs from input.txt*/
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &water_lvl);
    fill_in_terr(terr, fp, water_lvl);
    fclose(fp);

    find_islands(terr, 1, 1, 'y');

    /*
    fop = fopen("output.txt", "w+");

    for(i=1, k=1; i<=TERR_SIZE && k<=mark; ++i)
    {
        for(j=1; j<=TERR_SIZE && k<=mark; ++j)
        {
            if(terr[i][j]==k-1){
                fprintf(fop, "%d %d\n", i, j);
                k++;
            }
        }
    }
    fclose(fop);*/

    return(0);
}

/*Fills the TERR_SIZExTERR_SIZE terrain array with the values from input.txt*/
void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp, int water_level)
{
    int i, j;

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

void find_islands(int terr[][TERR_SIZE+2], int i, int j)
{
    for( ; i<=TERR_SIZE; ++i)
    {
        for( ; j<TERR_SIZE; ++j)
        {
            if(terr[i][j] == island)
            {
                terr[i][j] = checked;

                if(terr[i][j+1] == island)
                    terr[i][j+1] = water;
                if(terr[i+1][j] == island)
                    terr[i+1][j] = water;
                if(terr[i][j-1] == island)
                    terr[i][j-1] = water;
                if(terr[i-1][j] == island)
                    terr[i-1][j] = water;
            }
        }
    }
}
