#include <stdio.h>
#include "matriks.h"

/*  DEFINISI PROTOTIPE PRIMITIF  */
/*** Konstruktor ***/
void MakeMatriks (int NB, int NK, Matriks *M) {
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
    //Algoritma
    NBrsEff(*M)=NB;
    NKolEff(*M)=NK;
}

/*** Selektor ***/
boolean IsIdxMatriksValid (int i, int j) {
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
    return(i>=IdxBrsMin && i<=IdxBrsMax && j>=IdxKolMin && j<=IdxKolMax);
}
indeks GetFirstIdxBrs (Matriks M) {
/* Mengirimkan indeks baris terkecil M */
    return IdxBrsMin;
}
indeks GetFirstIdxKol (Matriks M) {
/* Mengirimkan indeks kolom terkecil M */
    return IdxKolMin;
}
indeks GetLastIdxBrs (Matriks M) {
/* Mengirimkan indeks baris terbesar M */
    return(NBrsEff(M));
}
indeks GetLastIdxKol (Matriks M) {
/* Mengirimkan indeks kolom terbesar M */
    return(NKolEff(M));
}
boolean IsIdxMatriksEff (Matriks M, indeks i, indeks j) {
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
    return(i>=GetFirstIdxBrs(M) && j>=GetFirstIdxKol(M) && i<=GetLastIdxBrs(M) && j<=GetLastIdxKol(M));
}

/* KELOMPOK BACA/TULIS */
void BacaUkuranMatriks (Matriks * M) {
/* I.S. Matriks Matriks belum memiliki ukuran */
/* F.S. Ukuran matriks terdefinisi dan valid */
/* Matriks yang valid berukuran 10<=NB<=20 dan 10<=NK<=30 */
    // Kamus lokal
    int NB, NK;
    // Algoritma
    printf("Masukkan ukuran matriks (baris x kolom)\n");
    scanf("%d %d",&NB,&NK);
    while(!IsIdxMatriksValid(NB,NK)){
        scanf("%d %d",NB,NK);
    }
    MakeMatriks(NB, NK, M);
}
void TulisMatriksPeta (Matriks M, TabBangunan T){
/* I.S. M terdefinisi */
/* F.S. Menuliskan matriks sesuai dengan lokasi bangunan  */
/* Contoh: Menuliskan matriks berukuran 5x5
    #######
    #     #
    #     #
    #     #
    #     #
    #     #
    #######
*/
    // Kamus lokal
    int i, j;
    // Algoritma
    for (i = GetFirstIdxKol(M) - 1; i <= GetLastIdxKol(M) + 1; i++) {
        printf("#");
    }
    printf("\n");
    for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++) {
        printf("#");
        for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++) {
            if (ElmtMatriks(M, i, j) != 0) {
                if (Pemilik(ElmtTab(T, ElmtMatriks(M, i, j))) == 1) {
                    print_green(Tipe(ElmtTab(T, ElmtMatriks(M, i, j))));
                } else if (Pemilik(ElmtTab(T, ElmtMatriks(M, i, j))) == 2) {
                    print_red(Tipe(ElmtTab(T, ElmtMatriks(M, i, j))));
                } else {
                    print_yellow(Tipe(ElmtTab(T, ElmtMatriks(M, i, j))));
                }
            } else {
                printf(" ");
            }
        }
        printf("#\n");
    }
    for (i = GetFirstIdxKol(M) - 1; i <= GetLastIdxKol(M) + 1; i++) {
        printf("#");
    }
}
