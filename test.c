#include "shell.h"
char ** parse_quote(char* line) {
    char ** ans = calloc(8, sizeof(char*));
    char *s = strsep(&line, " ");
    int i = 0;
    while (s) {
      ans[i] = s;
      //printf("%d : %s", i, ans[i]);
      if(ans[i][0]=='\"'){
        s = "\"";
        strsep(&line, "\"");
        strcat(s,strsep(&line, "\""));
        strcat(s,"\"");
        i++;
      }
      else{
        s = strsep(&line, " ");
        i++;
      }
    }
    return ans;
  }
int main() {
  char * cmd="git commit -m\"adaadad\"";
  char ** args=parse_quote(cmd);
  int i=0;
  while(args[i]){
    printf("%s\n",args[i]);
    i++;
  }
  return 0;
}