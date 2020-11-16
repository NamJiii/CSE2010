#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Stack{
	int* key; // array
	int top; // topofstack
	int max_stack_size; // capacity
}Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
int IsFull(Stack *S);

Stack* CreateStack(int max){
	Stack * S = NULL;
	S = (Stack*)malloc(sizeof(struct Stack));
	S -> key = (int*)malloc(sizeof(max));
	S->max_stack_size = max;
	S->top = -1;
	return S;
}

void Push(Stack* S, int X){
	if(IsFull(S)) printf("Full stack");
	else{
		S->key[++S->top] = X;
		printf("%d inserted\n",X);
	}
}

int IsFull(Stack *S){
	if(S->top >= S->max_stack_size) return 1;
	else return 0;
}
void main(int argc, char* argv[]) {
//   FILE* fi = fopen(argv[1], "r");
	FILE* fi = fopen("lab4_input1.txt","r");
   Stack* stack;
   char input_str[101];
   int max, i = 0, a, b, result;

   fgets(input_str, 101, fi);
   max = strlen(input_str);
   stack = CreateStack(max);
   while (input_str[i] != '#') {
      if (input_str[i] >= 48 && input_str[i] <= 57) {
         Push(stack, input_str[i]-48);
      }
      i++;
 //     Pop(stack);
   }
   //printf("\nevaluation result : %d\n", result);
   fclose(fi);
   //DeleteStack(stack);
}
