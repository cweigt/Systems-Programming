#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0) { //this is the child process for the fork
        printf("I am the cicle");
    }

    write(fd[1], "hello", 6);
    char * buffer = malloc(6);
    read(fd[0], buffer, 6);
    printf("%s\n", buffer);
    free(buffer);

    return 0;
}