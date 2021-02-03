#include <stdio.h>

int main()
{
	int number,condition,first,second,third,fourth,fifth;
	
	/*The number must be between 23 and 98760*/
	condition=0;
	while(condition==0)
	{
		printf("Enter the number: ");
		scanf("%d", &number);
		if (number <= 23 || number >= 98760)
			printf("Not in range!\n");
		else
			condition=1;
	}
	
	printf("\n\n");
	
	/*We can find the digits using division and mod*/
	first = number % 10;
	second = (number/10)%10;
	third = (number/100)%10;
	fourth = (number/1000)%10;
	fifth = (number/10000)%10;
	
	/*Printing results*/
	printf("The fifth digit is %d\n",fifth);
	printf("The fourth digit is %d\n",fourth);
	printf("The third digit is %d\n",third);
	printf("The second digit is %d\n",second);
	printf("The first digit is %d\n\n",first);
	
}
