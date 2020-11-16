#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define inf 1000

typedef struct Node{
	int vertex;
	int dist;
	int prev;
}Node;

typedef struct Graph{
	int size;
	int** vertices;
	Node* nodes;
}Graph;

typedef struct Heap{
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap,int vertex,int distance);
Node deleteMin(Heap* minHeap);

void main(int argc, char* argv[]){
	
	FILE *fi = fopen(argv[1],"r");
	Graph g;

	int size;
	fscanf(fi,"%d\n",&size);
	g = CreateGraph(size+1);
	char temp=0;
	while(temp!='\n'){
		int node1,node2,weight;
		fscanf(fi,"%d-%d-%d",&node1,&node2,&weight);
		g.vertices[node1-1][node2-1]=weight;
		temp=fgetc(fi);
	}
	printShortestPath(g);
}


Graph CreateGraph(int size){
	int i,j;
	Graph g;
	g.size = size;
	g.nodes=malloc(sizeof(Node)*size);
	g.vertices = malloc(sizeof(int*)*size);
	for(i=0;i<size;i++){
		g.vertices[i]=malloc(sizeof(int)*size);
		g.nodes[i].vertex = i;
		g.nodes[i].prev=0;
		g.nodes[i].dist=inf;
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(i==j) g.vertices[i][j]=0;
			else g.vertices[i][j]=inf;
		}
	}
	return g;
}

Heap* createMinHeap(int heapSize){
	Heap* H = malloc(sizeof(Heap));
	H->Capacity = heapSize;
	H->Size = 0;
	H->Element = malloc(sizeof(Node)*heapSize);
	return H;
}

void insertToMinHeap(Heap* minHeap,int vertex, int distance){
	Node tmp;
	tmp.vertex=vertex;
	tmp.dist=distance;
	int i;
	for(i=++minHeap->Size;minHeap->Element[i/2].dist>distance;i/=2){
		minHeap->Element[i] = minHeap->Element[i/2];
	}
	minHeap->Element[i]=tmp;
}

Node DeleteMin(Heap* minHeap){
	int i,Child;
	int MinD,LastD;
	Node tmp, Lasttmp;
	tmp = minHeap->Element[1];
	MinD = minHeap->Element[1].dist;
	Lasttmp = minHeap->Element[minHeap->Size--];

	for(i=1;i*2<minHeap->Size; i=Child){
		Child=i*2;
		if(Child!=minHeap->Size && minHeap->Element[Child+1].dist<minHeap->Element[Child].dist) Child++;
		if(LastD>minHeap->Element[Child].dist) minHeap->Element[i] = Lasttmp;
		else break;
	}
	minHeap->Element[i]=Lasttmp;
	return tmp;
}
void printP(Graph g,int n){
	if(n!=0){
		printP(g,g.nodes[n].prev);
		printf("->");
	}
	printf("%d",n+1);
}
void printShortestPath(Graph g){
	int i,j;
	Node tmp;
	Heap* H = createMinHeap(g.size);
	g.nodes[0].dist=0;
	for(i=1;i<g.size-1;i++){
		g.nodes[i].dist=g.vertices[0][i];
		if(g.vertices[0][i]!=inf){
			g.nodes[i].prev=0;
		}
		insertToMinHeap(H,i,g.nodes[i].dist);
	}

	while(H->Size!=0){
		tmp = DeleteMin(H);
		for(i=0;i<g.size-1;i++){
			if(g.vertices[tmp.vertex][i]!=inf&&g.vertices[tmp.vertex][i]!=0){
				if(tmp.dist+g.vertices[tmp.vertex][i]<g.nodes[i].dist){
					g.nodes[i].dist=tmp.dist+g.vertices[tmp.vertex][i];
					g.nodes[i].prev=tmp.vertex;
					insertToMinHeap(H,i,g.nodes[i].dist);
				}
			}
		}
	}

	for(i=1;i<g.size-1;i++){
		printP(g,i);
		printf(" (cost : %d)\n",g.nodes[i].dist);
	}
}
