#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALLOC_SIZE (256)

char cmd[30000];

void read_file(FILE *fp){
	char ch;
	int i = 0;

	while((ch = fgetc(fp)) != EOF){
		if(ch == '\n') continue;
		cmd[i] = ch;
		i++;
		if(i == 29999){
			fprintf(stderr, "File is too big.\n");
			exit(1);
		}
	}
	cmd[i] = '\0';
}



int main(int argc, char *argv[]){

	FILE *fp;
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
	int i;
	int rc = 0;
	char c;
	char mem[30000];
	for(i = 0; i < 30000; i++){
		mem[i] = 0;
	}
	//while(getchar() != '\n'){}
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
