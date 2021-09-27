#include <stdio.h>
#include <unistd.h>

int main(){
int pid = fork();
printf("Fork Returns%d\n",pid);
if (pid<0){
fprintf(stderr, "Fork Failed");
return 1;
}
else if(pid == 0)
printf("Child Created\n");
else{
printf("Fork Returns %d\n",pid);
printf("Child Process Complete\n");
}
return 0;


















































































// Theory
// Process creation means the construction of a new process for the
// execution. A parent process creates a sub process and by making a fork(
// ) system call. After this, exec( ) system call is used to load the binary file
// of the child process into memory and start its execution. During the
// execution of the child process the parent process can create more child
// processes, otherwise the wait( ) process until the child process is
// completed and finally exit( ) process terminates the process.

// Procedure
// All the linux commands are done and verified using IDE(VS Code) on
// Linux based System

// Problem Statement
// Write a program to create a process in LINUX.

// Algorithm
// Execute the following statements:
// 1. Start
// 2. Assign fork( ) system call to pid.
// 3. If pid is less than 0, the child process is not created and print a
// result as fork fails.
// 4. If pid is equal to 0, the child process will be created and the child
// process starts the execution.
// 5. If pid is greater than 0, the child process is returned and
// implements a wait system call to wait for the child process to
// complete its execution if any.
// 6. Print the process id of the child and parent process.
// 7. Stop.