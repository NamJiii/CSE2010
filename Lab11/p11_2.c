#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue {
	int* key;
	int first, rear, qsize, max_queue_size;
};

struct _Graph {
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(int* nodes, int n);
void InsertEdge(Graph G, int a, int b);
void DeleteGraph(Graph G);
void Topsort(Graph G);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void MakeEmpty(Queue Q);
void ArrayLength(int* n, char* str);
int IsNum(char input){return (input>='0'&&input<='9');}
void Inputs(int* arr, char* str);

int main(int argc, char* agrv[]) {
	FILE *fi = fopen(agrv[1], "r");
	char numbers[100], inputs[150];
	fgets(numbers, 100, fi);
	int n = 0;
	ArrayLength(&n, numbers);
	int* nodes = (int*)malloc(sizeof(int)*n);
	Inputs(nodes, numbers);
	Graph G = CreateGraph(nodes, n);
	fgets(inputs, 100, fi);
	int len = strlen(inputs), i, j;
	for (i=0 ; i<len ; i+=4) {
		int a = inputs[i] - '0', b = inputs[i + 2] - '0';
		InsertEdge(G, a, b);
	}
	Topsort(G);
	DeleteGraph(G);
	fclose(fi);
	return 0;
}

void ArrayLength(int* n, char* numbers) {
	int num=strlen(numbers);
	int i;
	for (i=0;i<num;i++) if (IsNum(numbers[i])) (*n)++;
}

void Inputs(int* arr, char* str) {
	int num = strlen(str);
	int i,cnt = 0;
	for (i=0; i<num; i++) if (IsNum(str[i])) arr[cnt++] = str[i]-'0';
}

Graph CreateGraph(int* nodes, int n) {
	Graph G = (Graph)malloc(sizeof(struct _Graph));
	int i, j;
	G->size = n;
	G->node = (int*)malloc(sizeof(int) * G->size);
	G->matrix = (int**)malloc(sizeof(int*) * G->size);
	for (i = 0; i < G->size; i++) {
		G->node[i] = nodes[i];
		G->matrix[i] = (int*)malloc(sizeof(int) * G->size);
		for (j = 0; j < G->size; j++) G->matrix[i][j] = 0;
	}
	return G;
}

void InsertEdge(Graph G, int a, int b) {
	int x, y, i;
	for (i = 0; i < G->size; i++) {
		if (G->node[i] == a) x = i;
		if (G->node[i] == b) y = i;
	}
	G->matrix[x][y] = 1;
} 

void DeleteGraph(Graph G){
	free(G->node);
	int i;
	for(i=0;i<G->size;i++) free(G->matrix[i]);
	free(G->matrix);
	free(G);
}

void Topsort(Graph G){
	Queue tmp = MakeNewQueue(G->size);
	int* a = (int*)malloc(sizeof(int) * G->size);
	int i, j;
	for(i = 0; i < G->size; i ++){
		a[i] = 0;
		for(j = 0; j < G->size; j ++){
			if(i == j) continue;
			if(G->matrix[j][i]) a[i] ++;
		}
	}

	for(i = 0; i < G->size; i ++) if(!a[i]) Enqueue(tmp, i);

	while(!IsEmpty(tmp)){
		int b = Dequeue(tmp);
		printf("%d ", G->node[b]);
		for(i = 0; i < G->size; i ++){
			if(G->matrix[b][i])
				if(!(--a[i])) Enqueue(tmp, i);
		}
	}
	printf("\n");
	DeleteQueue(tmp);
}

Queue MakeNewQueue(int X){
	Queue tmp = (Queue)malloc(sizeof(struct _Queue));
	int i;
	tmp->first = tmp->rear = tmp->qsize = 0;
	tmp->max_queue_size = X;
	tmp->key = (int*)malloc(sizeof(int) * X);
	return tmp;
}

int IsEmpty(Queue Q){
	return Q->first == Q->rear;
}

int Dequeue(Queue Q){
	return Q->key[Q->first++];
}

void Enqueue(Queue Q, int X){
	Q->key[Q->rear++] = X;
}

void DeleteQueue(Queue Q){
	free(Q->key);
	free(Q);
}
