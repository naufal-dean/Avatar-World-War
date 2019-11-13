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
                counter = 0;
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
                printf("Bangunan yang digunakan untuk menyerang: ");
                int attackBuilding;
                scanf("%d", &attackBuilding);
                if (attackBuilding <= 0 || attackBuilding > counter) {
                    printf("Bro... Das not your building\n");
                    continue;
                }
                counter = 0;
                // mencari id dari attackBuilding
                for (int i = 1; i <= NBangunan(GameStatus); i++) {
                    if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
                        counter++;
                        if (counter == attackBuilding) {
                            attackBuilding = i;
                            break;
                        }
                    }
                }
                if (SudahSerang(ElmtTab(T(GameStatus), attackBuilding))) {
                    printf("This building is busy. The attack could not commence.\n");
                    continue;
                }

                printf("Daftar bangunan yang dapat diserang: \n");
                counter = 0;
                for (int i = 1; i <= NBangunan(GameStatus); i++) {
                    if ((Pemilik(ElmtTab(T(GameStatus), i)) != ActivePlayer(GameStatus)) && (AdaEdge(Adjacency(GameStatus), attackBuilding, i))) {
                        counter++;
                        printf("%d. ", counter);
                        TulisBangunan(ElmtTab(T(GameStatus), i));
                        printf("\n");
                    }
                }
                printf("Bangunan yang diserang: ");
                int defendBuilding;
                scanf("%d", &defendBuilding);
                if (defendBuilding <= 0 || defendBuilding > counter) {
                    printf("Um wat?\n");
                    continue;
                }
                counter = 0;
                // mencari id dari defendBuilding
                for (int i = 1; i <= NBangunan(GameStatus); i++) {
                    if ((Pemilik(ElmtTab(T(GameStatus), i)) != ActivePlayer(GameStatus)) && (AdaEdge(Adjacency(GameStatus), attackBuilding, i))) {
                        counter++;
                        if (counter == defendBuilding) {
                            defendBuilding = i;
                            break;
                        }
                    }
                }

                // attacking
                printf("Jumlah pasukan: ");
                int usedTroops;
                scanf("%d", &usedTroops);
                if (usedTroops > Pasukan(ElmtTab(T(GameStatus), attackBuilding))) {
                    printf("You don't have that many troops, do you?\n");
                    continue;
                }
                SudahSerang(ElmtTab(T(GameStatus), attackBuilding)) = true;
                Pasukan(ElmtTab(T(GameStatus), attackBuilding)) -= usedTroops;

                // various attack modifiers
                if (Pertahanan(ElmtTab(T(GameStatus), defendBuilding))) {
                    // "When in doubt, bruteforce." - Thomas Alfa Edison
                    for (int i = 1; i <= usedTroops; i++) {
                        if (i*3/4 >= Pasukan(ElmtTab(T(GameStatus), defendBuilding))) {
                            usedTroops -= i*3/4;
                            Pasukan(ElmtTab(T(GameStatus), defendBuilding)) = usedTroops;
                            usedTroops = 0;
                            Pemilik(ElmtTab(T(GameStatus), defendBuilding)) = ActivePlayer(GameStatus);
                            printf("Overcoming the defenses, this building is now yours!\n");
                            break;
                        }
                    }
                    // if max troops can't kill (usedTroops == 0 if succeded before)
                    if (usedTroops > 0) printf("F. Their deaths are not in vain. The walls are thicc.\n");
                    Pasukan(ElmtTab(T(GameStatus), defendBuilding)) -= usedTroops*3/4;
                    usedTroops = 0;
                } else /* No modifier */ {
                    Pasukan(ElmtTab(T(GameStatus), defendBuilding)) -= usedTroops;
                    usedTroops = 0;
                    if (Pasukan(ElmtTab(T(GameStatus), defendBuilding)) <= 0) /* Success */ {
                        Pasukan(ElmtTab(T(GameStatus), defendBuilding)) *= -1;
                        Pemilik(ElmtTab(T(GameStatus), defendBuilding)) = ActivePlayer(GameStatus);
                        printf("This building is now yours!\n");
                    } else {
                        printf("F. Their deaths are in vain.\n");
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
            } else if (EQKata(command, MakeKata("BUILDINGS\n"))) {
                for (int i = 1; i <= NBangunan(GameStatus); i++) {
                    printf("%d. ", i);
                    TulisBangunan(ElmtTab(T(GameStatus), i));
                    printf(" ");
                    if (Pemilik(ElmtTab(T(GameStatus), i)) == 0) {
                        print_yellow('N');  // neutral
                    } else if (Pemilik(ElmtTab(T(GameStatus), i)) == 1) {
                        print_green('R');   // radiant
                    } else {
                        print_red('D');     // dire
                    }
                    printf("\n");
                }
            } else {
                printf("Wrong Command! Type HELP for help.\n");
            }
        }
    }
    return 0;
}
