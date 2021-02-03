#include <stdio.h>

#define TERR_SIZE 100
#define MAX_ISLAND 100
#define water 'w'
#define island 'i'
#define mark 'm'

void fill_in_terr(char terr[][TERR_SIZE]);
void find_islands(char terr[][TERR_SIZE], int i, int j);

int main(void)
{
	int howManyIsland, i, j;
	char terr[TERR_SIZE][TERR_SIZE];
	FILE *fp;

    fill_in_terr(terr);

    /*  Finds how many island are in the terrain,
        and marks first found pixels to keep islands' coordinates   */
    howManyIsland = 0;
    for(i=0; i<TERR_SIZE; ++i)
    {
        for(j=0; j<TERR_SIZE; ++j)
        {
            if( (terr[i][j] == island) && (howManyIsland < MAX_ISLAND) )
            {
                terr[i][j] = mark;
                howManyIsland++;
                find_islands(terr, i, j);
            }
        }
    }
	/*  Filling in the output file. First line is the count of islands, the rest is coordinates of them.    */
    fp = fopen("output.txt", "w");
    fprintf(fp, "%d\n", howManyIsland);
    for(i=0; i<TERR_SIZE; ++i)
    {
        for(j=0; j<TERR_SIZE; ++j)
        {
            if(terr[i][j] == mark)
                fprintf(fp, "%d %d\n", i, j);
        }
    }
    fclose(fp);

    return(0);
}

/*  Fills the TERR_SIZExTERR_SIZE terrain array */
void fill_in_terr(char terr[][TERR_SIZE])
{
    int i, j, water_lvl, inp_val;
    FILE *fp = fopen("input.txt", "r");

    fscanf(fp, "%d", &water_lvl);

    for(i=0; i<TERR_SIZE; ++i)
    {
        for(j=0; j<TERR_SIZE; ++j)
        {
            if(!feof(fp))
            {
                fscanf(fp, "%d", &inp_val);
                if(inp_val > water_lvl)
                    terr[i][j] = island;
                else
                    terr[i][j] = water;
            }
        }
    }
    fclose(fp);
}

void find_islands(char terr[][TERR_SIZE], int i, int j)
{
    /*  If the function isn't called from main,
        ignores the pixel as seeing it like water.  */
    if(terr[i][j] != mark)
        terr[i][j] = water;

    /*  Checks right    */
    if( (j+1 < TERR_SIZE) && (terr[i][j+1] == island) )
        find_islands(terr, i, j+1);

    /*  Checks below    */
    if( (i+1 < TERR_SIZE) && (terr[i+1][j] == island) )
        find_islands(terr, i+1, j);

    /*  Checks left     */
    if( (j-1 < TERR_SIZE) && (terr[i][j-1] == island) )
        find_islands(terr, i, j-1);

    /*  Checks above    */
    if( (i-1 < TERR_SIZE) && (terr[i-1][j] == island) )
        find_islands(terr, i-1, j);
}
