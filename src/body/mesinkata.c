#include <stdio.h>
#include "../header/mesinkata.h"

boolean EndKata;
Kata CKata;

void IgnoreBlank() {
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
    while (CC == BLANK) {
        ADV();
    }
}

void STARTKATA(char * path) {
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
    START(path);
    if (CC == MARK) {
        EndKata = true;
    } else {
        EndKata = false;
        IgnoreBlank();
        ADVKATA();
    }
}

void ADVKATA() {
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure AkuisisiKata */
    if (CC == MARK) {
        EndKata = true;
    } else {
        AkuisisiKata();
        IgnoreBlank();
    }
}

void AkuisisiKata() {
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    int i = 1;
    do {
        CKata.TabKata[i] = CC;
        i++;
        ADV();
    } while ((CC != MARK) && (CC != BLANK) && (i <= NMax));
    CKata.Length = i - 1;
}

/*** Kelompok input stdin ***/
void ScanInt(int * input) {
/* Membaca integer dari keyboard memakai mesinkar. */
/* I.S. input sembarang */
/* F.S. nilai input sesuai masukan pengguna */
    // Algoritma
    STARTKATA(NULL);
    (*input) = KataToInt(CKata);
}

void ScanChar(char * input) {
/* Membaca char dari keyboard memakai mesinkar. */
/* I.S. input sembarang */
/* F.S. nilai input sesuai masukan pengguna */
    // Algoritma
    STARTKATA(NULL);
    (*input) = Char(CKata, 1);
}

void ScanKata(Kata * input) {
/* Membaca Kata dari keyboard memakai mesinkar. */
/* I.S. input sembarang */
/* F.S. nilai input sesuai masukan pengguna */
    // Algoritma
    STARTKATA(NULL);
    CopyKata(input, CKata);
}
