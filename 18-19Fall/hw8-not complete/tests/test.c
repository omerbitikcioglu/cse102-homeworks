#include <stdio.h>
#include <string.h>

#define TERR_SIZE 512
#define INP_MAX_SIZE 3
#define water -1

void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp);
void find_islands(int terr[][TERR_SIZE+2], int water_level, int i, int j, int *mark, int isFirst);

int main(void)
{
    int water_lvl;
    int terr[TERR_SIZE+2][TERR_SIZE+2];
    int mark = -1;
    FILE *fp = fopen("input.txt","r");

    /*Getting water level value and the other inputs from input.txt*/
    fscanf(fp, "%d", &water_lvl);
    fill_in_terr(terr, fp);
    fclose(fp);

    find_islands(terr, water_lvl, 1, 1, &mark, 1);

    mark *= -1; /*Gets the positive value of mark*/
    printf("Islands : %d\n", mark-1);

    return(0);
}

/*Fills the TERR_SIZExTERR_SIZE terrain array with the values from input.txt*/
void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp)
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
                fscanf(fp, "%d", &terr[i][j]);
            else
                return;
        }
    }
}

void find_islands(int terr[][TERR_SIZE+2], int water_level, int i, int j, int *mark, int isFirst)
{
    //printf("reached1, mark: %d value: %d\n",*mark+1, terr[i][j]);
    if(terr[i][j] > water_level)
    {
        terr[i][j] = *mark-1;

        if(terr[i][j+1] > water_level){
            //printf("reached3, mark: %d, value: %d\n",*mark+1, terr[i][j]);
            find_islands(terr, water_level, i, j+1, mark, 0); /*Check right*/
        }
        else if(terr[i][j+1] >= 0)
            terr[i][j+1] = water;

        if(terr[i+1][j] > water_level){
            //printf("reached4, mark: %d value: %d\n",*mark+1, terr[i][j]);
            find_islands(terr, water_level, i+1, j, mark, 0); /*Check down */
        }
        else if(terr[i+1][j] >= 0)
            terr[i+1][j] = water;

        if(terr[i][j-1] > water_level){
            //printf("reached5, mark: %d value: %d\n",*mark+1, terr[i][j]);
            find_islands(terr, water_level, i, j-1, mark, 0); /*Check left */
        }
        else if(terr[i][j-1] >= 0)
            terr[i][j-1] = water;

        if(terr[i-1][j] > water_level){
            //printf("reached6, mark: %d value: %d\n",*mark+1, terr[i][j]);
            find_islands(terr, water_level, i-1, j, mark, 0); /*Check up   */
        }
        else if(terr[i-1][j] >= 0)
            terr[i-1][j] = water;

        if(isFirst == 1)
        {
            if(j < TERR_SIZE){
                *mark -= 1;
                //printf("reached7, mark: %d value: %d\n",*mark+1, terr[i][j]);
                find_islands(terr, water_level, i, j+1, mark, 1);
            }
            else if(i < TERR_SIZE){
                *mark -= 1;
                //printf("reached8, mark: %d value: %d\n",*mark+1, terr[i][j]);
                find_islands(terr, water_level, i+1, 1, mark, 1);
            }
            return;
        }
        else
            return;
    }
    else if(terr[i][j] >= 0)
    {
        terr[i][j] = water;

        if(isFirst == 1)
        {
            if(j < TERR_SIZE)
            {
                while(terr[i][j+1] < 0 && j < TERR_SIZE)
                    j++;
                if(j < TERR_SIZE)
                    find_islands(terr, water_level, i, j+1, mark, 1);
            }
            if(i < TERR_SIZE && j == TERR_SIZE){
                find_islands(terr, water_level, i+1, 1, mark, 1);
            }
            return;
        }
        else
            return;
    }
    else
    {
        if(isFirst == 1)
        {
            if(j < TERR_SIZE)
            {
                while(terr[i][j+1] < 0 && j < TERR_SIZE)
                    j++;
                if(j < TERR_SIZE)
                    find_islands(terr, water_level, i, j+1, mark, 1);
            }
            if(i < TERR_SIZE && j == TERR_SIZE){
                //printf("reached12, mark: %d value: %d\n",*mark+1, terr[i][j]);
                find_islands(terr, water_level, i+1, 1, mark, 1);
            }
            return;
        }
        else
            return;
    }
}
/*
int how_many_islands(int terr[][TERR_SIZE+2])
{
    int i, j;

    for(i=1; i<=TERR_SIZE; ++i)
    {
        for(j=1; j<=TERR_SIZE; ++j)
        {
            if(terr[i][j] < -1)
        }
    }
}*/
