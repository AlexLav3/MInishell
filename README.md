# Minishell - 42Core project 

## Project Overview:
A small shell that has to imitate bash behavior 

The Minishell can handle the following: 

’ (single quote)

" (double quote)

 <, >, <<, >> 
 
Pipes

environment variables ($ followed by a sequence of characters) 

$? 

ctrl-C, ctrl-D and ctrl-\ 

interactive mode:
ctrl-C displays a new prompt on a new line.
ctrl-D exits the shell.
ctrl-\ does nothing.

built-in commands:
echo with option -n
cd with only a relative or absolute path
pwd 
export 
unset 
env
exit 

## Other notes 
Although it was allowed to use at most 1 global variable to indicate a received signal, we did not use any. 

It was required to not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon). 


