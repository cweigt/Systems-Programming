#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int main(){
    int fd;
    fd = open("genesis.txt", O_RDONLY); //opening the input file

    //this gets the size of the file
    int offset;
    lseek(fd, 0, SEEK_SET); //force the offset to be 0
    offset = lseek(fd, 0, SEEK_END); //moves to the end of the file 
    
    int half1;
    half1 = offset/2; //how many bytes for the first half

    int half2;
    half2 = offset - half1; //how many bytes for the second half

    int part1; //opening file for part1
    part1 = creat("genesis_part1.txt", 0644);

    char * buffer;
    buffer = malloc(1000); //how much it will read at one time

    lseek(fd, 0, SEEK_SET);
    while(half1 > 0){
        int length;
        if(half1 > 1000){
            length = 1000;
        }else if(half1 > 0){
            length = half1;
        }
        read(fd, buffer, length);
        half1 = half1 - length;
        write(part1, buffer, length);
    }
    close(part1);

    int part2; //opening file for part2
    part2 = creat("genesis_part2.txt", 0644);

    while(half2 > 0){
        int length;
        if(half2 > 1000){
            length = 1000;
        }else if(half2 > 0){
            length = half2;
        }
        read(fd, buffer, length);
        half2 = half2 - length;
        write(part2, buffer, length);
    }
    close(part2);


    //closing all files
    close(fd);
    free(buffer);
}