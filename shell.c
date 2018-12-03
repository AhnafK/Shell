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
static void sighandler(int signo){
	if(signo==SIGINT){
	}

}
int main(int argc, char *argv[]){
  int* status=malloc(sizeof(int));
  *status=0;
  int backup_stdout=dup(STDOUT_FILENO);
  int backup_stdin=dup(STDIN_FILENO);
  signal(SIGINT,sighandler);
  while(WIFEXITED(*status)){
      char * str1=calloc(1000,sizeof(char));
	  while(!strcmp(str1,"")){
		printf("shell$ ");
		//printf("%c", getchar());  
		fgets(str1,1000,stdin);
	    str1[strlen(str1)-1]='\0';
	  }
      char *** args=parse_multiple(str1);
      for(int i=0;i<lenarray(args);i++){
			if(!fork()){
				int executed=1;
				for(int j=0;j<lenarrayl(args[i]);j++){
					if(!strcmp(args[i][j],">")){
						int fd=open(args[i][j+1],O_WRONLY|O_CREAT);
						int new=dup2(fd,STDOUT_FILENO);
						args[i][j]=NULL;
					}
					else if(!strcmp(args[i][j],"<")){
						int fd=open(args[i][j+1],O_RDONLY);
						int new=dup2(fd,STDIN_FILENO);
						execlp(args[i][j-1],args[i][j-1],NULL);
					}
					else if(!strcmp(args[i][j],"|")){
						int fd[2];
                		pipe(fd);
						char ** outargs=calloc(10,sizeof(char));
						for(int ind=0;ind<j;ind++){
							outargs[ind]=args[i][ind];
						}
						char ** inargs=calloc(10,sizeof(char));
						for(int ind=j;ind<lenarrayl(args[i]);ind++){
							inargs[ind]=args[i][ind];
						}
						int wr=dup2(fd[1],STDOUT_FILENO);
						int rd=dup2(fd[0],STDIN_FILENO);
						if(!fork()){
							execvp(outargs[0],outargs);
							dup2(backup_stdout,STDOUT_FILENO);
							close(fd[1]);
						}
						else{
							execvp(inargs[0],inargs);
							dup2(backup_stdin,STDIN_FILENO);
							close(fd[0]);
						}
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