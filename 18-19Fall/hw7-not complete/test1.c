#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN_ID 10
#define MAX_LEN_KW 8

/*Defining a structure for gates*/
typedef struct{
    char    keyword [MAX_LEN_KW+1];
    int     data;
    gate_t  *input1, *input2;
}gate_t;

int     which_keyword   (char *keyword);
int     calc_gate       (char *keyword, int input1, int input2);
void    row_len_circ    (FILE *fp, int *row_len);
int     evaluate_circ   (int inp1, int inp2);

int main(void)
{
    FILE    *fip1,*fip2;
    char    kw[MAX_LEN_KW+1];
    char    id[MAX_LEN_ID+1];
    int     row_len = 0;

    fip1 = fopen("circuit.txt", "r+");
    row_len_circ(fip1, &row_len);


    return(0);
}

/*  Determines what is the keyword.
    0 = INPUT, 1 = AND, 2 = OR, 3 = NOT, 4 = FLIPFLOP   */
int which_keyword(char *keyword)
{
    if(strcmp(keyword,"INPUT")==0)
        return (0);
    if(strcmp(keyword,"AND")==0)
        return (1);
    if(strcmp(keyword,"OR")==0)
        return (2);
    if(strcmp(keyword,"NOT")==0)
        return (3);
    if(strcmp(keyword,"FLIPFLOP")==0)
        return (4);
}

/*Evaluates the value of the gate with reference to the keyword*/
int calc_gate(char *keyword, int input1, int input2)
{
    if(strcmp(keyword,"AND")==0)
        return (input1&&input2);
    if(strcmp(keyword,"OR")==0)
        return (input1||input2);
    if(strcmp(keyword,"NOT")==0)
        return (!input1);
    if(strcmp(keyword,"FLIPFLOP")==0)
    {
        if(input1==input2)
            return 0;
        else
            return 1;
    }
}

/*Calculates the row size of the circuit.txt*/
void row_len_circ(FILE *fp, int *row_len)
{
    int i;
    char *circ = (char *) malloc(sizeof(char));

    circ[0] = fgetc(fp);
    for(i=0; circ[i]!=EOF; ++i)
    {
        circ = (char *) realloc(circ, sizeof(circ)+1);
        circ[i+1] = fgetc(fp);

        if(circ[i+1]=='\n' || circ[i+1]==EOF)
            (*row_len)++;
    }
    free(circ);
}

/*Evaluates the circuit and returns the output value*/
int evaluate_circ(int inp1, int inp2)
{

}












