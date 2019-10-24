#include <stdio.h>
#include "../header/stack.h"

/*** Konstruktor ***/
void MakeEmptyStack (Stack *S) {
/* I.S. S sembarang; */
/* F.S. Terbentuk Stack S kosong (Top bernilai NilStack) dengan kapasitas MaxElStack */
    Top(*S) = NilStack;
}

/*** Kelompok tes Stack kosong / penuh ***/
boolean IsStackEmpty (Stack S) {
/* Mengembalikan true jika Stack S kosong */
    return (Top(S) == NilStack);
}
boolean IsStackFull (Stack S) {
/* Mengembalikan true jika Stack S penuh */
    return (Top(S) == MaxElStack);
}

/*** Kelompok Add dan Del elemen ***/
void Push (Stack * S, ElTypeStack X) {
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, tetapi tidak penuh */
/* F.S. X menjadi Top yang baru, Top bertambah 1 */
    // Algoritma
    Top(*S)++;
    CopyElTypeStack(&InfoTop(*S), X);
}

void Pop (Stack * S, ElTypeStack * X) {
/* Menghapus X dari Stack S */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen Top terakhir sebelum dihapus, Top berkurang 1 */
    // Algoritma
    CopyElTypeStack(X, InfoTop(*S));
    Top(*S)--;
}

/*** Kelompok fungsi pembantu ***/
ElTypeStack MakeElTypeStack (TabBangunan T, Queue Q1, Queue Q2) {
/* Membentuk ElTypeStack dari komponen-komponennya */
    // Kamus lokal
    ElTypeStack E;
    // Algoritma
    CopyTabBangunan(&TB(E), T);
    CopyQueue(&S1(E), Q1);
    CopyQueue(&S2(E), Q2);
    return (E);
}

void CopyElTypeStack (ElTypeStack * Eout, ElTypeStack Ein) {
/* Melakukan penyalinan Ein ke Eout */
/* I.S. Ein terdefinisi, Eout sembarang */
/* F.S. Eout sama dengan Ein */
    // Algoritma
    CopyTabBangunan(&TB(*Eout), TB(Ein));
    CopyQueue(&S1(*Eout), S1(Ein));
    CopyQueue(&S2(*Eout), S2(Ein));
}
