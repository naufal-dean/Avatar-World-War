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
        // add troops to owned buildings
        for (int i=1;i<=NBangunan(GameStatus);i++) {
            TambahPasukan(&ElmtTab(T(GameStatus), i), ActivePlayer(GameStatus));
        }

        // active skills turn decay
        if (ActivePlayer(GameStatus) == 1) {
            SHIELD2(GameStatus)--;
            if (SHIELD2(GameStatus) < 0) SHIELD2(GameStatus) = 0;
        } else {
            SHIELD1(GameStatus)--;
            if (SHIELD1(GameStatus) < 0) SHIELD1(GameStatus) = 0;
        }

        boolean finishTurn = false;
        TabSkill TS;
        MakeEmptyTabSkill(&TS);
        printf("Current Turn #: %d\n", Turn(GameStatus));
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), TS, TS));
        while (!finishTurn) {
            printf("========================\n");
            Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus)));

            if (ActivePlayer(GameStatus) == 1) {
                printf("Player 1's Turn\n");
                if (IsQueueEmpty(Q1(GameStatus))) {
                    printf("You currently have no skills available.\n");
                } else {
                    printf("Current skill: ");
                    if (InfoHead(Q1(GameStatus)) == 1) printf("IU\n");
                    else if (InfoHead(Q1(GameStatus)) == 2) printf("S\n");
                    else if (InfoHead(Q1(GameStatus)) == 3) printf("ET\n");
                    else if (InfoHead(Q1(GameStatus)) == 4) printf("AU\n");
                    else if (InfoHead(Q1(GameStatus)) == 5) printf("CH\n");
                    else if (InfoHead(Q1(GameStatus)) == 6) printf("IR\n");
                    else if (InfoHead(Q1(GameStatus)) == 7) printf("B\n");
                }
            }
            else {
                if (IsQueueEmpty(Q2(GameStatus))) {
                    printf("You currently have no skills available.\n");
                } else {
                    printf("Player 2's Turn\n");
                    printf("Current skill: ");
                    if (InfoHead(Q2(GameStatus)) == 1) printf("IU\n");
                    else if (InfoHead(Q2(GameStatus)) == 2) printf("S\n");
                    else if (InfoHead(Q2(GameStatus)) == 3) printf("ET\n");
                    else if (InfoHead(Q2(GameStatus)) == 4) printf("AU\n");
                    else if (InfoHead(Q2(GameStatus)) == 5) printf("CH\n");
                    else if (InfoHead(Q2(GameStatus)) == 6) printf("IR\n");
                    else if (InfoHead(Q2(GameStatus)) == 7) printf("B\n");
                }
            }

            TulisMatriksPeta(Peta(GameStatus), T(GameStatus)); printf("\n");

            PrintTabSkill(S1(GameStatus)); PrintTabSkill(S2(GameStatus)); // debug

            Kata command;
            boolean berhasil = false;
            ElTypeStack tmp;
            printf("Your command: ");
            ScanKata(&command);

            if (EQKata(command, MakeKata("ATTACK\n")) || EQKata(command, MakeKata("A\n"))) {
                berhasil = AttackCommand();
            } else if (EQKata(command, MakeKata("LEVEL_UP\n")) || EQKata(command, MakeKata("Q\n"))) {
                berhasil = LevelUpCommand();
            } else if (EQKata(command, MakeKata("SKILL\n")) || EQKata(command, MakeKata("S\n"))) {
                berhasil = SkillCommand();
            } else if (EQKata(command, MakeKata("UNDO\n")) || EQKata(command, MakeKata("D\n"))) {
                Pop(&StatusPemain(GameStatus), &tmp);
                berhasil = UndoCommand();
            } else if (EQKata(command, MakeKata("END_TURN\n")) || EQKata(command, MakeKata("E\n"))) {
                berhasil = EndTurnCommand();
                finishTurn = true;
            } else if (EQKata(command, MakeKata("SAVE\n"))) {
                SaveCommand();
            } else if (EQKata(command, MakeKata("LOAD\n"))) {
                LoadCommand();
            } else if (EQKata(command, MakeKata("MOVE\n"))) {
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
