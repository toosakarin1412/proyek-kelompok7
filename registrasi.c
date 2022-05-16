#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Silahkan masukkan username dan password\n");
        printf("./reg [username] [password\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}