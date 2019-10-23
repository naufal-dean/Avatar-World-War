// /*** ADT PETA ***/
//
// #ifndef PETA_H
// #define PETA_H
//
// #include "boolean.h"
//
// /* Ukuran minimum dan maksimum baris dan kolom */
// #define BrsMin 10
// #define BrsMax 20
// #define KolMin 10
// #define KolMax 30
//
// typedef int indeks; /* indeks baris, kolom */
// typedef int ElType;
// typedef struct {
//     ElType Mem[BrsMax+1][KolMax+1];
//     int NBrsEff; /* Jumlah baris yang terisi */
//     int NKolEff; /* Jumlah kolom yang terisi */
// } Peta;
// /* NBrsEff <= 1 dan NKolEff <= 1 */
// /* Indeks peta yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
// /* Memori peta yang dipakai selalu di "ujung kiri atas" */
//
// /*** Selektor ***/
// #define NBrsEff(M) (M).NBrsEff
// #define NKolEff(M) (M).NKolEff
// #define Elmt(M,i,j) (M).Mem[(i)][(j)]
//
// /*  DEFINISI PROTOTIPE PRIMITIF  */
// /*** Konstruktor ***/
// void MakePeta (int NB, int NK, Peta *M);
// /* I.S. NB dan NK adalah valid untuk memori peta yang dibuat */
// /* F.S. Peta M sesuai dengan definisi di atas terbentuk */
//
// /*** Selektor ***/
// boolean IsIdxValid (int i, int j);
// /* Mengirimkan true jika i, j adalah indeks yang valid untuk peta apa pun */
// indeks GetFirstIdxBrs (Peta M);
// /* Mengirimkan indeks baris terkecil M */
// indeks GetFirstIdxKol (Peta M);
// /* Mengirimkan indeks kolom terkecil M */
// indeks GetLastIdxBrs (Peta M);
// /* Mengirimkan indeks baris terbesar M */
// indeks GetLastIdxKol (Peta M);
// /* Mengirimkan indeks kolom terbesar M */
// boolean IsIdxEff (Peta M, indeks i, indeks j);
// /* Mengirimkan true jika i, j adalah indeks efektif bagi M */
//
// /* KELOMPOK BACA/TULIS */
// void BacaMATRIKS (Peta * M, int NB, int NK);
// /* I.S. IsIdxValid(NB,NK) */
// /* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
// /* Proses: Melakukan MakePeta(M,NB,NK) dan mengisi nilai efektifnya */
// /* Selanjutnya membaca nilai elemen per baris dan kolom */
// /* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
// 1 2 3
// 4 5 6
// 8 9 10
// */
// void TulisMATRIKS (Peta M);
// /* I.S. M terdefinisi */
// /* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
//    dipisahkan sebuah spasi */
// /* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
// /* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
// 1 2 3
// 4 5 6
// 8 9 10
// */
//
// /* Operasi lain */
// int NBElmt (Peta M);
// /* Mengirimkan banyaknya elemen M */
//
// #endif
