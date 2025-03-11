#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    FILE * input_fp; //input file with read only
    input_fp = fopen("genesis.txt", "r+");

    FILE * part1; //first output file for reverse, creating with write permissions
    part1 = fopen("genesis_reverse.txt", "w+");

    FILE * part2;
    part2 = fopen("genesis_line_reverse.txt", "w+");

    char buffer[1000]; //fixed size of memory

    //going to end of the file to determine size
    fseek(input_fp, 0, SEEK_END);
    int file_size = ftell(input_fp); //tells us where we are in file for reading

    //reverse order for part1
    //starting at the end of the file
    for(int i = file_size - 1; i >= 0; i--){
        fseek(input_fp, i, SEEK_SET); //using seek_set to go to char position
        int ch1 = fgetc(input_fp); //reading the character from the input file
        fputc(ch1, part1); //putting character into part1
    }

    //getting the size of the line for part2
    while((fgets(buffer, sizeof(buffer), input_fp))){
        int length = 0;
        //excluding those weird cases covered in class… thanks stackoverflow
        while(buffer[length] != '\0' && buffer[length] != '\n'){
            length++;
        }

        //now doing the actual reverse for part2 for each line
        for(int i = length - 1; i >= 0; i--){
            fputc(buffer[i], part2); //taking the character that it's currently at in the line and adding it to part2
        }
        fputc('\n', part2); //after every new line, adds this back for whatever reason
    }

    floseall();

    return 0;
}