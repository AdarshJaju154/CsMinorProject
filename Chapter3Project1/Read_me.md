**Project 1—UNIX Shell**

This project consists of designing a C program to serve as a shell interface that accepts user commands and then executes each command in a separate process. Your implementation will support input and output redirection, as well as pipes as a form of IPC between a pair of commands. Completing this project will involve using the UNIX fork(), exec(), wait(), dup2(), and pipe() system calls and can be completed on any Linux, UNIX, or macOS system.

**Overview**

A shell interface gives the user a prompt, after which the next command is entered. The separate child process is created using the fork() system call, and the user’s command is executed using one of the system calls in the exec() family. The main() function presents the prompt osh-\> and outlines the steps to be taken after input from the user has been read. The main() function continually loops as long as should run equals 1.

**This project is organized into several parts:**

1\. Creating the child process and executing the command in the child

2\. Providing a history feature

3\. Adding support of input and output redirection

4\. Allowing the parent and child processes to communicate via a pipe

**Executing Command in a Child Process:**

A child process is forked and executes the command specified by the user. This will require parsing what the user has entered into separate tokens and storing the tokens in an array of character strings called args. This args array will be passed to the execvp() function, which has the following prototype:

execvp(char \*command, char \*params[]).

A sample output for the shell interface is
![4](https://user-images.githubusercontent.com/75697115/199963430-a7e6dbe2-7837-4fd7-8667-3d4603d2d964.jpg)


**Creating a History Feature**

The next task is to modify the shell interface program so that it provides a history feature to allow a user to execute the most recent command by entering !!. For example, if a user enters the command ls -l, she can then execute that command again by entering !! at the prompt. 
![2](https://user-images.githubusercontent.com/75697115/199963303-4b9d88c0-9d4b-4d37-9004-a93cd91b94a0.jpg)
![3](https://user-images.githubusercontent.com/75697115/199963318-ae2877a3-8f2a-4e8b-b08b-8b536cfd19be.jpg)


**Redirecting Input and Output**

If a user enters

osh\>ls \> out.txt

the output from the ls command will be redirected to the file out.txt. Similarly, input can be redirected as well.

For example, if the user enters

osh\>sort \< in.txt

the file in.txt will serve as input to the sort command.

Managing the redirection of both input and output will involve using the dup2() function, which duplicates an existing file descriptor to another file descriptor. For example, if fd is a file descriptor to the file out.txt, the call

dup2(fd, STDOUT FILENO);

duplicates fd to standard output (the terminal).

Sample output file created:
![1](https://user-images.githubusercontent.com/75697115/199963110-c60312dd-ea17-497d-b22f-c724c2525261.jpg)

**Communication via a Pipe**

This modification to the shell will allow the output of one command to serve as the input to another using a pipe. Both the ls and less commands will run as separate processes and will communicate using the UNIX pipe() function.

![image](https://user-images.githubusercontent.com/75697115/199962397-0bdb8fc0-6155-446c-b29d-6c2e4175a56f.png)

![image](https://user-images.githubusercontent.com/75697115/199962390-06caf2a5-5b1a-4bf4-b9ec-b6fc6503abab.png)

