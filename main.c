#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
	char cmd[30000];

	if(argc != 1) {
		strcpy(cmd, argv[1]);
	}else{
		printf("input:: ");
		scanf("%s", cmd);
	}
	
	int pc = 0;
	int ptr = 0;
	int i;
	int rc = 0;
	char c;
	char mem[30000];
	for(i = 0; i < 30000; i++){
		mem[i] = 0;
	}
	while(getchar() != '\n'){}
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
		}
		pc++;
	}
	printf("\n");
	return 0;
}
