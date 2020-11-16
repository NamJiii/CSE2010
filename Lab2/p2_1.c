#include<stdio.h>

void main(int argv,char** argc)
{
	int num1,num2;

	printf("enter 2 integers\n");
	scanf("%d%d",&num1,&num2);

	printf("you entered\n%d, %d\n",num1,num2);
	swap(&num1,&num2);
	printf("after swapping\n%d, %d\n",num1,num2);
}

void swap(int *num1, int *num2)
{
	int temp=*num1;
	*num1 = *num2;
	*num2 = temp;
}

