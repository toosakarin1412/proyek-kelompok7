#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

void write2bin(peserta data){
    //
}

int main(int argc, char *argv[]){
    peserta data;
    if(argc != 3){
        printf("Silahkan masukkan username dan password\n");
        printf("./reg [username] [password\n");
        return EXIT_FAILURE;
    }

    strcpy(data.username, argv[1]);
    strcpy(data.password, argv[2]);

    write2bin(data);
    printf("Registrasi berhasil...\n");
    return EXIT_SUCCESS;
}