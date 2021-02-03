/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

#include "hw4_io.h"
#include <stdio.h>

int read_polynomial3(double * a0, double * a1, double * a2, double * a3)
{
	double c0,c1,c2,c3;
	
	scanf("%lf %lf %lf %lf", &c0, &c1, &c2, &c3);
	
	*a0 = c0;
	*a1 = c1;
	*a2 = c2;
	*a3 = c3;
	
}

int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4)
{
	double c0,c1,c2,c3,c4;
	
	scanf("%lf %lf %lf %lf %lf", &c0, &c1, &c2, &c3, &c4);
	
	*a0 = c0;
	*a1 = c1;
	*a2 = c2;
	*a3 = c3;
	*a4 = c4;
}

void write_polynomial3(double a0, double a1, double a2, double a3)
{
	int i,pow;
	double co_efs[4];
	
	co_efs[0]=a0;
	co_efs[1]=a1;
	co_efs[2]=a2;
	co_efs[3]=a3;
	
	pow = 3;
	/*Writes the polynomial*/ 
	for(i=3; i>=0; i--, pow--)
	{
		/*Dont put + on the very first*/
		if(co_efs[i] > 0 && i != 3)
			printf("+");

		/*If coefficient is 0 then dont write it because its value is 0*/
		if(co_efs[i] != 0)
		{
			/*Dont write 1.0 or -1.0, just x^pow or -x^pow*/
			
			if(co_efs[i] != 1 && co_efs[i] != -1)
			{
				if(pow != 0 && pow != 1)
					printf("%.1fx^%d",co_efs[i],pow);
				else if(pow == 0)
					printf("%.1f",co_efs[i]*1.0);
				else if(pow == 1)
					printf("%.1fx",co_efs[i]);
			}
			else if(co_efs[i] == 1)
			{
				if(pow != 0 && pow != 1)
					printf("x^%d",pow);
				else if(pow == 0)
					printf("1");
				else if(pow == 1)
					printf("x");
			}
			else
			{
				if(pow != 0 && pow != 1)
					printf("x^%d",pow);
				else if(pow == 0)
					printf("-1");
				else if(pow == 1)
					printf("-x");
			}
		}
	
	}
	
}

/*Exactly the same as the previous function*/
void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
	int i,pow;
	double co_efs[5];
	
	co_efs[0]=a0;
	co_efs[1]=a1;
	co_efs[2]=a2;
	co_efs[3]=a3;
	co_efs[4]=a4;
	
	pow = 4;
	for(i=4; i>=0; i--, pow--)
	{
		if(co_efs[i] > 0 && i != 4)
			printf("+");

		if(co_efs[i] != 0)
		{
			if(co_efs[i] != 1 && co_efs[i] != -1)
			{
				if(pow != 0 && pow != 1)
					printf("%.1fx^%d",co_efs[i],pow);
				else if(pow == 0)
					printf("%.1f",co_efs[i]*1.0);
				else if(pow == 1)
					printf("%.1fx",co_efs[i]);
			}
			else if(co_efs[i] == 1)
			{
				if(pow != 0 && pow != 1)
					printf("x^%d",pow);
				else if(pow == 0)
					printf("1");
				else if(pow == 1)
					printf("x");
			}
			else
			{
				if(pow != 0 && pow != 1)
					printf("x^%d",pow);
				else if(pow == 0)
					printf("-1");
				else if(pow == 1)
					printf("-x");
			}
		}
	
	}

}














