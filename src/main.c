#include <stdio.h>
#include "header/array.h"
#include "header/bangunan.h"
#include "header/boolean.h"
#include "header/graph.h"
#include "header/kata.h"
#include "header/listlinier.h"
#include "header/matriks.h"
#include "header/mesinkar.h"
#include "header/mesinkata.h"
#include "header/pcolor.h"
#include "header/point.h"
#include "header/queue.h"
#include "header/stack.h"
#include "header/status.h"

int main() {
    int X, error;
    /* KAMUS KATA */
    Kata K;

    InitGameStatus(105, 105, 35);
    printf("Initializing GameStatus...\n");
    SetupConfigGameStatus("../data/config.txt", &error);
    printf("Initialization done...\n");

    ScanKata(&K);
    TulisKata(K);
    ScanKata(&K);
    TulisKata(K);

    // boolean finish = false;
    // while (!finish) {
    //     for (int i=1;i<=NBangunan(GameStatus);i++) {
    //         TambahPasukan(&ElmtTab(T(GameStatus), i), ActivePlayer(GameStatus));
    //     }
    //     ScanKata(&K);
    //     TulisKata(K);
    //     printf("\n");
    //     TulisMatriksPeta(Peta(GameStatus), T(GameStatus)); printf("\n");
    //     finish = 1;
    // }
    //
    // // Test MakeKata
    // CopyKata(&K, MakeKata("Ahahaha\n"));
    // TulisKata(K);

    return 0;
}
