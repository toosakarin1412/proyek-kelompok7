#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "head.h"

char data_soal[100][400];
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
        strcpy(data_soal[jml_soal], buffer);
        int pjg_string = strlen(buffer);
        data_soal[jml_soal][pjg_string-1] = '\0';
        jml_soal++;
    }
    fclose(fp);
}

soal parseSoal(char *textsoal){
    char *token;
    soal curSoal;
    int hitung = 0;
    //printf("%s\n", textsoal);
    token = strtok(textsoal, "@");
    while(token != NULL){
        //printf("%s\n", token);
        if(hitung == 0){
            curSoal.kunci = token[0];
        }else if(hitung == 1){
            strcpy(curSoal.soal, token);
        }else if(hitung == 2){
            strcpy(curSoal.pilihan, token);
        }
        hitung++;
        token = strtok(NULL, "@");
    }

    return curSoal;
}

void parsePilihan(char *pilihan){

}

int *randomSoal(int jmlsoal){
    time_t t;
    static int playingSoal[15];
    srand((unsigned)time(&t));
    for(int i = 0;i < 15;i++){
        playingSoal[i] = rand()%jmlsoal;
        printf("%d\n", playingSoal[i]);
    }

    return playingSoal;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Silahkan masukkan username dan password\n");
        return EXIT_FAILURE;
    }

    peserta data;
    data = readlogin();
    // strcpy(data.username, "admin");
    // strcpy(data.password, "admin");
    if(strcmp(data.username, argv[1]) == 0 && strcmp(data.password, argv[2]) == 0){
        printf("Login berhasil\n");
    }else{
        printf("Login gagal\n");
        return EXIT_FAILURE;
    }

    readsoal();
    soal buffer_soal;
    int *playingSoal;
    playingSoal = randomSoal(jml_soal);
    for(int i = 0;i < jml_soal;i++){
        printf("====================\n");
        printf("No Soal : %d\n", playingSoal[i]);
        buffer_soal = parseSoal(data_soal[i]);
        printf("Kunci : %c\n", buffer_soal.kunci);
        printf("Soal : %s\n", buffer_soal.soal);
        printf("Pilihan : %s\n", buffer_soal.pilihan);
    }

    return EXIT_SUCCESS;
}