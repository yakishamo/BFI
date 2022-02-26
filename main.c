#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define REALLOC_SIZE (3000)

char *cmd = NULL;
int cmdarr_len = REALLOC_SIZE;
int cmd_len = 0;

void read_file(FILE *fp){
	char ch;
	int i = 0;

	while((ch = fgetc(fp)) != EOF){
		cmd[i] = ch;
		i++;
		if(((i+1)%REALLOC_SIZE) == 0){
			if((cmd = realloc(cmd, cmdarr_len + sizeof(char) * REALLOC_SIZE)) 
					== NULL){
				fprintf(stderr, "realloc error.\n");
			}else{
				//nothing to do//
			}
			cmdarr_len += REALLOC_SIZE;
		}
	}
	cmd[i] = '\0';
}

int main(int argc, char *argv[]){

	FILE *fp;
	if((cmd = malloc(sizeof(char)*REALLOC_SIZE)) == NULL){
		fprintf(stderr, "malloc error.\n");
		exit(1);
	}else{
		//nothing to do.
	}
	if(argc == 2) {
		strcpy(cmd, argv[1]);
		cmd_len = strlen(cmd);
		if(cmd_len > REALLOC_SIZE){
			fprintf(stderr, "Too long code.\n");
			exit(1);
		}
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
			fprintf(stderr, "Too few options.");
	} else {
		fprintf(stderr, "Too many options.(%d)\n", argc);
		exit(1);
	}

	//fprintf(stderr, "%s\n", cmd);

	int pc = 0;
	int ptr = 0;
	int i, j;
	int rc = 0;
	char c;
	char mem[30000];
	for(i = 0; i < 30000; i++){
		mem[i] = 0;
	}

	while(cmd[pc] != '\0'){
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
					if(pc == cmd_len){
						fprintf(stderr, "'[' is too many.\n");
						exit(1);
					}
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
					if(pc == 0){
						fprintf(stderr, "']' is too many.\n");
						exit(1);
					}
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
	free(cmd);
	return 0;
}
