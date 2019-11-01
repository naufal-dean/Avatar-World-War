#include <stdio.h>
#include "../header/status.h"

Status GameStatus;

/*** Konstruktor ***/
void InitGameStatus (int NBMatriks, int NKMatriks, int MaxElTab) {
/* I.S. GameStatus sembarang */
/* F.S. Status GameStatus terdefinisi */
/* Proses: Melakukan alokasi, memanfaatkan konstruktor tiap komponen Status.
           ActivePlayer = 1. Turn = 1. */
    // Algoritma
    MakeMatriks(NBMatriks, NKMatriks, &Peta(GameStatus));
    MakeEmptyStack(&StatusPemain(GameStatus));
    ActivePlayer(GameStatus) = 1;
    Turn(GameStatus) = 1;
}

/*** Setup ***/
void SetupConfigGameStatus(char * ConfigPath, int * error) {
/* I.S. GameStatus terdefinisi
        Isi file config terdefinisi, jumlah bangunan > 2, ukuran map valid */
/* F.S. Isi GameStatus sesuai dengan config */
/* Proses: Melakukan setup GameStatus sesuai isi file di ConfigPath */
    // Kamus lokal
    int NBPeta, NKPeta, NBangunan, i, j, X, Y;
    TabBangunan T;
    Queue Q1, Q2;
    Graph G;
    // Algoritma
    // Inisialisasi mesin kata
    STARTKATA(ConfigPath, error);
    if ((*error) != 0) {
        return;
    }
    
    // Ukuran peta
    NBPeta = KataToInt(CKata);
    ADVKATA();
    NKPeta = KataToInt(CKata);
    ReadNextLine();
    // Jumlah bangunan
    NBangunan = KataToInt(CKata);
    ReadNextLine();
    // Inisialisasi GameStatus
    InitGameStatus(NBPeta, NKPeta, NBangunan);
    // Read bangunan
    MakeEmptyTab(&T, NBangunan);
    for (i = 1; i <= NBangunan; i++) {
        CopyBangunan(&ElmtTab(T, i), ParseInputBangunan(i));
        ReadNextLine();
    }
    Pemilik(ElmtTab(T, 1)) = 1;
    Pemilik(ElmtTab(T, 2)) = 2;
    // Assign ID bangunan ke Peta(GameStatus)
    for (i = 1; i <= NBPeta; i++) {
        for (j = 1; j <= NKPeta; j++) {
            ElmtMatriks(Peta(GameStatus), i, j) = 0;
        }
    }

    for (i = 1; i <= NBangunan; i++) {
        X = Absis(Lokasi(ElmtTab(T, i)));
        Y = Ordinat(Lokasi(ElmtTab(T, i)));
        ElmtMatriks(Peta(GameStatus), X, Y) = i;
    }

    // Inisialisasi Queue Skill
    MakeEmptyQueue(&Q1, 10);
    AddElQueue(&Q1, INSTANT_UPGRADE);
    MakeEmptyQueue(&Q2, 10);
    AddElQueue(&Q2, INSTANT_UPGRADE);

    // Assign T, Q1, Q2 to StatusPemain(GameStatus)
    Push(&StatusPemain(GameStatus), MakeElTypeStack(T, Q1, Q2));

    // Adjacency matriks
    CreateEmptyGraph(&G);
    for (int i=1;i<=NBangunan;i++) {
        InsertGraph(&G, i, 0);
    }
    
    for (int i=1;i<=NBangunan;i++) {
        for (int j=1;j<=NBangunan;j++) {
            if (KataToInt(CKata) == 1) InsertGraph(&G, i, j);
            ADVKATA();
        }
        ReadNextLine();
    }
}

Bangunan ParseInputBangunan(int ID) {
/* Mengembalikan Bangunan sesuai input pada file
   Format input: "Tipe Lokasi(X) Lokasi(Y)"
   CKata awal ada di Tipe, CKata akhir ada di Lokasi(Y) */
    // Kamus lokal
    char Tipe;
    int X, Y;
    // Algoritma
    // Tipe
    Tipe = Char(CKata, 1);
    ADVKATA();
    // Lokasi
    X = KataToInt(CKata);
    ADVKATA();
    Y = KataToInt(CKata);

    return(MakeBangunan(ID, Tipe, MakePoint(X, Y)));
}
