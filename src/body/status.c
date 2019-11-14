#include <stdio.h>
#include "../header/status.h"

Status GameStatus;

/*** Konstruktor ***/
void InitGameStatus (int NBPeta, int NKPeta, int NBangunan) {
/* I.S. GameStatus sembarang */
/* F.S. Status GameStatus terdefinisi */
/* Proses: Melakukan alokasi, memanfaatkan konstruktor tiap komponen Status.
           ActivePlayer = 1. Turn = 1. */
    // Algoritma
    MakeMatriks(NBPeta, NKPeta, &Peta(GameStatus));
    MakeEmptyGraph(&Adjacency(GameStatus));
    MakeEmptyStack(&StatusPemain(GameStatus));
    MakeEmptyTabSkill(&S1(GameStatus));
    MakeEmptyTabSkill(&S2(GameStatus));
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
    int i, j, X, Y;
    Graph G;
    // Algoritma
    // Inisialisasi mesin kata
    STARTKATA(ConfigPath, error);
    if ((*error) != 0) {
        return;
    }

    // Ukuran peta
    NBPeta(GameStatus) = KataToInt(CKata);
    ADVKATA();
    NKPeta(GameStatus) = KataToInt(CKata);
    ReadNextLine();
    // Jumlah bangunan
    NBangunan(GameStatus) = KataToInt(CKata);
    ReadNextLine();
    // Inisialisasi GameStatus
    InitGameStatus(NBPeta(GameStatus), NKPeta(GameStatus), NBangunan(GameStatus));
    // Read bangunan
    MakeEmptyTab(&T(GameStatus), NBangunan(GameStatus));
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        CopyBangunan(&ElmtTab(T(GameStatus), i), ParseInputBangunan(i));
        ReadNextLine();
    }
    Pemilik(ElmtTab(T(GameStatus), 1)) = 1;
    Pemilik(ElmtTab(T(GameStatus), 2)) = 2;
    // Assign ID bangunan ke Peta(GameStatus)
    for (i = 1; i <= NBPeta(GameStatus); i++) {
        for (j = 1; j <= NKPeta(GameStatus); j++) {
            ElmtMatriks(Peta(GameStatus), i, j) = 0;
        }
    }

    for (i = 1; i <= NBangunan(GameStatus); i++) {
        X = Absis(Lokasi(ElmtTab(T(GameStatus), i)));
        Y = Ordinat(Lokasi(ElmtTab(T(GameStatus), i)));
        ElmtMatriks(Peta(GameStatus), X, Y) = i;
    }

    // Inisialisasi Queue Skill
    MakeEmptyQueue(&Q1(GameStatus), 10);
    AddElQueue(&Q1(GameStatus), INSTANT_UPGRADE);
    MakeEmptyQueue(&Q2(GameStatus), 10);
    AddElQueue(&Q2(GameStatus), INSTANT_UPGRADE);

    // Adjacency matriks
    MakeEmptyGraph(&G);
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        for (j = 1; j < NBangunan(GameStatus); j++) {
            if (KataToInt(CKata) == 1)
              InsertElGraph(&G, i, j);
            ADVKATA();
        }
        if (KataToInt(CKata) == 1)
          InsertElGraph(&G, i, j);
        ReadNextLine();
    }
    // Assign Graph G ke Adjacency(GameStatus)
    CopyGraph(&Adjacency(GameStatus), G);
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
