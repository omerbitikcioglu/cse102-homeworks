
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
