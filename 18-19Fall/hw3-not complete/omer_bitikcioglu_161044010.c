/*Libraries*/
#include <stdio.h>
#include <string.h>

/*Macros*/
#define input2_row_length 250
#define input2_max_rows 100
#define input1_word_length 10

int main(void)
{
	int i, j, ni, nj, k, compare;
	char word[input1_word_length], test_word[input1_word_length], input_2[input2_max_rows][input2_row_length], c;
	size_t word_size;
	FILE *fp1, *fp2, *fp3; 
	
	/*Filling into input_2 array from input2.txt*/
	fp2 = fopen("input2.txt","r");
	for(i=0; i<input2_max_rows; ++i)
	{
		for(j=0; j<input2_row_length && !feof(fp2); ++j)
		{
			c = getc(fp2);
			input_2[i][j]=c;
			
			/*End of line*/
			if(input_2[i][j]=='\n' || input_2[i][j]==' ')
				j = input2_row_length;
		}
	}
	fclose(fp2);
	
	fp1 = fopen("input1.txt","r");
	fp3 = fopen("output.txt","w");
	do{
		/*Gets the word from input1.txt*/
		fgets(word, input1_word_length, fp1);

		/*Finds the size of the word and deletes newline char*/
		word_size = strlen(word);
		if(word[word_size-1]=='\n')
		{
			word[word_size-1]='\0';
			word_size -=1;
		}
		
		/*Looks for matching first char and checks horizontal and vertical to find the word*/
		for(i=0; i<input2_max_rows; ++i)
		{
			for(j=0; j<input2_row_length ; ++j)
			{
				if(input_2[i][j]==*word)
				{
					ni = i, nj = j;
					
					/*Checking horizontal from matching char*/
					for(k=0;k<word_size;++k,++nj)
						test_word[k]=input_2[i][nj];
					test_word[word_size]='\0';
					
					if(strcmp(word,test_word)==0){
						fprintf(fp3, "%s (%d,%d) Horizontal\n",word,i+1,j+1);
					}
					else
					{
						/*Checking vertical from matching char*/
						for(k=0;k<word_size;++k,++ni)
							test_word[k]=input_2[ni][j];
						
						test_word[word_size]='\0';
		
						if(strcmp(word,test_word)==0)
							fprintf(fp3, "%s (%d,%d) Vertical\n",word,i+1,j+1);
					}
				}
				
				/*End of line*/
				if(input_2[i][j]=='\n' || input_2[i][j]==' ')
					j = input2_row_length;
			}
		}
	}while(!feof(fp1));
	
	fclose(fp1);
	fclose(fp3);
	
	return 0;
}