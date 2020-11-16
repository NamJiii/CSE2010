#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node
{
	ElementType element;
	Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType X,List L,Position P);
void PrintList(List L);

void Delete(ElementType X,List L);
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X,List L);
void DeleteList(List L);

List MakeEmpty(List L){
    List newNode = (List)malloc(sizeof(struct Node));
    newNode->element = 0;
    newNode->next = 0;
    L = newNode;
    return L;
}

int IsEmpty(List L){
	if(L = NULL) return 1;
	else return 0;
}

int IsLast(Position P, List L){
	if(!(P->next)) return 1;
	else return 0;
}

void Insert(ElementType X,List L,Position P){
	Position newNode;
	newNode = (Position)malloc(sizeof(struct Node));
	/*
	newNode->element = X;
	if(P == NULL){
	newNode->next = L;
	L = newNode;
	}
	
	else{
	newNode->next = P->next;
	P->next = newNode;
	}
	*/
	newNode->element = X;
	newNode->next = L->next;
	L->next = newNode;
}


void PrintList(List L){
	Position nodes = L;
	while(!IsLast(nodes,L)){
		nodes = nodes->next;		
		if(nodes->element !=0)printf("key:%d	", nodes->element);
	}
}

void Delete(ElementType X,List L){
}

Position Find(ElementType X, List L){
	if(X == -1){
		return NULL;
	}
	Position currentNode = L;
	while(currentNode->element != X){
		currentNode = currentNode->next;
	}
	
	return currentNode;
}

Position FindPrevious(ElementType X,List L){
}
void DeleteList(List L){
}

int main(int argc, char *argv[]){
char command;
int key1, key2;
FILE *input;
Position header;
Position tmp;
if(argc == 1)
input = fopen("input.txt", "r");
else
input = fopen(argv[1], "r");
header = MakeEmpty(header);
while(1) {
command = fgetc(input);
if(feof(input)) break;
switch(command) {
case 'i':
fscanf(input, "%d %d", &key1, &key2);
///tmp = Find(key2, header); hw3
///Insert(key1, header, tmp); hw3
Insert(key1,header,header);
break;
case 'd':
fscanf(input, "%d", &key1);
Delete(key1, header);
break;
case 'f':
fscanf(input, "%d", &key1);
tmp = FindPrevious(key1, header);
if(IsLast(tmp, header))
printf("Could not find %d in the list\n", key1);
else {
if(tmp->element>0)
printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
else
printf("Key of the previous node of %d is header.\n", key1);
}
break;
case 'p':
PrintList(header);
break;
default:
break;
}
}
DeleteList(header);
fclose(input);
return 0;
}
