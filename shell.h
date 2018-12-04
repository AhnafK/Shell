#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>


char ** parse_arg(char* line);
char *** parse_multiple(char* line);
int lenarray2(char*** arr);
int lenarray1(char** arr);