#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

peserta readlogin(){
    peserta data;
    return data;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Silahkan masukkan username dan password\n");
        return EXIT_FAILURE;
    }

    peserta data;
    //data = readlogin();
    strcpy(data.username, "admin");
    strcpy(data.password, "admin");
    if(strcmp(data.username, argv[1]) == 0 && strcmp(data.password, argv[2]) == 0){
        printf("Login berhasil\n");
    }else{
        printf("Login gagal\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}