#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
    int fd;
    fd = open("genesis.txt", O_RDONLY);

    int fd2;
    fd2 = creat("genesis_copy.txt", 0644);

    char ch_buffer;

    ssize_t ret;

    //ch_buffer is a pointer, so it needs the '&' character I guess

    //greater than 0 is the EOF, the loop stops once the EOF is less than 0
        //end of line
    while((ret = read(fd, &ch_buffer, sizeof(char))) > 0){
        write(fd2, &ch_buffer, sizeof(char));
    }

    //closing both files
    close(fd);
    close(fd2);
}