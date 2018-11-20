#include "shell.h"
char ** parse_arg(char* line) {
	char ** ans = calloc(5, sizeof(char*));
	char *s = strsep(&line, " ");
	int i = 0;
	while (s) {
		ans[i] = s;	
		/*printf("%d : %s", i, ans[i]);*/
		s = strsep(&line, " ");
		i++;
	}
	return ans;
}
char *** parse_multiple(char* line){
	char *** ans = calloc(5, sizeof(char**));
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

int main(int argc, char *argv[]){
  int f=fork();
  int* status=malloc(sizeof(int));
  if(!f){
    while(WEXITSTATUS(*status)!=5){
      if(!fork()){
	char str1[20];
	printf("shell$ ");
	fgets(str1,20,stdin);
	str1[strlen(str1)-1]='\0';
	char *** args=parse_multiple(str1);
	for(int i=0;i<sizeof(args)/sizeof(char**);i++){
	  if(!fork()){
	    printf("\n");
	    execvp(args[i][0],args[i]);
	    if(!strcmp(args[i][0],"cd")){
	      chdir(args[i][1]);
	    }
	    exit(1);
	  }
	  else{
	    wait(status);
	  }
	}
	if(!strcmp(args[0][0],"exit")){
	  exit(5);
	}
      }
      else{
	wait(status);
      }
    } 
  }
  else{
    wait(status);
  }
  return 0;
}
