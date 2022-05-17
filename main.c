#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

char soal[100][255];
int jml_soal = 0;

peserta readlogin(){
    peserta data;
    FILE *fp = fopen("database/login.bin", "rb");
    fread(&data, sizeof(peserta), 1, fp);
    fclose(fp);
    return data;
}

void readsoal(){
    FILE *fp = fopen("database/soal.txt", "r");
    if(fp == NULL){
        printf("File tidak ditemukan\n");
    }
    char buffer[255];
    jml_soal = 0;
    while(fgets(buffer, sizeof(buffer), fp) != NULL){
        strcpy(soal[jml_soal], buffer);
        int pjg_string = strlen(buffer);
        soal[jml_soal][pjg_string-1] = '\0';
        jml_soal++;
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
    for(int i = 0;i < jml_soal;i++){
        printf("%s\n", soal[i]);
    }

    return EXIT_SUCCESS;
}