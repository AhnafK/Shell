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
int lenarray(char*** arr){
	int i=0;
	while(arr[i]){
		i++;
	}
	return i;
}
int lenarrayl(char** arr){
	int i=0;
	while(arr[i]){
		i++;
	}
	return i;
}
int main(int argc, char *argv[]){
  int* status=malloc(sizeof(int));
  *status=0;
  int backup_stdout=dup(STDOUT_FILENO);
  int backup_stdin=dup(STDIN_FILENO);
    while(WIFEXITED(*status)){
      char * str1=readline("shell$ ");
      char *** args=parse_multiple(str1);
      for(int i=0;i<lenarray(args);i++){
			if(!fork()){
				int executed=1;
				for(int j=0;j<lenarrayl(args[i]);j++){
					if(!strcmp(args[i][j],">")){
						int fd=open(args[i][j+1],O_WRONLY|O_CREAT);
						int new=dup2(fd,STDOUT_FILENO);
						execlp(args[i][j-1],args[i][j-1],NULL);
					}
					else if(!strcmp(args[i][j],"<")){
						int fd=open(args[i][j+1],O_RDONLY);
						int new=dup2(fd,STDIN_FILENO);
						execlp(args[i][j-1],args[i][j-1],NULL);
					}
				}
				execvp(args[i][0],args[i]);
				dup2(backup_stdout,STDOUT_FILENO);
				dup2(backup_stdin,STDIN_FILENO);
			}
			else{
				wait(status);
			}
		}
		if(!strcmp(args[0][0],"exit")){
			free(status);
			free(str1);
			exit(1);
		}
		if(!strcmp(args[0][0],"cd")){
			chdir(args[0][1]);
		}
	} 
	
    wait(status);
  	return 0;
}
