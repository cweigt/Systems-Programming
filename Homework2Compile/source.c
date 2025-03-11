#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * fp;

   fp = fopen ("testFile.txt", "w+");
   fprintf(fp, "%s %s %s %d %s", "We", "are", "in", 2025, "\n");
   fprintf(fp, "%s %s %s", "Riley", "is", "cool!");

   fclose(fp);

   printf("Done with creating \"testFile.txt\"");

   return(0);

}