#include <stdio.h>
#include <string.h>
#include <math.h>
#define LIM_NUM 100
#define LIM_POL_CH 1000

/*      Computer Programming        */
/*            ~ HW4 ~               */
/*  Written by Omer F. Bitikcioglu  */

int create_pol(char *poly);
double calculate_pol(double x, char *poly, int n);
int find_term(char *poly, char *term, int i);
double calculate_term(double x, char *term, char *poly, int i);

int main(void)
{
    FILE *ifp, *ofp;
    double num, result;
    int count, n;
    char poly[LIM_POL_CH+1];

    ifp = fopen("values.txt", "r");
    ofp = fopen("evaluations.txt", "w+");
    n = create_pol(poly);

    /*  Takes a value from the input file, and
        calculates the result of the polynomial, and
        writes it to the output file.    */
    count = 0;
    while(fscanf(ifp,"%lf",&num)==1 && count!=LIM_NUM)
    {
        result = calculate_pol(num,poly,n);
        fprintf(ofp,"%.2lf\n",result);
        ++count;
    }
    fclose(ifp);
    fclose(ofp);

    return 0;
}

int create_pol(char *poly)
{
    FILE *fp;
    char c;
    int i,j;

    fp = fopen("polynomial.txt","r");
    /*  This part gets chars from our polynomial input file,
    deletes spaces, and creates a polynomial string without spaces
        'T' is a random value       */
    c = 'T';
    for(i=0,j=0; c != EOF && j<LIM_POL_CH; j++)
    {
        c = fgetc(fp);

        if(c == ' ' || c == EOF)
        {
            /*Do nothing*/
        }
        else
        {
            *(poly+i)=c;
            i++;
        }
    }
    fclose(fp);
    *(poly+i)='\0';
    /*Returns length of the polynomial*/
    return i;
}

double calculate_pol(double x, char *poly, int n)
{
    int i,found;
    double term_result,result=0;
    char term[n+1];

    for(i=0; *(poly+i)!='\0'; i++)
    {
        /*Take a term from polynomial*/
        found = find_term(poly,term,i);

        /*If term is found then calculate the term value*/
        if(found==1)
        {
            term_result = calculate_term(x, term, poly, i);
            result += term_result;
        }
    }
    /*Returns the value of whole polynomial*/
    return result;
}

int find_term(char *poly, char *term, int i)
{
    int k,j,found=0;

    /* Takes the term until reaches + or - or \0 char */
    if(i==0)
    {
        if(*poly=='-')
        {
            for(j=1; *(poly+j)!='+' && *(poly+j)!='-' && *(poly+j)!='\0'; ++j)
                *(term+j-1)=*(poly+j);
            *(term+j-1)='\0';
        }
        else
        {
            for(j=0; *(poly+j)!='+' && *(poly+j)!='-' && *(poly+j)!='\0'; ++j)
                *(term+j)=*(poly+j);
            *(term+j)='\0';
        }
        found=1;
    }
    else if(*(poly+i)=='-' || *(poly+i)=='+')
    {
        for(j=1; *(poly+i+j)!='+' && *(poly+i+j)!='-' && *(poly+i+j)!='\0'; ++j)
            *(term+j-1)=*(poly+i+j);
        *(term+j-1)='\0';
        found=1;
    }
    return found;
}

/*Calculates the term with double x and returns the result*/
double calculate_term(double x, char *term, char *poly, int i)
{
    int j,m,x_included;
    double p,coef,term_result=0;
    char ch_x,ch_p;

    m = (int)strlen(term);
    x_included = 0;
    for(j=0; j<m; ++j)
    {
        /*If x is found*/
        if(*(term+j)=='x')
        {
            /*If x is the first element of the term*/
            if(j==0)
            {
                /*If x has a power different from 1*/
                if(*(term+1)=='^')
                {
                    sscanf(term,"%c%c%lf",&ch_x,&ch_p,&p);
                    if(*poly == '-' || *(poly+i) == '-')
                        term_result-=pow(x,p);
                    else
                        term_result+=pow(x,p);
                    x_included = 1;
                }
                /*If x's power is 1*/
                else
                {
                    if(*poly == '-' || *(poly+i) == '-')
                        term_result-=x;
                    else
                        term_result+=x;
                    x_included = 1;
                }
            }
            /*If x has a coefficient*/
            else
            {
                if(*(term+j+1)=='^')
                {
                    sscanf(term,"%lf%c%c%lf",&coef,&ch_x,&ch_p,&p);
                    if((i==0 && *poly == '-') || (i!=0 && *(poly+i) == '-'))
                        term_result-=coef*(pow(x,p));
                    else
                        term_result+=coef*(pow(x,p));
                    x_included = 1;
                }
                else
                {
                    sscanf(term,"%lf%c",&coef,&ch_x);
                    if((i==0 && *poly == '-') || (i!=0 && *(poly+i) == '-'))
                        term_result-=coef*x;
                    else
                        term_result+=coef*x;
                    x_included = 1;
                }
            }
        }
    }
    /*If there is no x in the term (constant)*/
    if(x_included==0)
    {
        sscanf(term,"%lf",&coef);
        if((i==0 && *poly == '-') || (i!=0 && *(poly+i) == '-'))
            term_result -= coef;
        else
            term_result += coef;
    }
    return term_result;
}
