#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "head.h"

char data_soal[100][400];
int jml_soal = 0;

char score[15][30] = {"50.000", "125.000", "250.000", "500.000", "1.000.000",
                        "2.000.000", "4.000.000", "8.000.000", "16.000.000", "32.000.000",
                        "64.000.000", "125 Juta", "250 Juta", "500 Juta", "1 Milyar"};

peserta readlogin(){
    peserta data;
    FILE *fp = fopen("database/login.bin", "rb");
    if(fp == NULL){
        printf("Silahkan registrasi terlebih dahulu\n");
        exit(1);
    }
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
    char buffer[255];
    char *token;
    soal curSoal;
    int hitung = 0;
    //printf("%s\n", textsoal);
    strcpy(buffer, textsoal);
    token = strtok(buffer, "@");
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

void parsePilihan(char pilihan[255]){
    char buffer[255];
    char *token;char huruf = 'A';
    strcpy(buffer, pilihan);
    token = strtok(buffer, "$");
    while(token != NULL){
        printf("%c.%s\n", huruf, token);
        huruf++;
        token = strtok(NULL, "$");
    }
}

int *randomSoal(int jmlsoal){
    time_t t;
    static int playingSoal[15];
    srand((unsigned)time(&t));
    for(int i = 0;i < 15;i++){
        playingSoal[i] = rand()%jmlsoal;
        //printf("%d\n", playingSoal[i]);
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

    system("clear");

    readsoal();
    soal buffer_soal;
    int *playingSoal;char lanjut;
    playingSoal = randomSoal(jml_soal);
    char jawaban;char uang[30] = "0";
    for(int i = 0;i < 15;i++){
        printf("========================================\n");
        printf("SELAMAT DATANG DI PERMAINAN\n");
        printf("WHO WANT TO BE A MILLIONARE\n");
        printf("========================================\n");
        printf("Hadiah Anda Saat Ini : Rp.%s\n", uang);
        printf("Next Hadiah : %s\n", score[i]);
        printf("========================================\n");

        // Soal dan mekanisme jawab
        buffer_soal = parseSoal(data_soal[playingSoal[i]]);
        printf("Soal : %s\n", buffer_soal.soal);
        parsePilihan(buffer_soal.pilihan);
        printf("Jawab : ");scanf(" %c", &jawaban);
        jawaban = toupper(jawaban);
        printf("========================================\n");
        if(jawaban == buffer_soal.kunci){
            strcpy(uang, score[i]);
            printf("Selamat anda benar\n");
            printf("========================================\n");
            printf("Hadiah Anda Saat Ini : Rp.%s\n", uang);
            if(i == 14){
                printf("SELAMAT ANDA TELAH MENYELESAIKAN PERMAINAN\nWHO WANT TO BE A MILLIONARE\n");
                break;
            }
            printf("Apakah anda ingin lanjut ? (Y/N) : ");
            scanf(" %c", &lanjut);
            if(lanjut == 'Y' || lanjut == 'y'){
                printf("========================================\n");
                system("clear");
                continue;
            }else{
                printf("========================================\n");
                printf("Selamat Anda berhak membawa uang sebesar : Rp.%s\n", uang);
                break;
            }
        }else{
            printf("Yah anda salah\n");
            printf("Maaf anda harus pulang dengan tangan kosong\n");
            printf("========================================\n");
            break;
        }
    }

    printf("Permainan Selesai\n");

    return EXIT_SUCCESS;
}