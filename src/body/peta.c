#include "../header/peta.h"
#include <stdio.h>

/*  DEFINISI PROTOTIPE PRIMITIF  */
/*** Konstruktor ***/
void MakePeta (int NB, int NK, Peta *M) {
/* I.S. NB dan NK adalah valid untuk memori peta yang dibuat */
/* F.S. Peta M sesuai dengan definisi di atas terbentuk */
    // Kamus lokal

    //Algoritma
    NBrsEff(*M)=NB;
    NKolEff(*M)=NK;
}

/*** Selektor ***/
boolean IsIdxValid (int i, int j) {
/* Mengirimkan true jika i, j adalah indeks yang valid untuk peta apa pun */
    return(i>=BrsMin && i<=BrsMax && j>=KolMin && j<=KolMax);
}
indeks GetFirstIdxBrs (Peta M) {
/* Mengirimkan indeks baris terkecil M */
    return BrsMin;
}
indeks GetFirstIdxKol (Peta M) {
/* Mengirimkan indeks kolom terkecil M */
    return KolMin;
}
indeks GetLastIdxBrs (Peta M) {
/* Mengirimkan indeks baris terbesar M */
    return(NBrsEff(M));
}
indeks GetLastIdxKol (Peta M) {
/* Mengirimkan indeks kolom terbesar M */
    return(NKolEff(M));
}
boolean IsIdxEff (Peta M, indeks i, indeks j) {
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
    return(i>=GetFirstIdxBrs(M) && j>=GetFirstIdxKol(M) && i<=GetLastIdxBrs(M) && j<=GetLastIdxKol(M));
}

/* KELOMPOK BACA/TULIS */
void BacaUkuranPeta (Peta * M) {
/* I.S. Peta belum memiliki ukuran */
/* F.S. Ukuran peta terdefinisi dan valid */
/* Peta yang valid berukuran 10<=NB<=20 dan 10<=NK<=30 */
    // Kamus lokal
    int NB, NK;
    // Algoritma
    printf("Masukkan ukuran peta (baris x kolom)\n");
    scanf("%d %d",&NB,&NK);
    while(!IsIdxValid(NB,NK)){
        scanf("%d %d",NB,NK);
    }
    MakePeta(NB, NK, M);
}
void TulisPeta (Peta M){
/* I.S. M terdefinisi */
/* F.S. Menuliskan peta sesuai dengan kondisi bangunan yang ada */
/* Contoh: Menuliskan peta berukuran 5x5
    * * * * * * *
    *           *
    *           *
    *           *
    *           *
    *           *
    * * * * * * *
*/ 
    // Kamus lokal
    indeks i,j;
    int ctr;
    // Algoritma
    ctr=1;
    for(i=GetFirstIdxBrs(M)-1; i<=GetLastIdxBrs(M)+1; i++){
        for(j=GetFirstIdxKol(M)+1; j<=GetLastIdxKol(M)+1; j++){
            if(i==GetFirstIdxBrs(M)-1 || i==GetLastIdxBrs(M)+1){
                if(j==GetLastIdxKol(M)+1){
                    printf("*\n");
                }
                else{
                    printf("* ");
                }
            }
            else{
                if(j==GetFirstIdxKol(M)-1){
                    printf("* ");
                }
                else{
                    printf("%d ",ctr);
                    ctr++;
                }
            }
        }
    }
}

