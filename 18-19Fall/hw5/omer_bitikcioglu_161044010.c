#include <stdio.h>
#include <string.h>
#define MAX_INP_CH 250
#define MAX_NODE_CH 10

int fOutput(int hyphen, int i, int j, FILE* ofp, char node[], char inpStr[], int flag2);
int deleteSpaces(char inpStr[], size_t n, int i, int j);

int main(void)
{
    int i=0,j=0,hyphen=0;
    char node[MAX_NODE_CH+1],inpStr[MAX_INP_CH+1];
    size_t n;
    FILE* ifp = fopen("input.txt","r");
    FILE* ofp = fopen("output.txt","w+");

    /*I get the input text into a string*/
    fgets(inpStr,MAX_INP_CH+1,ifp);
    fclose(ifp);

    n = strlen(inpStr);
    deleteSpaces(inpStr,n,i,j);

    /*Calls the recursive function*/
    fOutput(hyphen,i,j,ofp,node,inpStr,0);
    fclose(ofp);

    return(0);
}

/*Parses nodes and writes them into the output file*/
int fOutput(int hyphen, int i, int j, FILE* ofp, char node[], char inpStr[], int flag2)
{
    int k,flag=0;
    size_t n;

    /*While '(' char increases the amount of hyphen, ')' decreases*/
    if(inpStr[i]=='(')
        return fOutput(hyphen+1,i+1,j,ofp,node,inpStr,flag2);
    if(inpStr[i]==')')
    {
        if(inpStr[i-1]==')')
            return fOutput(hyphen-1,i+1,j,ofp,node,inpStr,flag2);
        else
        {
            node[j]='\0';
            n = (int)strlen(node);
            /*Checks if there is a char different from space*/
            for(k=0;k<n;k++)
            {
                if(node[k]!=' ')
                    flag=1;
            }
            /*Controls if the node is empty or not and writes the node into the output file*/
            if(n!=0 && flag==1)
            {
                /*flag2 checks if a node was written before*/
                if(flag2==1)
                    fprintf(ofp,"\n");
                for(k=0;k<hyphen;k++)
                    fprintf(ofp,"-");
                fputs(node,ofp);
            }
            return fOutput(hyphen-1,i+1,0,ofp,node,inpStr,1);
        }
    }
    if(inpStr[i]==',')
    {
        if(inpStr[i-1]==')')
            return fOutput(hyphen,i+1,j,ofp,node,inpStr,flag2);
        else
        {
            node[j]='\0';
            n = (int)strlen(node);
            for(k=0;k<n;k++)
            {
                if(node[k]!=' ')
                    flag=1;
            }
            if(n!=0 && flag==1)
            {
                if(flag2==1)
                    fprintf(ofp,"\n");
                for(k=0;k<hyphen;k++)
                    fprintf(ofp,"-");
                fputs(node,ofp);
            }
            return fOutput(hyphen,i+1,0,ofp,node,inpStr,1);
        }
    }
    if(inpStr[i]=='\0')
    {
        if(j!=0)
        {
            node[j]='\0';

            if(flag2==1)
                fprintf(ofp,"\n");
            for(k=0;k<hyphen;k++)
                fprintf(ofp,"-");
            fputs(node,ofp);

            return 0;
        }
        return 0;
    }
    /*Assigns chars to our nodes*/
    if(j<MAX_NODE_CH)
    {
        node[j]=inpStr[i];
        return fOutput(hyphen,i+1,j+1,ofp,node,inpStr,flag2);
    }
    return fOutput(hyphen,i+1,j,ofp,node,inpStr,flag2);
}

/*Deletes spaces at the beginning and end of the string*/
int deleteSpaces(char inpStr[], size_t n, int i, int j)
{
    /*Ignores the spaces at the beginning and shifts the entire input string*/
    if(inpStr[i]==' ')
    {
        for(j=0;inpStr[j+1]!='\0'; ++j)
            inpStr[j]=inpStr[j+1];
        inpStr[j]='\0';
        return deleteSpaces(inpStr,n,i,j);
    }
    /*Deletes the spaces at the end of the input string*/
    n = strlen(inpStr);
    if(inpStr[n-1]==' ')
    {
        inpStr[n-1]='\0';
        return deleteSpaces(inpStr,n-1,i,j);
    }
    return 0;
}
