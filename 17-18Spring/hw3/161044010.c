#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min, int max);
void horseRacingGame();
void countOccurrence();
void triangleOfSequences();

int main()
{
	/*Generates random numbers*/
	srand(time(NULL));
	
	/*Calls menu*/
	menu();
	
	return 0;
}

void menu()
{
	int choice,condition;
	
	/*The menu will be shown until 0 is entered*/
	condition = 0;
	do
	{
		/*Printing menu*/
		printf("1.Horse Racing Game\n");
		printf("2.Occurrence Counter\n");
		printf("3.Triangle of Sequences\n");
		printf("0.Exit\n");
		printf("              Your selection: ");
		scanf("%d",&choice);
		printf("\n");
		
		/*Menu choices*/
		switch(choice)
		{
			case 1 :	horseRacingGame();
						break;
		
			case 2 :	countOccurrence();
						break;
		
			case 3 :	triangleOfSequences();
						break;
		
			case 0 :	condition = 1;
						break;
		
			default :	printf("Invalid choice!\n\n");
						break;
		}
	}
	while(condition == 0);
}

int getInt(int mini, int maxi)
{
	int input,condition;
	
	/*The function will ask for input in range of maxi and mini*/
	condition = 0;
	while(condition == 0)
	{
		scanf("%d",&input);
	
		/*Checking the range*/
		if (input >= mini && input <= maxi)
			condition = 1;
		else
			printf("Not in range !\n");
	}
	
	return input;
}

/*Assigns a random value to num and checks if it's in range. 
Modulus operator guarantee that num will be less or equal to max.
Also checks whether it is bigger than min or not*/
int numberGeneratorBetweenRange(int min, int max)
{
	int num;

	do
		num = rand()%(max+1);
	while(num < min);
	
	return num;
}

void horseRacingGame()
{
	int i,j,numofHorses,horseNum,condition,winnerTime,winner,otherWinner,timeOfHorse;
	
	/*Number of horses is randomly generated*/ 
	numofHorses = numberGeneratorBetweenRange(3,5);
	
	printf("Number of Horse : %d\n",numofHorses);
	
	/*User picking a horse number*/
	printf("Horse Number: ");
	horseNum = getInt(1,numofHorses);
	
	printf("Racing starts...\n");
	
	/*This loop gets a random running time for each horse, prints the and checks who is the winner*/
	winnerTime = 21;
	for(i=1;i<=numofHorses;i++)
	{
		/*Generating random running time*/
		timeOfHorse = numberGeneratorBetweenRange(10,20);
		
		printf("Horse %d: ",i);
		
		/*Printing horse's running time*/
		for(j=0;j<timeOfHorse;j++)
			printf("-");
		
		printf("\n");
		
		/*Checking who is the winner*/
		if (timeOfHorse < winnerTime)
		{	
			winnerTime = timeOfHorse;
			winner=i;
			otherWinner = 0;
		}
		else if (timeOfHorse == winnerTime && horseNum == i)
			otherWinner = 1;
	}
	
	/*Prints that user won or lose*/
	if(winner == horseNum || otherWinner != 0)
		printf("You win! Winner is Horse %d\n",horseNum);
	else
		printf("You lose! Winner is Horse %d\n",winner);
}

void countOccurrence()
{
	int i,n,search_num,big_num,digit,check_num,counter,temp;
	
	/*Taking inputs from user*/
	printf("Big Number: ");
	scanf("%d",&big_num);
	
	printf("Search Number: ");
	scanf("%d",&search_num);
	
	/*The loop will control big number's digit number and checks every digit if it equals to search number. 
	And then it divides big number to the left and search again and again until big number goes 0*/
	counter = 0;
	do
	{
		/*Assigning big number to a temporary variable to calculate digit number*/
		temp = big_num;
		digit = 0;
		while(temp != 0)
		{
			temp /= 10;
			digit +=1;
		}
		/*Controls if a portion of the big num which we called here as check num, match with search num*/
		n = 10;
		for(i=1;i<=digit;i++)
		{
			check_num = big_num % n;
			
			/*Avoid to take 00 as equals to 0*/ 
			if(i<2 || check_num != (big_num%(n/10)))
			{
				if (check_num == search_num)
					counter +=1;
			}	
			n *= 10;
		}
		/*To control left parts of the big num, we divide into 10 and integer gets rid of the fraction*/
		big_num /= 10;
	}
	while(big_num != 0);
	
	printf("Occurrence: %d\n",counter);
	
}

void triangleOfSequences()
{
	int i,j,k,num;
	
	num = numberGeneratorBetweenRange(2, 10);
	
	/*i means the line number*/
	for(i=1;i<=num;i++)
	{
		k = i;
		for(j=1;j<=i;j++,k+=i)
		{
			printf("%d ",k);
		}
		
		printf("\n");
	}
	printf("\n");
}