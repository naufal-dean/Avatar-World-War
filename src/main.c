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
        printf("Current Turn #: %d\n", Turn(GameStatus));
        while (!finishTurn) {
            printf("========================\n");
            if (ActivePlayer(GameStatus) == 1) printf("Player 1's Turn\n");
            else printf("Player 2's Turn\n");
            TulisMatriksPeta(Peta(GameStatus), T(GameStatus));
            printf("\n");
            printf("Your command: ");
            Kata command;
            ScanKata(&command);
            if (EQKata(command, MakeKata("ATTACK\n"))) {
                printf("Daftar bangunan:\n");
                int counter = 0;
                for (int i = 1; i <= NBangunan(GameStatus); i++) {
                    if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
                        counter++;
                        printf("%d. ", counter);
                        TulisBangunan(ElmtTab(T(GameStatus), i));
                        if (SudahSerang(ElmtTab(T(GameStatus), i))) printf(" BUSY");
                        else printf(" AVAILABLE");
                        printf("\n");
                    }
                }
            } else if (EQKata(command, MakeKata("LEVEL_UP\n"))) {

            } else if (EQKata(command, MakeKata("SKILL\n"))) {

            } else if (EQKata(command, MakeKata("UNDO\n"))) {

            } else if (EQKata(command, MakeKata("END_TURN\n"))) {
                printf("Player change!\n");
                // reset status bangunan
                for (int i = 1; i <= NBangunan(GameStatus); i++) {
                    SudahSerang(ElmtTab(T(GameStatus), i)) = false;
                }
                // mengubah 1 -> 2, 2 -> 1
                ActivePlayer(GameStatus) = 3 - ActivePlayer(GameStatus);
                // menambah turn number
                if (ActivePlayer(GameStatus) == 1) Turn(GameStatus)++;
                // mengakhiri turn
                finishTurn = true;
            } else if (EQKata(command, MakeKata("SAVE\n"))) {

            } else if (EQKata(command, MakeKata("MOVE\n"))) {

            } else if (EQKata(command, MakeKata("EXIT\n"))) {
                printf("Babai :)\n");
                exit(0);
            } else if (EQKata(command, MakeKata("HELP\n"))) {
                // Isiin dong siapapun males gua
            } else {
                printf("Wrong Command! Type HELP for help.\n");
            }
        }
    }
    return 0;
}
