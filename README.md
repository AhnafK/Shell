# Shell
by Mohamed Jamil and Ahnaf Kazi

Features:
	-Executes commands
	-Parse multiple commands on one line
	-Redirects with < and >
	-Piping with |

Attempted:
	-keeping quotes as one token

/*parse_args()
  input: char *line
  output: array of strings where each string is a token

  separates line into arguments
 */

/*parse_multiple()
  input: char *line
  output: array of array of tokens for each command

  seperates line into multiple parts with respaect to the delimiter of ;.
  facilitates multiple commands in a single line
 */