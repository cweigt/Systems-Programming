#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
int main(){
    FILE * pic;
    pic = fopen("darthvador.bmp", "r+");

    fseek(pic, 0, SEEK_END);
    int size = ftell(pic);

    //read the bmp info from the header
    unsigned int size1, width, height;

    fseek(pic, 18, SEEK_SET);
    fread(&width, 4, 1, pic);
    fread(&height, 4, 1, pic);

    fseek(pic, 34, SEEK_SET);
    fread(&size1, 4, 1, pic);


    //-1, create a new file stream for new pic
    FILE * new_pic;
    new_pic = fopen("darthvador_flipped.bmp", "w+");
    //0, write the same header into the new file stream
    rewind(pic);
    char * buf;
    buf = malloc(54);
    fread(buf, 54, 1, pic);
    fwrite(buf, 54, 1, new_pic);
    free(buf);
    buf = malloc(width * 3);
    for(int j = 0; j < height; j++){
        //1, create a row buffer for the whole row of pixels
        fread(buf, 3, width, pic);
        
        //2, swap from the beginning to the end
        for(int i = 0; i < width / 2; i++){
            for(int k = 0; k < 3; k++){
                char temp = buf[i * 3 + k];
                buf[i * 3 + k] = buf[(width - i - 1) * 3 + k];
                buf[(width - i - 1) * 3 + k] = temp;
            }
        }
        //3, write on the new file stream
        fwrite(buf, 3, width, new_pic);
        //repeat the last 1-3 steps
    }
    free(buf);
    fclose(new_pic);
    fclose(pic);
    return 0;
}