typedef struct peserta
{
    char username[30];
    char password[30];
}peserta;

typedef struct soal{
    char pertanyaan[256];
    char pilihanganda[128];
    char jawaban;
}soal;