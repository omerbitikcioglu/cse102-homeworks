#include <stdio.h>
#include <string.h>
#define MAX_INP_CH 100

double totalCost(char *cmpName, char *partStr, char *inpStr, int i, int n, int flag, int coef, double total);
int dltSpaces(char *myStr, int i, int j);

int main(void)
{
    char    cmpName[MAX_INP_CH+2], inpStr[MAX_INP_CH+2], partStr[MAX_INP_CH+1];
    int     i, n, flag;
    double  total=0;

    printf("Name the object:\n");
    fgets(cmpName,MAX_INP_CH+2,stdin);
    /*  MAX_INP_CH+2 -- +2 opens space for \n and \0 chars
        when we press enter in console it creates \n char   */

    n = (int)strlen(cmpName);
    cmpName[--n]='\0';
    /*This deletes the \n char from end of our string*/

    total = totalCost(cmpName, partStr, inpStr, 0, n, -1, 0, 0);
    printf("Total cost of %s is %lf",cmpName,total);

    return (0);
}

/*At first call --> i = 0, flag = -1, coef = 0, total = 0*/
double totalCost(char *cmpName, char *partStr, char *inpStr, int i, int n, int flag, int coef, double total)
{
    if(flag==-1)/*First touch to the function*/
        printf("Define %s?:\n",cmpName);

    if(flag<=0)
    {
        if(flag==0)
        {
            printf("Define %s in %s?:\n",partStr,cmpName);
            n = strlen(partStr);
            for(i=0;i<n;++i)
                cmpName[i]=partStr[i];
            cmpName[i]='\0';
        }

        /*Getting input string from the command line*/
        fgets(inpStr,MAX_INP_CH+2,stdin);
        n = (int)strlen(inpStr);
        inpStr[--n]='\0';

        /*Is it part name or price?*/
        for(i=0;i<n;++i)
        {
            if(inpStr[i]==' ')
            {
                flag=1; /*This string consists of parts of the compound*/
                i=n;
            }
        }
        if(flag!=1)
        {
            sscanf(inpStr,"%lf",&total);
            return total;
        }
    }

    if(flag>=1)
    {
        dltSpaces(inpStr, 0,0);
        if(flag==1)
        {
            /*Parsing the term as coef and its name*/
            partStr = strtok(inpStr," ");
            sscanf(partStr,"%d",&coef);
            partStr = strtok(NULL," ");

            total = (double)coef*totalCost(cmpName, partStr, inpStr, 0, n, 0, 0, 0);
            flag=2;
        }
        if(flag==2)
        {
            partStr = strtok(NULL," ");

            if(partStr!=NULL)
            {
                sscanf(partStr,"%d",&coef);
                partStr = strtok(NULL," ");

                total += (double)coef*totalCost(cmpName, partStr, inpStr, 0, n, 0, 0, 0);
            }
            else
                return total;
        }
    }
}

/*Deletes extra spaces between tokens*/
int dltSpaces(char *myStr, int i, int j)
{
    if((myStr[i]==' ' && myStr[i+1]==' ') || (myStr[i]==' ' && myStr[i-1]==' '))
    {
        for(j=i; myStr[j+1]!='\0'; ++j)
            myStr[j]=myStr[j+1];
        myStr[j]='\0';

        return dltSpaces(myStr, i+1, 0);
    }
    if(myStr[i]!='\0')
        return dltSpaces(myStr, i+1, 0);
    return (0);
}







