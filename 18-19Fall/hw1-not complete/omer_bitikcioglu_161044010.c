#include <stdio.h>
#define SAMPLES 10

/*Checks if the given (x,y) point is above or below the line*/
int check_sep_line(float tng, float x, float y, float x2, float y2);

int main()
{
	/*Initializing needed variables*/
	float x , y, totalx, totaly, avgx1, avgx2, avgy1, avgy2, tngCon, tngSep, midx, midy;
	int i, control, moveon, class_one_flag, class_two_flag, label;

	/*Reading samples and finding avarage point for class 1*/
	totalx=0;totaly=0;
	for(i=1; i<=SAMPLES; ++i)
	{
		scanf("%f %f",&x,&y);
		/*To find out avarage point*/
		totalx +=x;
		totaly +=y;
	}

	/*Avarage of x and y*/
	totalx /= SAMPLES;
	avgx1 = totalx;
	totaly /= SAMPLES;
	avgy1 = totaly;
	/*Now, avarage point of class1 is (avgx1,avgy1) */

	/*Reading samples and finding avarage point for class 2*/
	totalx=0;totaly=0;
	for(i=1; i<=SAMPLES; ++i)
	{
		scanf("%f %f",&x,&y);

		/*To find out avarage point*/
		totalx +=x;
		totaly +=y;
	}

	/*Avarage of x and y*/
	totalx /= SAMPLES;
	avgx2 = totalx;
	totaly /= SAMPLES;
	avgy2 = totaly;
	/*Now, avarage point of class2 is (avgx2,avgy2) */

	/*Tangent of connecting line*/
	tngCon = (avgy2-avgy1)/(avgx2-avgx1);

	/*Finding the mid point(midx,midy) of the connecting line*/
	midx = (avgx1+avgx2)/2;
	midy = (avgy1+avgy2)/2;

	/*Tangent of separating line
	Since they're perpendicular...*/
	tngSep = (-1)/tngCon;

	/*Where is class1 and class2?
	It is enough to find class1, class2 must be on the opposite side*/
	class_one_flag = check_sep_line(tngSep, avgx1, avgy1, midx, midy);
	class_two_flag = (-1)*class_one_flag;

	/*Testing*/
	moveon=1;
	while(moveon==1)
	{
		control = scanf("%f %f",&x,&y);

		if(control==2)
		{
			label = check_sep_line(tngSep, x, y, midx, midy);

			if(label == class_one_flag)
				printf("class1\n");
			else if(label == class_two_flag)
				printf("class2\n");
		}
		else
			moveon=0;
	}
}

/*Checks if the given (x,y) point is above or below the line*/
int check_sep_line(float tng, float x, float y, float x2, float y2)
{
	int flag;

	/*	y-y2/x-x2=tng
		y-y2 = tng*(x-x2)
		y 	 = tng*(x-x2)+y2
		0 	 = tng*(x-x2)+y2-y 	 */

	if((tng*(x-x2)+y2-y)>0)
		flag = 1;
	if((tng*(x-x2)+y2-y)<0)
		flag = -1;

	return flag;
}
