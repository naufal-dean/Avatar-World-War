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

#include "console.h"

int main() {
    int X, error, counter;
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
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), Q1(GameStatus), Q2(GameStatus)));
        while (!finishTurn) {
            printf("========================\n");
            if (ActivePlayer(GameStatus) == 1) printf("Player 1's Turn\n");
            else printf("Player 2's Turn\n");
            TulisMatriksPeta(Peta(GameStatus), T(GameStatus)); printf("\n");
            printf("Your command: ");
            Kata command;
            boolean berhasil = false;
            ScanKata(&command);
            if (EQKata(command, MakeKata("ATTACK\n"))) {
                berhasil = AttackCommand();
            } else if (EQKata(command, MakeKata("LEVEL_UP\n"))) {
                berhasil = LevelUpCommand();
            } else if (EQKata(command, MakeKata("SKILL\n"))) {

            } else if (EQKata(command, MakeKata("UNDO\n"))) {
                berhasil = UndoCommand();
            } else if (EQKata(command, MakeKata("END_TURN\n"))) {
                berhasil = EndTurnCommand();
                finishTurn = true;
            } else if (EQKata(command, MakeKata("SAVE\n"))) {

            } else if (EQKata(command, MakeKata("MOVE\n"))) {
                berhasil = MoveCommand();
            } else if (EQKata(command, MakeKata("EXIT\n"))) {
                printf("Babai :)\n");
                exit(0);
            } else if (EQKata(command, MakeKata("HELP\n"))) {
                HelpCommand();
            } else if (EQKata(command, MakeKata("BUILDINGS\n"))) {
                BuildingsCommand();
            } else {
                printf("Wrong Command! Type HELP for help.\n");
            }
            if (berhasil) Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), Q1(GameStatus), Q2(GameStatus)));
        }
    }
    return 0;
}
