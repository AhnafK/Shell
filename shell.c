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

int main(int argc, char *argv[]){
    int f=fork();
    int* status=malloc(sizeof(int));
    if(!f){
        f=fork();
        if(!f){
            char str1[20];
            printf("shell$ ");
            fgets(str1,20,stdin);
            str1[strlen(str1)-1]='\0';
            char ** args=parse_arg(str1);
            printf("%s",args[0]);
            execvp(args[0],args);
        }
        else{
            wait(status);
        }
    }
    else{
        wait(status);
    }
    return 0;
}