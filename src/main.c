#include "../includes/pipex.h"
#include <unistd.h>
#include <stdio.h>

void    prog_exit(char *mes, int value)
{

}

int    main(int argc, char **argv, char **envp)
{
//    if (argc != 5)
//        prog_exit("Incorrect data", 1);
//    else
//    {
//
//    }
    printf("Before fork\n");
    pid_t pid = fork();
    if (pid == 0) {
        printf("child process %d \n", pid);
        exit(123);
    }
    else
    {
        printf("parent process %d\n", pid);
    }
    int a = 0;
    wait(&a);
    printf("Hunia %d\n", WEXITSTATUS(a));
    return 0;
}
