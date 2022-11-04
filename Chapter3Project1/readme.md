**Project 1—UNIX Shell**

This project consists of designing a C program to serve as a shell interface that accepts user commands and then executes each command in a separate process. Your implementation will support input and output redirection, as well as pipes as a form of IPC between a pair of commands. Completing this project will involve using the UNIX fork(), exec(), wait(), dup2(), and pipe() system calls and can be completed on any Linux, UNIX, or macOS system.

**Overview**

A shell interface gives the user a prompt, after which the next command is entered. The separate child process is created using the fork() system call, and the user’s command is executed using one of the system calls in the exec() family. The main() function presents the prompt osh-> and outlines the steps to be taken after input from the user has been read. The main() function continually loops as long as should run equals 1. 

**This project is organized into several parts:**

` `1. Creating the child process and executing the command in the child 

\2. Providing a history feature 

\3. Adding support of input and output redirection 

\4. Allowing the parent and child processes to communicate via a pipe

**Executing Command in a Child Process:**

A child process is forked and executes the command specified by the user. This will require parsing what the user has entered into separate tokens and storing the tokens in an array of character strings called args. This args array will be passed to the execvp() function, which has the following prototype: 

execvp(char \*command, char \*params[]).

A sample output for the shell interface is 

![](Aspose.Words.4df2448f-e3a3-474a-be7d-a2ea2e260822.001.png)





**Creating a History Feature**

The next task is to modify the shell interface program so that it provides a history feature to allow a user to execute the most recent command by entering !!. For example, if a user enters the command ls -l, she can then execute that command again by entering !! at the prompt. ![](Aspose.Words.4df2448f-e3a3-474a-be7d-a2ea2e260822.002.png)

![](Aspose.Words.4df2448f-e3a3-474a-be7d-a2ea2e260822.003.png)

**Redirecting Input and Output**

If a user enters 

osh>ls > out.txt

the output from the ls command will be redirected to the file out.txt. Similarly, input can be redirected as well. 

For example, if the user enters 

osh>sort < in.txt

the file in.txt will serve as input to the sort command.

Managing the redirection of both input and output will involve using the dup2() function, which duplicates an existing file descriptor to another file descriptor. For example, if fd is a file descriptor to the file out.txt, the call 

dup2(fd, STDOUT FILENO);

duplicates fd to standard output (the terminal).


Sample output file created:

![](Aspose.Words.4df2448f-e3a3-474a-be7d-a2ea2e260822.004.png)

**Communication via a Pipe**

This modification to the shell will allow the output of one command to serve as the input to another using a pipe. Both the ls and less commands will run as separate processes and will communicate using the UNIX pipe() function. 

![](Aspose.Words.4df2448f-e3a3-474a-be7d-a2ea2e260822.005.png)

![](Aspose.Words.4df2448f-e3a3-474a-be7d-a2ea2e260822.006.png)
