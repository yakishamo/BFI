#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	char cmd[1024];

	if(argc != 1) {
		strcpy(cmd, argv[1]);
	}else{
		printf("input:: ");
		scanf("%s", cmd);
	}
	
	int pc = 0;
	int ptr = 0;
	int i;
	char c;
	char mem[1024];
	for(i = 0; i < 1024; i++){
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
				while(cmd[pc] != ']'){
					pc++;
				}
			}
			break;
		case ']':
			if(mem[ptr] != 0){
				while(cmd[pc] != '['){
					pc--;
				}
			}
			break;
		default:
			printf("Unknown Command(%d)\n", pc+1);
			return -1;
		}
		pc++;
		/*for(i = 0; i < 10; i++){
			printf("%d ", mem[i]);
		}
		printf("\n");*/
	}
	printf("\n");
	return 0;
}
