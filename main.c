#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

char soal[100][255];

// peserta readlogin(){
//     peserta data;
//     return data;
// }

void readsoal(){
    FILE *fp = fopen("database/soal.txt", "r");
    if(fp == NULL){
        printf("File tidak ditemukan\n");
    }
    char buffer[255];
    int hitung = 0;
    while(fgets(buffer, sizeof(buffer), fp) != NULL){
        strcpy(soal[hitung], buffer);
        hitung++;
    }
    fclose(fp);
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

    readsoal();
    printf("%s\n", soal[0]);

    return EXIT_SUCCESS;
}