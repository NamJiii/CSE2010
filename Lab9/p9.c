#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _DisjointSet{
	int size_maze;
	int* ptr_arr;
}DisjointSets;

void Init(DisjointSets *sets, DisjointSets *maze_print, int num);
void Union(DisjointSets *sets, int i, int j);
int Find(DisjointSets *sets, int i);
void CreateMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void PrintMaze(DisjointSets *sets, int num);
void FreeMaze(DisjointSets *sets, DisjointSets *maze_print);
void DeleteCycle(DisjointSets *sets,int num);

int main(int argc, char* argv[]){
	int num, i;
	FILE* fi = fopen(argv[1], "r");
	DisjointSets *sets, *maze_print;
	fscanf(fi, "%d", &num);
	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));
	Init(sets, maze_print, num);
	CreateMaze(sets, maze_print, num);
	PrintMaze(maze_print, num);
	FreeMaze(sets, maze_print);
	fclose(fi);
}

void Init(DisjointSets *sets, DisjointSets *maze_print, int num){
	int i;
	sets->size_maze = maze_print->ptr_arr = num;
	sets->ptr_arr = (int*)malloc(sizeof(int) * num * num);
	maze_print->ptr_arr = (int*)malloc(sizeof(int) * num * (num - 1) * 2);
	for(i = 0; i < num * num; i++){
		sets->ptr_arr[i] = i;
		if(i > num * (num - 1))
			continue;
		maze_print->ptr_arr[i] = -1;
		maze_print->ptr_arr[num * (num - 1) + i] = -1;
	}
}

int Find(DisjointSets *sets, int i){
 	if(sets->ptr_arr[i] < 0 || sets->ptr_arr[i] == i)
 		return i;
 	return Find(sets, sets->ptr_arr[i]);
}

void Union(DisjointSets *sets, int i, int j){
 	int uni1 = Find(sets, i), uni2 = Find(sets, j);
 	if(sets->ptr_arr[uni1] == uni1 && sets->ptr_arr[uni2] == uni2){
 		sets->ptr_arr[uni1] = uni2;
 		sets->ptr_arr[uni2] = -1;
 	}
 	else if(sets->ptr_arr[uni1] < sets->ptr_arr[uni2]){
 		sets->ptr_arr[uni2] = uni1;
 	}
 	else{
 		if(sets->ptr_arr[uni2] == sets->ptr_arr[uni1]) sets->ptr_arr[uni2]--;
 		sets->ptr_arr[uni1] = uni2;
 	}
}

void CreateMaze(DisjointSets *sets, DisjointSets *maze_print, int num){
 	
 	int a,b,x,y,chs;
 	int wall = num * (num - 1) * 2;

 	srand((unsigned int)time(NULL));

 	while(1){
	 	while(1){
			chs = rand() % wall;
			if(maze_print->ptr_arr[chs]!=0) break;
		}

	 	maze_print->ptr_arr[chs] = 0;

	 	if (chs < num * (num - 1)) {
	 		x=chs/(num-1);
	 		y=chs%(num-1);
	 		a=x*num+y;
	 		b=a+1;
	 	}
	 	else {
	 		a = chs - num * (num - 1);
	 		b = a + num;
	 	}

	 	if (Find(sets, a) != Find(sets, b)) Union(sets, a, b);
	 	else continue;

		if(Find(sets,0)==Find(sets,num*num-1)) break;
 	}
}

void PrintMaze(DisjointSets *maze_print, int num){

	int length = 2 * num + 1;
	int i, j, n;

	for (i = 0; i < num; i++) printf(" -");
	printf(" \n");

	for (i = 1; i < length - 1; i++) {
		if (i % 2) {
			
			if (i != 1) printf("| ");
			else printf("  ");

			for (j = 0; j < num - 1; j++) {
				if (maze_print->ptr_arr[(i / 2) * (num - 1) + j]) printf("| ");
				else printf("  ");
			}
			if (i != length - 2) printf("|\n");
			else printf(" \n");
		}
		else {
			for (j = 0; j < num; j++) {
				n = ((i - 1) / 2) * num + j + num * (num - 1);
				if (maze_print->ptr_arr[n]) printf(" -");
				else printf("  ");
			}
			printf(" \n");
		}
	}

	for (i = 0; i < num; i++) printf(" -");
	printf(" \n");

}

void FreeMaze(DisjointSets *sets, DisjointSets *maze_print){
	free(sets->ptr_arr);
	free(sets);
	free(maze_print->ptr_arr);
	free(maze_print);
}
/*
void DeleteCycle(DisjointSets *sets, int num){
	int i,j,k;
	for(k=2;k<num;k++){
		for(i=0;i<k;i++){
			if(find(sets,i)==find(sets,i+1)==find(sets,i+num)==find(sets,i+num+1)


}*/
