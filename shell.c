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

int lenarray2(char*** arr){
	int i=0;
	while(arr[i]){
		i++;
	}
	return i;
}

int lenarray1(char** arr){
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
	signal(SIGINT,sighandler);
  	int backup_stdout=dup(STDOUT_FILENO);
  	int backup_stdin=dup(STDIN_FILENO);
	while(WIFEXITED(*status)){
      char str1[1000];
      printf("shell$ ");
	  if(!fgets(str1,1000,stdin)){
		  exit(1);
	  }
      str1[strlen(str1)-1]='\0';
      char *** args=parse_multiple(str1);
	  if(!strcmp(args[0][0],"")){
		  exit(0);
	  }
	  if(!strcmp(args[0][0],"exit")){
		exit(1);
		free(status);
	  }
	  if(!strcmp(args[0][0],"cd")){
		chdir(args[0][1]);
	  }
      for(int i=0;i<lenarray2(args);i++){
		if(!fork()){
		  	for(int j=0;j<lenarray1(args[i]);j++){
				if(!strcmp(args[i][j],">")){
					int fd=open(args[i][j+1],O_WRONLY|O_CREAT);
					int new=dup2(fd,STDOUT_FILENO);
					args[i][j]=NULL;
				}
				else if(!strcmp(args[i][j],"<")){
					int fd=open(args[i][j+1],O_RDONLY);
					int new=dup2(fd,STDIN_FILENO);
					args[i][j]=NULL;
				}
				else if(!strcmp(args[i][j],"|")){
					int fd[2];
					pipe(fd);
					if(!fork()){
						close(fd[0]);
						int new=dup2(fd[1],STDOUT_FILENO);
						args[i][j]=NULL;
						execvp(args[i][0],args[i]);
						exit(0);
					}
					else{
						wait(status);
						int rd=dup2(fd[0],STDIN_FILENO);
						close(fd[1]);
						char ** inargs=calloc(10,sizeof(char));
						int loc=0;
						for(int ind=j+1;ind<lenarray1(args[i]);ind++){
							inargs[loc]=args[i][ind];
							loc++;
						}
						execvp(inargs[0],inargs);
						free(inargs);
						exit(0);
					}
				}
			}
				execvp(args[i][0],args[i]);
				exit(0);
				dup2(backup_stdout,STDOUT_FILENO);
				dup2(backup_stdin,STDIN_FILENO);
			}
			else{
				wait(status);
			}
		}
	} 
    wait(status);
  	return 0;
}