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
	List newlist = (List) malloc(sizeof(struct Node));
	newlist->element = 0;
	newlist->next = NULL;
	L = newlist;
	return L;
}

int IsEmpty(List L){
	return L->next == NULL;
}

int IsLast(Position P, List L){
	return P->next == NULL;
}

void Insert(ElementType X,List L,Position P){
	if(P==NULL) printf("Insertion(%d) Failed : cannot find the location to be inserted\n",X);
	else{
	Position newNode;
	newNode = (Position)malloc(sizeof(struct Node));
	if(newNode==NULL) printf("Out of space!!!");

	newNode->element = X;
	newNode->next = P->next;
	P->next = newNode;
	}
}


void PrintList(List L){
	Position nodes = L;
	while(!IsLast(nodes,L)){
		nodes = nodes->next;		
		if(nodes->element !=0)printf("key:%d	", nodes->element);
	}
}

void Delete(ElementType X,List L){
	Position P, TmpCell;

	P = FindPrevious(X,L);

	if(P==NULL) printf("Deletion failed : element %d is not in the list\n",X);
	else if(!IsLast(P,L)){
		TmpCell = P->next;
		P->next = TmpCell->next;
		free(TmpCell);
	}
}

Position Find(ElementType X, List L){
	if(X==-1) return L;

	Position P;
	P=L->next;
	while(P!=NULL && P->element != X) P=P->next;
	if(P==NULL) return NULL;
	return P;
}

Position FindPrevious(ElementType X,List L){
	Position P;
	P=L;
	while(P->next!=NULL && P->next->element != X) P=P->next;
	if(P==NULL) return NULL;

	return P;
}

void DeleteList(List L){
	Position P, Tmp;
	
	P=L->next;
	L->next = NULL;
	while(P!=NULL){
		Tmp = P->next;
		free(P);
		P = Tmp;
	}
}

int main(int argc, char *argv[]){
	char command;
	int key1, key2;
	FILE *input;
	Position header;
	Position tmp;

	if(argc == 1) input = fopen("input.txt", "r");
	else input = fopen(argv[1], "r");

	header = MakeEmpty(header);

	while(1) {
		command = fgetc(input);
		if(feof(input)) break;
		switch(command) {
			case 'i':
				fscanf(input, "%d %d", &key1, &key2);
				tmp = Find(key2, header);
				Insert(key1, header, tmp);
				break;

			case 'd':
				fscanf(input, "%d", &key1);
				Delete(key1, header);
				break;

			case 'f':
				fscanf(input, "%d", &key1);
				tmp = FindPrevious(key1, header);
				if(IsLast(tmp, header)) printf("Could not find %d in the list\n", key1);
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
