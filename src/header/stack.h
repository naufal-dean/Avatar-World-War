/* ADT Stack */
/* Tabel dan alamat top disimpan secara eksplisit */
/* Memakai array statik */

#ifndef STACK_H
#define STACK_H

#include "boolean.h"
#include "bangunan.h"
#include "listlinier.h"

/* Kamus umum */
#define NilStack 0            // Indeks top stack kosong
#define MaxElStack 25         // Max elemen

/* Definisi elemen dan koleksi objek */
typedef int AddressStack;
typedef struct {
    List Bangunan1;
    Queue Skill1;
    List Bangunan2;
    Queue Skill2;
} ElTypeStack;
typedef struct {
    ElTypeStack T[MaxEl + 1]; // tabel penyimpan elemen
    AddressStack Top;         // alamat Top: elemen puncak
} Stack;
// Definisi stack S kosong : S.Top = Nil
// Indeks T yang dipakai [1..MaxElStack]

/*** Selektor Stack ***/
#define Top(S) (S).Top
#define InfoTop(S) (S).T[(S).Top]
/*** Selektor ElTypeStack ***/
#define B1(E) (E).Bangunan1
#define S1(E) (E).Skill1
#define B2(E) (E).Bangunan2
#define S2(E) (E).Skill2

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
void MakeEmptyStack (Stack *S);
/* I.S. S sembarang; */
/* F.S. Terbentuk Stack S kosong (Top bernilai NilStack) dengan kapasitas MaxElStack */

/*** Kelompok tes Stack kosong / penuh ***/
boolean IsStackEmpty (Stack S);
/* Mengembalikan true jika Stack S kosong */
boolean IsStackFull (Stack S);
/* Mengembalikan true jika Stack S penuh */

/*** Kelompok Add dan Del elemen ***/
void Push (Stack * S, ElTypeStack X);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, tetapi tidak penuh */
/* F.S. X menjadi Top yang baru, Top bertambah 1 */

void Pop (Stack * S, ElTypeStack * X);
/* Menghapus X dari Stack S */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen Top terakhir sebelum dihapus, Top berkurang 1 */

/*** Kelompok fungsi pembantu ***/
ElTypeStack MakeElTypeStack (List L1, Queue Q1, List L2, Queue Q2);
/* Membentuk ElTypeStack dari komponen-komponennya */

void CopyElTypeStack (ElTypeStack * Eout, ElTypeStack Ein);
/* Melakukan penyalinan Ein ke Eout */
/* I.S. Ein terdefinisi, Eout sembarang */
/* F.S. Eout sama dengan Ein */

#endif // STACK_H
