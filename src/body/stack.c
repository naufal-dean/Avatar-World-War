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
ElTypeStack MakeElTypeStack (TabBangunan T, int S1[], int S2[]) {
/* Membentuk ElTypeStack dari komponen-komponennya */
    // Kamus lokal
    ElTypeStack E;
    // Algoritma
    CopyTabBangunan(&TB(E), T);
    CopyTabSkill(&TS1(E), S1);
    CopyTabSkill(&TS2(E), S2);
    return (E);
}

void CopyElTypeStack (ElTypeStack * Eout, ElTypeStack Ein) {
/* Melakukan penyalinan Ein ke Eout */
/* I.S. Ein terdefinisi, Eout sembarang */
/* F.S. Eout sama dengan Ein */
    // Algoritma
    CopyTabBangunan(&TB(*Eout), TB(Ein));
    CopyTabSkill(&TS1(*Eout), TS1(Ein));
    CopyTabSkill(&TS2(*Eout), TS2(Ein));
}

/*** Kelompok fungsi pembantu tab skill ***/
void MakeEmptyTabSkill(TabSkill * S) {
/* I.S. S sembarang */
/* F.S. Terbentuk tabel S kosong dengan elemen bernilai 0 */
/* Proses: Inisialisasi semua elemen S dengan 0 */
    // Kamus lokal
    int i;
    // Algoritma
    for (i = 1; i <= MaxElTabSkill; i++) {
        (*S)[i] = 0;
    }
}
void CopyTabSkill(TabSkill * Sout, TabSkill Sin) {
/* Melakukan penyalinan Sin ke Sout */
/* I.S. Sin terdefinisi, Sout sembarang */
/* F.S. Sout sama dengan Sin */
    // Kamus lokal
    int i;
    // Algoritma
    for (i = 1; i <= MaxElTabSkill; i++) {
        (*Sout)[i] = Sin[i];
    }
}
