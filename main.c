#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRINT_LEN (10)
#define REALLOC_SIZE (1000)

char *cmd;
int cmd_len = REALLOC_SIZE;

void *my_realloc(void* ptr, int size){
	ptr = realloc(ptr, size);
	if(ptr == NULL) {
		fprintf(stderr, "realloc error.\n");
		exit(1);
	}
}

void read_file(FILE *fp){
	char ch;
	int i = 0;

	while((ch = fgetc(fp)) != EOF){
		cmd[i] = ch;
		i++;
		if((i%REALLOC_SIZE) == 0){
			my_realloc(cmd, cmd_len + sizeof(char) * REALLOC_SIZE);
			cmd_len += REALLOC_SIZE;
		}
	}
	cmd[i] = '\0';
}



int main(int argc, char *argv[]){

	FILE *fp;
	if((cmd = malloc(sizeof(char)*REALLOC_SIZE)) == NULL){
		fprintf(stderr, "malloc error.\n");
		exit(1);
	}

	if(argc == 2) {
		strcpy(cmd, argv[1]);
		//fprintf(stderr, "strlen:%d\n", strlen(cmd));
		//fprintf(stderr, "cmd[strlen(cmd)] = %d\n", cmd[strlen(cmd)]);
	} else if(argc == 3) {
		if(strcmp(argv[1], "-f") == 0){
		if((fp = fopen(argv[2], "r")) == NULL){
			fprintf(stderr, "File open error.\n");
			exit(1);
			}
		read_file(fp);
		fclose(fp);
		} else {
			fprintf(stderr, "Too many options.(%d)\n", argc);
			exit(1);
		}
	} else if(argc == 1) {
			printf("input:: ");
			scanf("%s", cmd);
	} else {
		fprintf(stderr, "Too many options.(%d)\n", argc);
		exit(1);
	}

	//fprintf(stderr, "cmd : %s\n", cmd);
	int pc = 0;
	int ptr = 0;
	int i, j;
	int rc = 0;
	char c;
	char mem[30000];
	for(i = 0; i < 30000; i++){
		mem[i] = 0;
	}
	//while(getchar() != '\n'){}
	while(cmd[pc] != '\0'){
/*
 * 		for(i = 0; i<PRINT_LEN; i++){
 *			printf("%3d ", mem[i]);
 *		}
 */
//		printf("\n");
		switch(cmd[pc]){
		case '>':
			ptr++;
			break;
		case '<':
			ptr--;
			break;
		case '+':
			mem[ptr]++;
			break;
		case '-':
			mem[ptr]--;
			break;
		case '.':
			printf("%c",mem[ptr]);
			break;
		case ',':
			while((c = getchar()) != '\n') mem[ptr] = c;
			break;
		case '[':
			if(mem[ptr] == 0){
				rc = 0;
				while(!(cmd[pc] == ']' && rc == 0)){
					if(cmd[pc] == ']') rc--;
					pc++;
					if(cmd[pc] == '[') rc++;
				}
			}
			break;
		case ']':
			if(mem[ptr] != 0){
				rc = 0;
				while(!(cmd[pc] == '[' && rc == 0)){
					if(cmd[pc] == '[') rc--;
					pc--;
					if(cmd[pc] == ']') rc++;
				}
			}
			break;
		default:
			break;
		}
		pc++;
	}
	printf("\n");
	return 0;
}
