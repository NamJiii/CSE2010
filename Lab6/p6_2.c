#include<stdio.h>
#include<stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode{
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Height(Position node);
int Max(int a, int b){if(a>b) return a; else return b;}
AVLTree Insert(ElementType X,AVLTree T);
void printInorder(AVLTree T);
void DeleteTree(AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);

int main(int argc, char **argv){
	FILE *fp = fopen(argv[1],"r");
	AVLTree myTree =NULL;
	int num;
	if(fp == NULL){
		printf("There is no file : %s\n",argv[1]);
		exit(-1);
	}

	while(fscanf(fp,"%d",&num)!=EOF){
		myTree = Insert(num,myTree);
		printInorder(myTree);
		printf("\n");
	}

	DeleteTree(myTree);
	return 0;
}
void DeleteTree(AVLTree T){
	if(T->Left!=NULL) DeleteTree(T->Left);
	else if (T->Right!=NULL) DeleteTree(T->Right);
	else if (T->Left==NULL && T->Right==NULL) free(T);
}

int Height(Position node){
	if(node==NULL) return -1;
	return node->Height;
}
AVLTree Insert(ElementType X,AVLTree T){
	if(T==NULL){
		T=malloc(sizeof(struct AVLNode));
		if(T==NULL) printf("Out of space!!!");
		else{
			T->Element = X;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if(X<T->Element){
		T->Left = Insert(X,T->Left);
		if(Height(T->Left) - Height(T->Right) == 2){
			if(X<T->Left->Element) T = SingleRotateWithLeft(T);
			else T = DoubleRotateWithLeft(T);
		}
	}
	else if(X>T->Element){
		T->Right = Insert(X,T->Right);
		if(Height(T->Right)-Height(T->Left)==2){
			if(X>T->Right->Element) T = SingleRotateWithRight(T);
			else T = DoubleRotateWithRight(T);
		}
	}
	else{
		printf("[Error] %d already in the tree!\n",X);
		return T;
	}
	T->Height = Max(Height(T->Left),Height(T->Right))+1;
	return T;
}

void printInorder(AVLTree T){
	if(T){
		printInorder(T->Left);
		printf("%d(%d) ", T->Element, T->Height);
		printInorder(T->Right);
	}
}

Position SingleRotateWithLeft(Position node){
	Position K1;
	K1 = node->Left;
	node->Left = K1->Right;
	K1->Right = node;

	node->Height = Max(Height(node->Left),Height(node->Right))+1;
	K1->Height = Max(Height(K1->Left),node->Height)+1;

	return K1;
}

Position DoubleRotateWithLeft(Position node){
	node->Left = SingleRotateWithRight(node->Left);

	return SingleRotateWithLeft(node);
}

Position SingleRotateWithRight(Position node){
	Position K1;
	K1 = node ->Right;
	node->Right = K1->Left;
	K1->Left =node;
	node->Height = Max(Height(node->Left),Height(node->Right))+1;
	K1->Height = Max(Height(K1->Left),Height(K1->Right))+1;
	return K1;
}

Position DoubleRotateWithRight(Position node){
	node->Right = SingleRotateWithLeft(node->Right);

	return SingleRotateWithRight(node);
}
