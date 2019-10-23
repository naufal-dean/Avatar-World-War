/*** ADT Matriks ***/

#ifndef MATRIKS_H
#define MATRIKS_H

#include "boolean.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 10
#define BrsMax 20
#define KolMin 10
#define KolMax 30

typedef int indeks; /* indeks baris, kolom */
typedef int ElType;
typedef struct {
    ElType Mem[BrsMax+1][KolMax+1];
    int NBrsEff; /* Jumlah baris yang terisi */
    int NKolEff; /* Jumlah kolom yang terisi */
} Matriks;
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/*** Selektor ***/
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

/*  DEFINISI PROTOTIPE PRIMITIF  */
/*** Konstruktor ***/
void MakeMatriks (int NB, int NK, Matriks *M);
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/*** Selektor ***/
boolean IsIdxValid (int i, int j);
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
indeks GetFirstIdxBrs (Matriks M);
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (Matriks M);
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (Matriks M);
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (Matriks M);
/* Mengirimkan indeks kolom terbesar M */
boolean IsIdxEff (Matriks M, indeks i, indeks j);
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */

/* KELOMPOK BACA/TULIS */
void BacaUkuranMatriks (Matriks * M);
/* I.S. Matriks belum memiliki ukuran */
/* F.S. Ukuran matriks matriks terdefinisi dan valid */
/* Matriks yang valid berukuran 10<=NB<=20 dan 10<=NK<=30 */
void TulisMatriks (Matriks M);
/* I.S. M terdefinisi */
/* F.S. Menuliskan matriks sesuai dengan kondisi bangunan yang ada */
/* Contoh: Menuliskan matriks berukuran 5x5
    * * * * * * *
    *           *
    *           *
    *           *
    *           *
    *           *
    * * * * * * *
*/

#endif
