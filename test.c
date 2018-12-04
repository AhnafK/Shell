#include "shell.h"

char ** parse_quote(char* line) {
  char ** ans = calloc(8, sizeof(char*));
  char *t = strsep(&line, "\"");
  char *s = strsep(&t, " ");
  int i = 0;
  while(t){
    while (s) {
      ans[i] = s;	
      /*printf("%d : %s", i, ans[i]);*/
      s = strsep(&t, " ");
      i++;
    }
    ans[i] = strsep(&line, "\"");
    i++;
    t = strsep(&line, "\"");
  }
  return ans;
}

int main() {
  char * cmd="git commit -m\"ada adad\"";
  char ** args=parse_quote(cmd);
  int i=0;
  while(args[i]){
    printf("%s\n",args[i]);
    i++;
  }
  return 0;
}
