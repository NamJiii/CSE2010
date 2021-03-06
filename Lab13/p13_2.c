#include<stdio.h>
#include<stdlib.h>

typedef struct Graph{
	int num;
	int** weight;
	int* check_visit;
}graph;

typedef struct Stack{
	int* content;
	int top;
	int max_stack_size;
}stack;

typedef struct CircularQueue{
	int* content;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
}queue;

graph makeGraph(FILE* fi);
void DFS_recursive(graph g,int start, int end);
void DFS_iterative(graph g,int start, int end);
void BFS_search(graph G,int start, int end);
stack* create_stack(int num);
void push(stack* s,int value);
int pop(stack* s);
void close_stack(stack* s);
queue* create_queue(int size);
void enqueue(queue* q,int value);
int dequeue(queue* q);
void close_queue(queue* q);
void clear_graph(graph g);

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1],"r");
	graph g =makeGraph(fi);

	int start, end;
	fscanf(fi,"%d-%d",&start,&end);

	printf("DFS recursive : ");
	DFS_recursive(g,start,end);
	if(g.num<end) printf("cannot find");
	else if(g.check_visit[end-1]==0) printf("cannot find");
	clear_graph(g);
	printf("\nDFS iterative : ");
	DFS_iterative(g,start,end);
	printf("\n");
	clear_graph(g);
	printf("BFS : ");
	BFS_search(g,start,end);
	printf("\n");

	fclose(fi);
}

graph makeGraph(FILE* fi){
	int i,j,size;
	char input;
	graph G;
	fscanf(fi,"%d",&size);
	G.num=size;

	G.check_visit = (int*)malloc(sizeof(int)*size);

	G.weight = (int**) malloc(sizeof(int*)*size);
	for(i=0;i<size;i++){G.weight[i] = (int*)malloc(sizeof(int)*size);}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			G.weight[i][j]=0;
		}
	}

	while(input!='\n'&&input!=EOF){
		int a,b;

		fscanf(fi,"%d-%d",&a,&b);
		G.weight[a-1][b-1]=1;
		input=fgetc(fi);
	}
	return G;
}

void clear_graph(graph g){
	int i;
	for(i=0; i<g.num;i++){
		g.check_visit[i]=0;
	}
}

queue* create_queue(int size){
	queue* q=(queue*)malloc(sizeof(queue));
	q->content = (int*) malloc(sizeof(int)*size);
	q->max_queue_size=size;
	q->qsize=0;
	q->rear=-1;
	return q;
}

void enqueue(queue* q,int value){
	q->rear = (q->rear+1) % q->max_queue_size;
	q->content[q->rear] = value;
}

int dequeue(queue* q){
	return q->content[q->qsize++];
}

void close_queue(queue* q){
	free(q->content);
	free(q);
}

void BFS_search(graph g,int start, int end){
	int temp;
	int i;
	queue* q = create_queue(g.num);
	enqueue(q,start-1);

	g.check_visit[start-1] = 1;
	while(!(q->qsize>q->rear)){
		temp = dequeue(q);
		printf("%d ",temp+1);
		for(i=0;i<end;i++){
			if(g.weight[temp][i]!=0&&g.check_visit[i]==0){
				enqueue(q,i);
				g.check_visit[i]=1;
			}
		}
	}
	if(temp+1!=end) printf("cannot find");
	close_queue(q);
}

stack* create_stack(int num){
	stack* s =(stack*) malloc(sizeof(stack));
	s->content =(int*) malloc(sizeof(int)*num);
	s->max_stack_size = num;
	s->top = -1;
	return s;
}

void DFS_iterative(graph G,int start, int end){
	int temp, i;
	stack* s = create_stack(G.num);
	push(s,start-1);

	G.check_visit[start-1] = 1;
	while(s->top>=0){
		temp = pop(s);
		printf("%d ",temp+1);
		if(temp+1==end) break;
		for(i=0;i<G.num;i++){
			if(G.weight[temp][i]!=0&&G.check_visit[i]==0){
				push(s,i);
				G.check_visit[i]=1;
			}
		}
	}

	if(temp+1!=end) printf("cannot find");
	close_stack(s);
}

void push(stack* s,int value){
	s->content[++s->top]= value;
}

int pop(stack* s){
	if(s->top<0) return -100;

	return s->content[s->top--];
}

void close_stack(stack* s){
	free(s->content);
	free(s);
}

void DFS_recursive(graph g, int start, int end){
	int i;
	g.check_visit[start-1] = 1;
	printf("%d ",start);
	for(i=0; i<g.num; i++){
		if(g.weight[start-1][i]!=0&& g.check_visit[i]==0){
			if(g.check_visit[end-1]==0) DFS_recursive(g,i+1,end);
		}
	}
}


