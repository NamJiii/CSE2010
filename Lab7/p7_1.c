#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef struct HeapStruct{
	int Capacity;
	int Size;
	ElementType* Elements;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap* maxHeap,int key);
int Find(Heap* heap, int value);

void main(int argc, char*  argv[]){
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap* maxHeap;
	int heapSize, key;
	while(!feof(fi)){
		fscanf(fi,"%c",&cv);
		switch(cv){
			case 'n':
				fscanf(fi,"%d",&heapSize);
				maxHeap = CreateHeap(heapSize);
				break;
			case 'i':
				fscanf(fi,"%d",&key);
				Insert(maxHeap,key);
				break;
			case 'd':
//				DeleteMax(maxHeap);
				break;
			case 'p':
//				PrintHeap(maxHeap);
				break;
			case 'f':
				fscanf(fi,"%d",&key);
				if(Find(maxHeap,key)) printf("%d is in the tree.\n",key);
				else printf("%d is not in the tree.\n",key);
				break;
		}
	}
}

Heap* CreateHeap(int heapSize){
	Heap* TmpHeap;
	TmpHeap = malloc(sizeof(struct HeapStruct));
	TmpHeap->Elements = (int*)malloc((heapSize+1)*sizeof(int));
	TmpHeap->Capacity = heapSize;
	TmpHeap->Size = 0;
	return TmpHeap;
}

int Find(Heap* heap,int value){
	int i;
	for(i=1; i<=heap->Capacity; i++){
		if(heap->Elements[i]==value) return 1;
	}
	return 0;
}
	
void Insert(Heap* maxHeap,int key){
	int i;
	if(maxHeap->Size == maxHeap->Capacity) printf("Heap is full\n");
	else if(Find(maxHeap,key)) printf("%d is already in the tree.\n",key);
	else{
		for(i=++maxHeap->Size; maxHeap->Elements[i/2]<key && i/2>0; i/=2)
			maxHeap->Elements[i] = maxHeap->Elements[i/2];
		maxHeap->Elements[i]=key;
		printf("insert %d\n",key);
	}
}

