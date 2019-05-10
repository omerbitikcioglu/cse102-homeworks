#include <stdio.h>

#define p1 0.5
#define p2 20
#define chunkSize 100
#define numSize 1000

int check_condition(double a, double b, double n);

int main(){
	
	int chunk_starts[chunkSize], chunk_sizes[chunkSize], i, j, z, chunk_size, arr_size, test, chunk; 
	double nums[numSize], chunk_avgs[chunkSize], total, avg, new_avg, temp;
	
	/*Get inputs from the input file to an array*/
	FILE *fp;
	fp = fopen("input.txt", "r");

	for(i=0; !feof(fp) && i<numSize; ++i)
	{
		fscanf(fp, "%lf", &nums[i]);		
	}
	
	fclose(fp);
	
	arr_size = i+1;
	
	/*Finding chunks*/
	total=0, chunk_size=0, chunk=0;
	for(i=0; i<arr_size; ++i)
	{
		total += nums[i];
		++chunk_size; 
		avg = total/(double)chunk_size;
		
		if((i+1)<arr_size)
		{
			new_avg = (total+nums[i+1])/(chunk_size+1);
			
			test = check_condition(avg,new_avg,nums[i+1]);
			
			if(test){
				/*Do nothing*/
			} 
			else if(chunk<chunkSize)
			{
				chunk_starts[chunk]=i-(chunk_size-1);
				chunk_sizes[chunk]=chunk_size;
				chunk_avgs[chunk]=avg;
				++chunk;
				total = 0;
				chunk_size = 0;
			}	
		}
	}
	
	/*Sorting chunks in ascending order*/
	for (i=0; i < (chunk-1); ++i)
	{
		for (j=0; j < chunk-1-i; ++j )
		{
			if (chunk_avgs[j] > chunk_avgs[j+1])
			{
				temp = chunk_avgs[j+1];
				chunk_avgs[j+1] = chunk_avgs[j];
				chunk_avgs[j] = temp;
				
				temp = chunk_starts[j+1];
				chunk_starts[j+1] = chunk_starts[j];
				chunk_starts[j] = temp;
				
				temp = chunk_sizes[j+1];
				chunk_sizes[j+1] = chunk_sizes[j];
				chunk_sizes[j] = temp;
			}
      }
	}
	
	/*Writing chunks to the output file*/
	fp = fopen("output.txt", "w+");
	
	for(i=0; i<chunk; ++i)
	{
		z = chunk_starts[i];
		for(j=0; j<chunk_sizes[i]; ++j, ++z)
		{
			fprintf(fp, "%lf ", nums[z]);
		}
		fprintf(fp, "%s", "\n");
	}
	
	fclose(fp);
}

/*Checks if the given n is suitable for the current chunk or not*/
int check_condition(double a, double b, double n)
{
	if (b > a*(1+p1) || b < a*(1-p1) || a > n*p2 || a < n/p2)
	{
		/*Fail*/
		return 0;
	}
	else
	{
		/*Satisfied*/
		return 1;
	}
}