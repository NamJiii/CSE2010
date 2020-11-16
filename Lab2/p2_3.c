#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
	int num = atoi(argv[1]);
	char **name;
	printf("enter %d names:\n",num);

	name = (char **)malloc(sizeof(char*)*num);
	int i;

	for(i=0; i<num; i++){
		name[i] = (char *)malloc(sizeof(char)*31);
		scanf("%s",name[i]);
	}

	printf("the names you entered:\n");
	for(i=0; i<num; i++){
		printf("%s\n",name[i]);
	}

	for(i = 0; i<num; i++){
		free(name[i]);
	}
	free(name);
	return 0;
}
