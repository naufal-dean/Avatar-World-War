#include <stdio.h>
#include "../header/kata.h"

/*** Konstruktor ***/
void MakeEmptyKata (Kata * K) {
/* Membentuk sebuah Kata kosong */
/* I.S. K sembarang */
/* F.S. K kosong, Length(K) = 0 */
    // Algoritma
    Length(*K) = 0;
}

Kata MakeKata(char * C) {
/* Mengembalikan Kata sesuai char pointer C
   Akhir char pointer ditandai oleh karakter '\n' pada C */
    // Kamus lokal
    int i = 0;
    Kata K;
    // Algoritma
    while (C[i] != '\n') {
        Char(K, i + 1) = C[i];
        i++;
    }
    Length(K) = i;

    return (K);
}

/*** Kelompok fungsi TULIS ***/
void TulisKata (Kata K) {
/* Nilai elemen K ditulis ke layar, format "e1e2...en",
jika Length(K) = 0 tidak ditulis apapun tanpa spasi, enter,
atau karakter lain di depan, belakang, atau di antaranya. */
/* I.S. K terdefinisi */
/* F.S. K tertulis di layar dengan format "e1e2...en",
jika Length(K) = 0 tidak ditulis apapun */
    // Kamus lokal
    int i;
    // Algoritma
    for (i = 1; i <= Length(K); i++) {
        printf("%c", Char(K, i));
    }
}

/*** Kelompok operasi relasional terhadap Kata ***/
boolean EQKata (Kata K1, Kata K2) {
/* Mengirimkan true jika Length(K1) = Length(K2) dan semua elemen yang terdefinisi sama */
    // Kamus lokal
    int i;
    boolean eq = true;
    // Algoritma
    if (Length(K1) != Length(K2)) {
        eq = false;
    } else {
        for (i = 1; i <= Length(K1); i++) {
            if (Char(K1, i) != Char(K2, i)) {
                eq = false;
            }
        }
    }
    return eq;
}

/*** Kelompok operasi lain ***/
void CopyKata(Kata * Kout, Kata Kin) {
/* Melakukan penyalinan Kin ke Kout */
/* I.S. Kin terdefinisi, Kout sembarang */
/* F.S. Length(Kout) = Length(Kin) dan semua elemen yang terdefinisi
   di Kout sama dengan Kin. Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    // Kamus lokal
    int i, imax;
    // Algoritma
    imax = (Length(Kin) > LengthMax) ? (LengthMax) : (Length(Kin));
    Length(*Kout) = imax;
    for (i = 1; i <= imax; i++) {
        Char(*Kout, i) = Char(Kin, i);
    }
}

int KataToInt(Kata K) {
    // Kamus lokal
    int val = 0, i;
    // Algoritma
    for (i = 1; i <= K.Length; i++) {
        val = (val * 10) + (Char(K, i) - '0');
    }
    return (val);
}
