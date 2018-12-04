# Shell
by Mohamed Jamil and Ahnaf Kazi

Features:
	*Executes commands
	*Parse multiple commands on one line
	*Redirects with < and >
	*Piping with |

Attempted:
	*keeping quotes as one token
Bugs:
	*Double Redirection does not function the first redirection of the two will be done
	*When using a seperate tester file to pass commands the shell prints out the shell prompt "shell$ " multiple times before executing the command. Although it works fine when using the shell normally
	*Multiple redirection and piping are not working

Files & Function Headers:

/*======== char ** parse_args() ==========
  input: char *line
  output: array of strings where each string is a token

  separates line into arguments
 ==========*/

/*======== char *** parse_multiple() ========
  input: char *line
  output: array of array of tokens for each command

  seperates line into multiple parts with respaect to the delimiter of ;.
  facilitates multiple commands in a single line
 ========*/
 
 /*======= int lenarray1() =========
   input: char ** array
   output: length of array of strings
   
   helper function to find the size of an array of strings
 ========*/
 
  /*======= int lenarray1() =========
   input: char *** array
   output: length of a 2d array of strings
   
   helper function to find the size of a 2d array of strings
 ========*/
