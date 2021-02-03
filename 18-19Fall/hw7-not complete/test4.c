#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN_ID 10
#define MAX_LEN_KW 8
#define MAX_LEN_LINE 228
#define MAX_LEN_INP 20

/*Defining a structure for gates*/
struct gate{
    char   id[MAX_LEN_ID+1];
    char   kw[MAX_LEN_KW+1];
    int    data;
    int    former_out;
    struct gate *input1;
    struct gate *input2;
};

int which_keyword(char *keyword);
struct gate *init_gate(char id[], int data);

int main(void)
{
    FILE *fip1 = fopen("circuit.txt","r");
    FILE *fip2 = fopen("input.txt","r");
    char circ_line[MAX_LEN_LINE+1];
    char kw[MAX_LEN_KW+1];
    char id[MAX_LEN_ID+1];
    char inputs;
    int data, flag = 0;
    struct gate* gate;

    while(!feof(fip1))
    {
        fgets(circ_line,MAX_LEN_LINE+1,fip1);
        if(flag == 0)
            kw = strtok(circ_line," ");
        else if(which_keyword(kw)==0)
        {
            /*INPUT keyword reached, initializing inputs*/
            do
            {
                id = strtok(NULL," ");
                do{
                    inputs = fgetc(fip2);
                }while(inputs==' ');

                sscanf(inputs,"%d",data);
                gate = init_gate(id, data);

            }while(id!=NULL);
        }
    }

    return (0);
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

struct gate *init_gate(char id[], int data)
{
    int i,n;

    /*Allocating memory for the new gate*/
    struct gate *new_gate = (struct gate*)malloc(sizeof(struct gate));

    strcpy(new_gate->id,id);
    new_gate->data = data;

    return new_gate;
}





