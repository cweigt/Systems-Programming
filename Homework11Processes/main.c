#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    FILE *genesis;
    genesis = fopen("genesis.txt", "r");

    
    fseek(genesis, 0, SEEK_END);
    int count = ftell(genesis);
    printf("%d\n", count); // Printing out how many bytes there are
    fseek(genesis, 0, SEEK_SET);

    int n = 5; // Number of processes
    int length = count / n;

    for (int i = 0; i < n; i++) {
        int pid = fork();


        
        if (pid == 0) { // Child process
            char *buffer = malloc(length);


            fseek(genesis, i * length, SEEK_SET);
            fread(buffer, length, 1, genesis);

            char filename[20];
            sprintf(filename, "genesis_part_%d.txt", i + 1);

            FILE *newFile = fopen(filename, "w");


            fwrite(buffer, length, 1, newFile);
            fclose(newFile);
            free(buffer);
            exit(0);
        }
    }
    
    fclose(genesis);
    return 0;
}
