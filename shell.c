#include "shell.h"
char ** parse_arg(char* line) {
	char ** ans = calloc(8, sizeof(char*));
	char *s = strtok(line, " ");
	int i = 0;
	while (s) {
		ans[i] = s;	
		/*printf("%d : %s", i, ans[i]);*/
		s = strtok(NULL, " ");
		i++;
	}
	return ans;
}
char *** parse_multiple(char* line){
	char *** ans = calloc(8, sizeof(char**));
	char *s = strsep(&line, ";");
	int i = 0;
	while (s) {
	        ans[i]=parse_arg(s);
		/*printf("%d : %s", i, ans[i]);*/
		s = strsep(&line, ";");
		i++;
	}
	return ans;
} 

char ** parse_quote(char* line) {
	char ** ans = calloc(8, sizeof(char*));
	char *s = strsep(&line, "\"");
	int i = 0;
	while (s) {
		ans[i] = s;	
		/*printf("%d : %s", i, ans[i]);*/
		s = strsep(&line, " ");
		i++;
	}
	return ans;
}

int main(int argc, char *argv[]){
  
  int* status=malloc(sizeof(int));

    while(WEXITSTATUS(*status)!=5){
      char str1[100];
      printf("shell$ ");
      fgets(str1,100,stdin);
      str1[strlen(str1)-1]='\0';
      char *** args=parse_multiple(str1);
      for(int i=0;i<sizeof(args)/sizeof(char**);i++){
			if(!fork()){
				printf("\n");
				execvp(args[i][0],args[i]);
				exit(1);
		}
			else{
				wait(status);
			}
		}
		if(!strcmp(args[0][0],"exit")){
			exit(5);
			free(status);
		}
		if(!strcmp(args[0][0],"cd")){
			chdir(args[0][1]);
		}
	} 
	
    wait(status);
  	return 0;
}
