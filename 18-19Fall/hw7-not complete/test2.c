#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN_ID 10
#define MAX_LEN_KW 8
#define MAX_LEN_LINE 228
#define MAX_LEN_INP 20

void init_circuit(FILE *fp, char circ_array[][MAX_LEN_LINE+1]);

/*Defining a structure for gates*/
struct gate{
    char   id[MAX_LEN_ID+1];
    int    data;
    int    former_out;
    struct gate *input1;
    struct gate *input2;
};

int main(void)
{
    FILE *fip1 = fopen("circuit.txt", "r");
    char kw         [MAX_LEN_KW+1];
    char id         [MAX_LEN_ID+1];
    char circ_array [2][MAX_LEN_LINE+1];
    int inputs      [MAX_LEN_INP];

    /*init_circuit(fip1,circ_array);*/

    /*Gets a line of circuit.txt
    fgets(line, MAX_LEN_LINE+1, fip1);

    Takes keyword
    strcpy(kw, strtok(line," "));

    if(which_keyword(kw)==0)
    {
        strcpy(id, strtok(NULL," "));
    }


    while(id != NULL)
    {

    }
        */
    return(0);
}
/*
void init_circuit(FILE *fp, char circ_array[][MAX_LEN_LINE+1])
{
    int i, j;
    char c, *ptr;

    for(i=1, j=0; c!=EOF; ++i)
    {
        c = fgetc(fp);

        circ_array[j][i-1] = c;
        printf("%c",circ_array[j][i-1]);

        if(c=='\n'){
            j++;

            ptr =(char *)malloc((MAX_LEN_LINE+1)*sizeof(char));
            circ_array+

            i=0;

        }
    }

}
*/
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

/*Evaluates the circuit and returns the output value
int evaluate_circ(FILE *fp, char circ_array[][])
{



}*/

struct gate *init_gate(char id[], int data)
{
    int i,n;

    /*Allocating memory for the new gate*/
    struct gate *new_gate = (struct gate*)malloc(sizeof(struct gate));

    /*Copying id string to gate struct*/
    n = strlen(id);
    for(i=0; i<n; ++i)
        new_gate->id[i] = id[i];
    new_gate->id[n]='\0';

    new_gate->data = data;

    return new_gate;
}












