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
        TabSkill TS;
        MakeEmptyTabSkill(&TS);
        printf("Current Turn #: %d\n", Turn(GameStatus));
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), TS, TS));
        while (!finishTurn) {
            printf("========================\n");
            Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus)));

            if (ActivePlayer(GameStatus) == 1) printf("Player 1's Turn\n");
            else printf("Player 2's Turn\n");

            TulisMatriksPeta(Peta(GameStatus), T(GameStatus)); printf("\n");

            Kata command;
            boolean berhasil = false;
            ElTypeStack tmp;
            printf("Your command: ");
            ScanKata(&command);
            PrintTabSkill(S1(GameStatus)); PrintTabSkill(S2(GameStatus));

            if (EQKata(command, MakeKata("ATTACK\n")) || EQKata(command, MakeKata("A\n"))) {
                berhasil = AttackCommand();
            } else if (EQKata(command, MakeKata("LEVEL_UP\n")) || EQKata(command, MakeKata("Q\n"))) {
                berhasil = LevelUpCommand();
            } else if (EQKata(command, MakeKata("SKILL\n")) || EQKata(command, MakeKata("S\n"))) {

            } else if (EQKata(command, MakeKata("UNDO\n")) || EQKata(command, MakeKata("D\n"))) {
                Pop(&StatusPemain(GameStatus), &tmp);
                berhasil = UndoCommand();
            } else if (EQKata(command, MakeKata("END_TURN\n")) || EQKata(command, MakeKata("E\n"))) {
                berhasil = EndTurnCommand();
                finishTurn = true;
            } else if (EQKata(command, MakeKata("SAVE\n")) || EQKata(command, MakeKata("V\n"))) {

            } else if (EQKata(command, MakeKata("MOVE\n")) || EQKata(command, MakeKata("W\n"))) {
                berhasil = MoveCommand();
            } else if (EQKata(command, MakeKata("EXIT\n")) || EQKata(command, MakeKata("P\n"))) {
                printf("Babai :)\n");
                exit(0);
            } else if (EQKata(command, MakeKata("HELP\n")) || EQKata(command, MakeKata("H\n"))) {
                HelpCommand();
            } else if (EQKata(command, MakeKata("BUILDINGS\n")) || EQKata(command, MakeKata("B\n"))) {
                BuildingsCommand();
            } else {
                printf("Wrong Command! Type HELP for help.\n");
            }

            if (!berhasil) {
                Pop(&StatusPemain(GameStatus), &tmp);
            }
        }
    }
    return 0;
}
