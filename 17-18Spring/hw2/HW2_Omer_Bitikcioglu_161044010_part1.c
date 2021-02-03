#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char letter_grades(int);
double calculate_avarage(double,int);

int main()
{
	int student_count,condition,i,score,
	menu,selection,index_b,index_s,biggest,smallest,
	grade_a,grade_b,grade_c,grade_d,grade_f;
	
	double total,avarage;
	
	char grade;
	
	/*Generate random numbers*/
	srand(40);
	
	/*Until fulfilling the condition, loop will continue*/
	condition=0;
	while(condition==0)
	{
		/*Taking number of the students from user*/
		printf("Enter student count:");
		scanf("%d",&student_count);
		printf("\n\n");
		
		/*Number of the students must be in range of 3 to 50*/
		if(student_count>=3 && student_count<=50)
			condition=1;
		else
			printf("Not in range!\n\n");
	}
	
	/*For loop below prints student scores...
	
	At the same time we will catch the biggest and the smallest scores
	We initiate biggest as smaller than the smallest posible, 
	smallest as bigger than the biggest possible... */
	biggest = 0,smallest=100;
	
	/*How many people got which grade is 0 at the first*/
	grade_a=0,grade_b=0,grade_c=0,grade_d=0,grade_f=0;
	
	/*The loop is also summing up the values to calculate avarage
	Total is 0 at first*/
	total=0;
	
	for(i=1;i<=student_count;i+=1)
	{
		/*Take only the range of 0 to 100*/
		score = rand()%101;
		
		/*Sum up the scores*/
		total += score;
		
		/*Printing scores*/
		printf("%4d ",score);
		/*Goes to under line in every 10 numbers*/
		if(i%10==0)
			printf("\n");
		
		/*Finding the highest score*/
		if (score > biggest)
		{
			biggest = score;
			index_b = i;
		}
		/*Finding the smallest score*/
		if (score < smallest)
		{
			smallest = score;
			index_s = i;
		}
		
		/*We're looking for how many people get A,B,C,D or F*/
		grade = letter_grades(score);
		switch(grade)
		{
			case 'A' :	grade_a+=1;
						break;
			case 'B' :	grade_b+=1;
						break;
			case 'C' :	grade_c+=1;
						break;
			case 'D' :	grade_d+=1;
						break;
			case 'F' :	grade_f+=1;
						break;
		}
		
	}
	
	/*Calculate avarage of the scores*/
	avarage = calculate_avarage(total,student_count);

	/*Shows menu until -1 value entered*/
	menu=0;
	while (menu==0)
	{
		printf("\n---------------------------------------------------");
		printf("\nStudent Score Calculator Menu for %d Student\n\n",student_count);
		
		printf("1) Most Successful Student\n");
		printf("2) Most Unsuccessful Student\n");
		printf("3) Letter Grade Statistics\n");
		printf("4) Calculate Average\n");
		printf("5) Show All Data\n");
		
		printf("                         Make Selection: ");
		scanf("%d",&selection);
		printf("\n");
		
		switch(selection)
		{
			/*Prints most successful score and its index*/
			case 1 :	printf("Most Successful student:\n");
						printf("Index: %d\n",index_b);
						printf("Score: %d\n",biggest);
						printf("Letter grade: %c\n",letter_grades(biggest));
						break;
			
			/*Prints most unsuccessful score and its index*/
			case 2 :	printf("Most Unsuccessful student:\n");
						printf("Index: %d\n",index_s);
						printf("Score: %d\n",smallest);
						printf("Letter grade: %c\n",letter_grades(smallest));
						break;
			
			/*How many student got which letter grade*/
			case 3 :	printf("%d student got letter grade 'A'\n",grade_a);
						printf("%d student got letter grade 'B'\n",grade_b);
						printf("%d student got letter grade 'C'\n",grade_c);
						printf("%d student got letter grade 'D'\n",grade_d);
						printf("%d student got letter grade 'F'\n",grade_f);
						break;
			
			/*Prints avarage of scores*/
			case 4 :	printf("The avarage score of %d student is %.2f",student_count,avarage);
						break;
			
			/*Shows every data*/
			case 5 :	printf("Most Successful student:\n");
						printf("Index: %d\n",index_b);
						printf("Score: %d\n",biggest);
						printf("Letter grade: %c\n",letter_grades(biggest));
						
						printf("\n");
						
						printf("Most Unsuccessful student:\n");
						printf("Index: %d\n",index_s);
						printf("Score: %d\n",smallest);
						printf("Letter grade: %c\n",letter_grades(smallest));
						
						printf("\n");
						
						printf("%d student got letter grade 'A'\n",grade_a);
						printf("%d student got letter grade 'B'\n",grade_b);
						printf("%d student got letter grade 'C'\n",grade_c);
						printf("%d student got letter grade 'D'\n",grade_d);
						printf("%d student got letter grade 'F'\n",grade_f);
						
						printf("\n");
						
						printf("The avarage score of %d student is %.2f\n",student_count,avarage);
						break;
			
			/*If -1 entered, loop will break and menu won't be shown*/
			case -1 :	menu = 1;
						break;
			
			/*If anything that is not in range entered, program warns user*/
			default :	printf("False Selection!!!\n");
						break;
		}
	}
	
	return 0;
}

/*Determines which score belongs to which letter grade*/
char letter_grades(int score)
{
	char grade;
	
	if (score < 60)
		grade = 'F';
	else if (score < 70)
		grade = 'D';
	else if (score < 80)
		grade = 'C';
	else if (score < 90)
		grade = 'B';
	else
		grade = 'A';
	
	return grade;
}

/*Calculates avarage of a series*/
double calculate_avarage(double total,int n)
{
	double avarage;
	
	avarage = total / (double)n;
	
	return avarage;
}

