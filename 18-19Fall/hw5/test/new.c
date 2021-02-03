#include <stdio.h>
#include <string.h>
#define MAX_INP_CH 250
#define MAX_NODE_CH 10

int fOutput(int hyphen, int i, int j, FILE* ofp, char node[], char inpStr[]);
int deleteSpaces(char node[], size_t n);

int main(void)
{
    int i=0,j=0,hyphen=0,r;
    size_t s;
    char node[MAX_NODE_CH+1],inpStr[MAX_INP_CH+1];
    FILE* ifp = fopen("input.txt","r");
    FILE* ofp = fopen("output.txt","w+");

    fgets(inpStr,MAX_INP_CH+1,ifp);
    fclose(ifp);

    /*Calls the recursive function*/
    r = fOutput(hyphen,i,j,ofp,node,inpStr);
    fclose(ofp);

    return(r);
}

int fOutput(int hyphen, int i, int j, FILE* ofp, char node[], char inpStr[])
{
    int k;
    size_t n;

    if(inpStr[i]=='(')
        return fOutput(hyphen+1,i+1,j,ofp,node,inpStr);
    if(inpStr[i]==')')
    {
        if(inpStr[i-1]==')')
            return fOutput(hyphen-1,i+1,j,ofp,node,inpStr);
        else
        {
            node[j]='\0';
            n = strlen(node);
            deleteSpaces(node,n);
            for(k=0;k<hyphen;k++)
                fprintf(ofp,"-");
            fputs(node,ofp);
            if(inpStr[i+1]!='\0')
                fprintf(ofp,"\n");
            return fOutput(hyphen-1,i+1,0,ofp,node,inpStr);
        }
    }
    if(inpStr[i]==',')
    {
        if(inpStr[i-1]==')')
            return fOutput(hyphen,i+1,j,ofp,node,inpStr);
        else
        {
            node[j]='\0';
            n = strlen(node);
            deleteSpaces(node,n);
            for(k=0;k<hyphen;k++)
                fprintf(ofp,"-");
            fputs(node,ofp);
            fprintf(ofp,"\n");
            return fOutput(hyphen,i+1,0,ofp,node,inpStr);
        }
    }
    if(inpStr[i]=='\0')
    {
        if(j!=0)
        {
            node[j]='\0';
            n = strlen(node);
            deleteSpaces(node,n);
            for(k=0;k<hyphen;k++)
                fprintf(ofp,"-");
            fputs(node,ofp);
            return 0;
        }
        else
            return 0;
    }
    if(hyphen==0 && inpStr[i]==' ')
        return fOutput(hyphen,i+1,j,ofp,node,inpStr);

    node[j]=inpStr[i];
    return fOutput(hyphen,i+1,j+1,ofp,node,inpStr);
}

int deleteSpaces(char node[], size_t n)
{
    if(node[n-1]==' ')
        return deleteSpaces(node,n-1);
    node[n]='\0';
    return 0;
}
