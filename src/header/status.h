/* ADT Status */

#ifndef STATUS_H
#define STATUS_H

#include "boolean.h"
#include "array.h"
#include "matriks.h"
#include "stack.h"

/* Kamus umum */
#define LengthMax 50

typedef struct {
    Matriks Peta;
    Array ListBangunan;
    Stack StatusBangunan;
    int ActivePlayer;
} Status;

/*** Selektor ***/
#define Char(K, i) (K).TabKata[i]
#define Length(K) (K).Length

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
void MakeEmptyKata (Kata * K);
/* Membentuk sebuah Kata kosong */
/* I.S. K sembarang */
/* F.S. K kosong, Length(K) = 0 */

/*** Kelompok fungsi TULIS ***/
void TulisKata (Kata K);
/* Nilai elemen K ditulis ke layar, format "e1e2...en",
   jika Length(K) = 0 tidak ditulis apapun tanpa spasi, enter,
   atau karakter lain di depan, belakang, atau di antaranya. */
/* I.S. K terdefinisi */
/* F.S. K tertulis di layar dengan format "e1e2...en",
        jika Length(K) = 0 tidak ditulis apapun */

/*** Kelompok operasi relasional terhadap Kata ***/
boolean EQKata (Kata K1, Kata K2);
/* Mengirimkan true jika Length(K1) = Length(K2) dan semua elemen yang terdefinisi sama */

/*** Kelompok operasi lain ***/
void CopyKata(Kata * Kout, Kata Kin);
/* Melakukan penyalinan Kin ke Kout */
/* I.S. Kin terdefinisi, Kout sembarang */
/* F.S. Length(Kout) = Length(Kin) dan semua elemen yang terdefinisi
   di Kout sama dengan Kin. Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

#endif // STATUS_H
