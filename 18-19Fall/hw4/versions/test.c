#include <stdio.h>
#include <string.h>
#include <math.h>
#define LIM_NUM 100
#define LIM_POL_CH 1000

/*      Computer Programming        */
/*            ~ HW4 ~               */
/*  Written by Omer F. Bitikcioglu  */

double pol(double x, char *poly, int n);
int create_pol(char *poly);
void find_term(char *poly, char *term, int i, int *l);

int main(void)
{
    FILE *ifp, *ofp;
    double num, result;
    int count, n,i;
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
        printf("%lf-deger\n",num);
        result = pol(num,poly,n);
        fprintf(ofp,"%lf\n",result);
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
    deletes spaces, and creates a polynomial string without spaces   */
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

double pol(double x, char *poly, int n)
{
    int i,j,k,l,cn,m,ks;
    double p,coef,result=0;
    char term[n+1];

    for(i=0; *(poly+i)!='\0'; i+=l+1)
    {
        find_term(poly,term,i,&l);

        m = (int)strlen(term);
        printf("%d-m degeri\n",m);
        cn = 0;
        /*Calculates the term with double x and adds the value to the result*/
        for(j=0; j<m; ++j)
        {
            if(*(term+j)=='x')
            {
                if(j==0)
                {
                    if(*(term+1)=='^')
                    {
                        sscanf(term+2,"%lf",&p);
                        if(*poly == '-' || *(poly+i) == '-')
                            result-=pow(x,p);
                        else
                            result+=pow(x,p);
                        cn = 1;
                    }
                    else
                    {
                        if(*poly == '-' || *(poly+i) == '-')
                            result-=x;
                        else
                            result+=x;
                        cn = 1;
                    }
                }
                else
                {
                    if(*(term+j+1)=='^')
                    {
                        sscanf(term,"%lf",&coef);
                        sscanf(term+j+2,"%lf",p);
                        if(*poly == '-' || *(poly+i) == '-')
                            result-=coef*(pow(x,p));
                        else
                        {
                            result+=coef*(pow(x,p));
                            printf("%lf-arasonuc\n",result);
                        }

                        cn = 1;
                    }
                    else
                    {
                        sscanf(term,"%lf",&coef);
                        if(*poly == '-' || *(poly+i) == '-')
                            result-=coef*x;
                        else
                        {
                            result+=coef*x;
                            printf("%lf-arasonuc\n",result);
                        }

                        cn = 1;
                    }
                }
            }
        }
        if(cn!=1)
        {
            sscanf(term,"lf",&coef);
            if(*poly == '-' || *(poly+i) == '-')
                result -= coef;
            else
                result += coef;
        }
    }

    return result;
}

void find_term(char *poly, char *term, int i, int *l)
{
    int k,ch_count;

    /* Takes the term until reaches + or - sign */
    if(i==0)
    {
        if(*poly=='-')
        {
            for(*l=1; *(poly+*l)!='+' && *(poly+*l)!='-' && *(poly+*l)!='\0'; ++*l)
                *(term+*l-1)=*(poly+*l);
            *(term+*l-1)='\0';
            ch_count = strlen(term);
            for(k=0;k<ch_count;++k)
                printf("%c",*(term+k));
            printf("\n");
        }
        else
        {
            for(*l=0; *(poly+*l)!='+' && *(poly+*l)!='-' && *(poly+*l)!='\0'; ++*l)
                *(term+*l)=*(poly+*l);
            *(term+*l)='\0';
            ch_count = strlen(term);
            for(k=0;k<ch_count;++k)
                printf("%c",*(term+k));
            printf("\n");
        }
    }
    else if(*(poly+i)=='-' || *(poly+i)=='+')
    {
        for(*l=1; *(poly+i+*l)!='+' && *(poly+i+*l)!='-' && *(poly+i+*l)!='\0'; ++*l)
            *(term+*l-1)=*(poly+i+*l);
        *(term+*l-1)='\0';
        ch_count = strlen(term);
        for(k=0;k<ch_count;++k)
            printf("%c",*(term+k));
        printf("\n");
    }
    printf("%d-l degeri\n",*l);
}
