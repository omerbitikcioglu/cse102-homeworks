#include <stdio.h>
#include <string.h>

#define TERR_SIZE 512
#define INP_MAX_SIZE 3
#define water -1

void fill_in_terr(int terr[][TERR_SIZE+2], FILE *fp);

int main(void)
{
    int water_lvl;
    char water_lvl_inp[INP_MAX_SIZE+1];
    int terr[TERR_SIZE+2][TERR_SIZE+2];
    FILE *fp = fopen("input.txt","r");

    /*Gets the water level value from input.txt*/
    fgets(water_lvl_inp, INP_MAX_SIZE+1, fp);
    sscanf(water_lvl_inp, "%d", &water_lvl);

    fill_in_terr(terr, fp);

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

void find_islands(int terr[][TERR_SIZE+2], int water_level, int i, int j, int mark, int isfirst)
{
    while(i<=TERR_SIZE)
    {
        while(j<=TERR_SIZE)
        {
            if(terr[i][j] > water_level)
            {
                terr[i][j] = mark;

                if(terr[i][j+1] >= 0)
                    find_islands(terr, water_level, i, j+1, mark); /*Check right*/
                if(terr[i+1][j] >= 0)
                    find_islands(terr, water_level, i+1, j, mark); /*Check down */
                if(terr[i][j-1] >= 0)
                    find_islands(terr, water_level, i, j-1, mark); /*Check left */
                if(terr[i-1][j] >= 0)
                    find_islands(terr, water_level, i-1, j, mark); /*Check up   */

                return;
            }
            else if(terr[i][j] >= 0)
            {
                terr[i][j] = water;
                return;
            }
            else
            {
                return;
            }

        }
    }
}

















