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
        Isi file config terdefinisi, jumlah bangunan >= 2, ukuran map valid */
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

/*** Save dan Load Game ***/
void SaveGameStatus(char * SavePath) {
/* I.S. GameStatus terdefinisi */
/* F.S. Isi GameStatus tersimpan dalam file di SavePath */
/* Proses:  Melakukan penulisan isi GameStatus ke file di GameStatus
            Tidak menyimpan status undo */
    // Kamus lokal
    FILE * file;
    Bangunan B;
    Queue Q;
    ElTypeQueue QX;
    int i, j;
    // Algoritma
    // Buka file
    file = fopen(SavePath, "w");

    // Print ukuran peta
    fprintf(file, "%d %d\n", NBPeta(GameStatus), NKPeta(GameStatus));

    // Print jumlah bangunan dan list bangunan
    fprintf(file, "%d\n", NBangunan(GameStatus));
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        B = ElmtTab(T(GameStatus), i);
        fprintf(file, "%c %d %d\n", Tipe(B), Absis(Lokasi(B)), Ordinat(Lokasi(B)));
    }

    // Print matriks adjacency
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        for (j = 1; j < NBangunan(GameStatus); j++) {
            if (AdaEdge(Adjacency(GameStatus), i, j)) {
                fprintf(file, "%d ", 1);
            } else {
                fprintf(file, "%d ", 0);
            }
        }
        if (AdaEdge(Adjacency(GameStatus), i, j)) {
            fprintf(file, "%d\n", 1);
        } else {
            fprintf(file, "%d\n", 0);
        }
    }

    // Print jumlah bangunan, kemudian status non default bangunan
    fprintf(file, "%d\n", NBangunan(GameStatus));
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        B = ElmtTab(T(GameStatus), i);
        fprintf(file, "%d %d %d %d\n", Pemilik(B), Level(B), Pasukan(B), SudahSerang(B));
    }

    // Print jumlah queue dan list skill 1
    CopyQueue(&Q, Q1(GameStatus));

    fprintf(file, "%d\n", NBElmtQueue(Q1(GameStatus)));
    if (NBElmtQueue(Q1(GameStatus)) == 0) {
        fprintf(file, "0\n");
    } else {
        for (i = 1; i < NBElmtQueue(Q1(GameStatus)); i++) {
            DelElQueue(&Q, &QX);
            fprintf(file, "%d ", QX);
        }
        DelElQueue(&Q, &QX);
        fprintf(file, "%d\n", QX);
    }

    // Print jumlah queue dan list skill 2
    CopyQueue(&Q, Q2(GameStatus));

    fprintf(file, "%d\n", NBElmtQueue(Q2(GameStatus)));
    if (NBElmtQueue(Q2(GameStatus)) == 0) {
        fprintf(file, "0\n");
    } else {
        for (i = 1; i < NBElmtQueue(Q2(GameStatus)); i++) {
            DelElQueue(&Q, &QX);
            fprintf(file, "%d ", QX);
        }
        DelElQueue(&Q, &QX);
        fprintf(file, "%d\n", QX);
    }

    // Print tab skill 1
    for (i = 1; i < MaxElTabSkill; i++) {
        fprintf(file, "%d ", ElmtS1(GameStatus, i));
    }
    fprintf(file, "%d\n", ElmtS1(GameStatus, i));

    // Print tab skill 2
    for (i = 1; i < MaxElTabSkill; i++) {
        fprintf(file, "%d ", ElmtS2(GameStatus, i));
    }
    fprintf(file, "%d\n", ElmtS2(GameStatus, i));

    // Print active player
    fprintf(file, "%d\n", ActivePlayer(GameStatus));
    // Print turn
    fprintf(file, "%d\n", Turn(GameStatus));

    // Tutup file
    fclose(file);
}

void LoadGameStatus(char * LoadPath, int * error) {
/* I.S. GameStatus terdefinisi
Isi file load terdefinisi, jumlah bangunan >= 2, ukuran map valid */
/* F.S. Isi GameStatus sesuai dengan load */
/* Proses:  Melakukan setup GameStatus sesuai isi file di LoadPath
Memanfaatkan prosedur SetupConfigGameStatus */
    // Kamus lokal
    int N, i;
    // Algoritma
    // Setup awal (dari ukuran peta sampai matriks adjacency)
    SetupConfigGameStatus(LoadPath, error);
    // Setup tambahan
    // Bangunan
    // Jumlah bangunan
    N = KataToInt(CKata);
    ReadNextLine();
    // Status bangunan
    for (i = 1; i <= N; i++) {
        // Pemilik
        Pemilik(ElmtTab(T(GameStatus), i)) = KataToInt(CKata);
        ADVKATA();
        // Level
        Level(ElmtTab(T(GameStatus), i)) = KataToInt(CKata);
        AssignProperti(&ElmtTab(T(GameStatus), i));
        ADVKATA();
        // Pasukan
        Pasukan(ElmtTab(T(GameStatus), i)) = KataToInt(CKata);
        ADVKATA();
        // SudahSerang
        SudahSerang(ElmtTab(T(GameStatus), i)) = KataToInt(CKata);
        ReadNextLine();
    }

    // Queue list 1
    // Jumlah skill
    N = KataToInt(CKata);
    ReadNextLine();
    // Reset skill default lalu assign skill hasil load
    MakeEmptyQueue(&Q1(GameStatus), 10);
    if (N > 0) {
        for (i = 1; i < N ; i++) {
            AddElQueue(&Q1(GameStatus), KataToInt(CKata));
            ADVKATA();
        }
        AddElQueue(&Q1(GameStatus), KataToInt(CKata));
    }
    ReadNextLine();

    // Queue list 2
    // Jumlah skill
    N = KataToInt(CKata);
    ReadNextLine();
    // Reset skill default lalu assign skill hasil load
    MakeEmptyQueue(&Q2(GameStatus), 10);
    if (N > 0) {
        for (i = 1; i < N ; i++) {
            AddElQueue(&Q2(GameStatus), KataToInt(CKata));
            ADVKATA();
        }
        AddElQueue(&Q2(GameStatus), KataToInt(CKata));
    }
    ReadNextLine();

    // Tab skill 1
    for (i = 1; i < MaxElTabSkill; i++) {
        ElmtS1(GameStatus, i) = KataToInt(CKata);
        ADVKATA();
    }
    ElmtS1(GameStatus, i) = KataToInt(CKata);
    ReadNextLine();
    // Tab skill 2
    for (i = 1; i < MaxElTabSkill; i++) {
        ElmtS2(GameStatus, i) = KataToInt(CKata);
        ADVKATA();
    }
    ElmtS2(GameStatus, i) = KataToInt(CKata);
    ReadNextLine();

    // Active player
    ActivePlayer(GameStatus) = KataToInt(CKata);
    ReadNextLine();
    // Turn
    Turn(GameStatus) = KataToInt(CKata);
    ReadNextLine();
}
