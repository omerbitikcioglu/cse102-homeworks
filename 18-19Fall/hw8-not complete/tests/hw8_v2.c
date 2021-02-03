#include <stdio.h>
#include <string.h>

#define TERR_SIZE 200
#define INP_MAX_SIZE 3
#define water -1

void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp);
void find_islands(int terr[][TERR_SIZE+2], int water_level, int i, int j, int *mark, int isFirst);

int main(void)
{
    int water_lvl;
    char water_lvl_inp[INP_MAX_SIZE+1];
    int terr[TERR_SIZE+2][TERR_SIZE+2];
    int mark = -1;
    FILE *fp = fopen("input.txt","r");

    /*Gets the water level value from input.txt*/
    fgets(water_lvl_inp, INP_MAX_SIZE+1, fp);
    sscanf(water_lvl_inp, "%d", &water_lvl);

    fill_in_terr(terr, fp);
    fclose(fp);
    find_islands(terr, water_lvl, 1, 1, &mark, 1);

    mark *= -1;
    printf("Islands : %d\n", mark-1);

    return(0);
}

/*Fills the 512x512 terrain array with the values from input.txt*/
void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp)
{
    char inputs[INP_MAX_SIZE+1], c;
    int int_value, i, j, k;

    for(i=0; i<TERR_SIZE+2; ++i)
    {
        for(j=0; j<TERR_SIZE+2; ++j)
        {
            /*Frame of the terrain initialized as water*/
            if(i == 0 || i == TERR_SIZE+1 || j == 0 || j == TERR_SIZE+1)
                terr[i][j] = water;
            else
            {
                c = fgetc(fp);
                /*Ignores white spaces, newlines, tabs*/
                while(c==' ' || c=='\n' || c=='\t' || c=='\v')
                    c = fgetc(fp);
                /*Gets an int value char by char from input.txt*/
                for(k=0; c!=' ' && c!=EOF && c!='\n'; ++k)
                {
                    inputs[k]=c;
                    c = fgetc(fp);
                }
                inputs[k]='\0';

                sscanf(inputs, "%d", &int_value);
                terr[i][j] = int_value;
            }
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
                //printf("reached9, mark: %d value: %d\n",*mark+1, terr[i][j]);
                find_islands(terr, water_level, i, j+1, mark, 1);
            }
            else if(i < TERR_SIZE){
                //printf("reached10, mark: %d value: %d\n",*mark+1, terr[i][j]);
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
            if(j < TERR_SIZE){
                //printf("reached11, mark: %d value: %d\n",*mark+1, terr[i][j]);
                find_islands(terr, water_level, i, j+1, mark, 1);
            }
            else if(i < TERR_SIZE){
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















