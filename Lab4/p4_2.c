#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Stack{
	int* key; // Array
	int top; // TopOfStack
	int max_stack_size; // Capacity
}Stack;

Stack* CreateStack(int max);
void Pop(Stack *S);
void Push(int X, Stack* S);
void DeleteStack(Stack* S);
int IsEmpty(Stack* S);
int IsFull(Stack* S);

void Push(int X,Stack* S){
	if(IsFull(S)) printf("Full stack");
	else S->key[++S->top] = X;
}

void Pop(Stack* S){
	if(IsEmpty(S)) printf("Empty stack");
	else S->top--;
}

Stack* CreateStack(int max){
	Stack* S = NULL;
	S = (Stack*)malloc(sizeof(max));
	S->key = (int*)malloc(sizeof(int)*max);
	S->max_stack_size = max;
	S->top = -1;
	return S;
}

void DeleteStack(Stack* S){
	if(S!=NULL) free(S);
}

int IsEmpty(Stack* S){
	if(S == NULL) return 1;
	else return 0;
}

int IsFull(Stack* S){
	if(S->top>=S->max_stack_size) return 1;
	else return 0;
}

void main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1],"r");
	Stack* stack;
	char input_str[101];
	int max,i=0,a,b,result;

	fgets(input_str,101,fi);
	max = strlen(input_str);
	printf("Pushed numbers :");
	stack = CreateStack(max);
	while(input_str[i] != '#'){
		if(input_str[i]>='0' && input_str[i]<='9'){
			Push(input_str[i]-48,stack);
		}
		else if(input_str[i]=='+'||input_str[i]=='-'||input_str[i]=='*'||input_str[i]=='/'||input_str[i]=='%'){
			a = stack->key[stack->top];
			Pop(stack);
			b = stack->key[stack->top];
			Pop(stack);
			if(input_str[i]=='+') Push(b+a,stack);
			else if(input_str[i]=='-') Push(b-a,stack);
			else if(input_str[i]=='*') Push(b*a,stack);
			else if(input_str[i]=='/') Push(b/a,stack);
			else Push(b%a,stack);
		}
		else printf("input error");
		printf("%d ",stack->key[stack->top]);
		i++;
	}
	printf("\nevaluation result : %d\n",stack->key[stack->top]);
	fclose(fi);
	DeleteStack(stack);
}
