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

    boolean finishGame = false;
    while (!finishGame) {
        for (int i=1;i<=NBangunan(GameStatus);i++) {
            TambahPasukan(&ElmtTab(T(GameStatus), i), ActivePlayer(GameStatus));
        }
        boolean finishTurn = false;
        while (!finishTurn) {
            printf("========================\n");
            if (ActivePlayer(GameStatus) == 1) printf("Player 1's Turn\n");
            else printf("Player 2's Turn\n");
            TulisMatriksPeta(Peta(GameStatus), T(GameStatus));
            printf("\n");
            printf("Your command: ");
            Kata command;
            ScanKata(&command);
            TulisKata(command);
            printf("\n");
            if (EQKata(command, MakeKata("ATTACK\n"))) {

            } else if (EQKata(command, MakeKata("LEVEL_UP\n"))) {

            } else if (EQKata(command, MakeKata("SKILL\n"))) {
                
            } else if (EQKata(command, MakeKata("UNDO\n"))) {
                
            } else if (EQKata(command, MakeKata("END_TURN\n"))) {
                printf("Player change!\n");
                ActivePlayer(GameStatus) = 3 - ActivePlayer(GameStatus);
                if (ActivePlayer(GameStatus) == 1) Turn(GameStatus)++;
                finishTurn = true;
            } else if (EQKata(command, MakeKata("SAVE\n"))) {
                
            } else if (EQKata(command, MakeKata("MOVE\n"))) {
                
            } else if (EQKata(command, MakeKata("EXIT\n"))) {
                printf("Babai :)\n");
                exit(0);
            }
            TulisKata(command);
            printf("\n");
        }
        // finishGame = true;
    }
    return 0;
}
