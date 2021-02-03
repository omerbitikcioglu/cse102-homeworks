#include <stdio.h>
#include <sys/resource.h>

#define TERR_SIZE 512
#define MAX_ISLAND 100
#define water -1
#define island -2
#define mark -3

int terr[TERR_SIZE+2][TERR_SIZE+2];

void fill_in_terr();
void find_islands(int i, int j);

int main(void)
{
	int howManyIsland, i, j, result;
	const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 16 MB
    struct rlimit rl;
    FILE *fp;

    result = getrlimit(RLIMIT_STACK, &rl);
    if ( (result == 0) && (rl.rlim_cur < kStackSize) )
    {
        rl.rlim_cur = kStackSize;
        result = setrlimit(RLIMIT_STACK, &rl);
    }

    /* Getting inputs from input.txt to terrain*/
    fill_in_terr();

    /*  Finds how many island are in the terrain,
        and marks first found pixels to keep islands' coordinates   */
    howManyIsland = 0;
    for(i=1; i<=TERR_SIZE; ++i)
    {
        for(j=1; j<=TERR_SIZE; ++j)
        {
            if( (terr[i][j] == island) && (howManyIsland < MAX_ISLAND) )
            {
                terr[i][j] = mark;
                find_islands(i, j);
                howManyIsland++;
            }
        }
    }
	/*  Filling in the output file.
		First line is count of islands,
		Rest is coordinates of them.	*/
    fp = fopen("output.txt", "w");
    fprintf(fp, "%d\n", howManyIsland);
    for(i=1; i<=TERR_SIZE; ++i)
    {
        for(j=1; j<=TERR_SIZE; ++j)
        {
            if(terr[i][j] == mark)
                fprintf(fp, "%d %d\n", i-1, j-1);
        }
    }
    fclose(fp);

    return(0);
}

/*Fills the TERR_SIZExTERR_SIZE terrain array with the values from input.txt*/
void fill_in_terr()
{
    int i, j, water_lvl;
    FILE *fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &water_lvl); /*Gets water level from input.txt*/

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
                if(terr[i][j] > water_lvl)
                    terr[i][j] = island;
                else
                    terr[i][j] = water;
            }
        }
    }
    fclose(fp);
}

void find_islands(int i, int j)
{
    /*  Just marks the first island pixel,
        ignores the rest as seeing them like water  */
    if(terr[i][j] != mark)
        terr[i][j] = water;

    /*Check right*/
    if(terr[i][j+1] == island)
        find_islands(i, j+1);

    /*Check down */
    if(terr[i+1][j] == island)
        find_islands(i+1, j);

    /*Check left */
    if(terr[i][j-1] == island)
        find_islands(i, j-1);

    /*Check up   */
    if(terr[i-1][j] == island)
        find_islands(i-1, j);
}
