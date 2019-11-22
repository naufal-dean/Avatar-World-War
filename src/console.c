#include <stdio.h>
#include <stdlib.h>
#include "console.h"

/*** Fungsi main ***/
void AppExecute() {
    /* I.S. Kondisi sembarang */
    /* F.S. Game selesai, baik karena ada pemenang, command EXIT, maupun error config */
    /* Proses: Melakukan proses eksekusi game */
    // Kamus Lokal
    int X, error, counter, troops0, troops1, troops2, buildings0, buildings1, buildings2;
    Kata K;

    // Algoritma
    printf("%s", MAGENTA);
    printf("══════════════════════════════ %sLOADING%s ══════════════════════════════\n", NORMAL, MAGENTA);
    printf("%s                      Initializing GameStatus...                     %s\n\n", YELLOW, NORMAL);

    InitGameStatus(105, 105, 35);
    SetupConfigGameStatus("../data/config.txt", &error); printf("\n");

    if (error != 0) {
        printf("%s                Config file not found. Exiting game...               %s\n", RED, MAGENTA);
        printf("══════════════════════════════ %sFAILED%s ═══════════════════════════════\n", NORMAL, MAGENTA);
        printf("%s", NORMAL);
        return;
    }
    printf("%s                        Initialization done...                       %s\n", GREEN, MAGENTA);
    printf("══════════════════════════════ %sSUCCEED%s ══════════════════════════════\n\n\n", NORMAL, MAGENTA);
    printf("═══════════════════════════ %sGAME  STARTED%s ═══════════════════════════\n\n", NORMAL, MAGENTA);
    printf("%s", NORMAL);

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
        printf("                           Current Turn: %d                              \n", Turn(GameStatus));
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus), Q1(GameStatus), Q2(GameStatus)));
        while (!finishTurn) {
            // count troops & buildings per player
            troops0 = 0;
            troops1 = 0;
            troops2 = 0;
            buildings0 = 0;
            buildings1 = 0;
            buildings2 = 0;
            for (int i=1;i<=NBangunan(GameStatus);i++) {
                if (Pemilik(ElmtTab(T(GameStatus), i)) == 0) {
                    troops0 += Pasukan(ElmtTab(T(GameStatus), i));
                    buildings0++;
                }
                else if (Pemilik(ElmtTab(T(GameStatus), i)) == 1) {
                    troops1 += Pasukan(ElmtTab(T(GameStatus), i));
                    buildings1++;
                }
                else if (Pemilik(ElmtTab(T(GameStatus), i)) == 2) {
                    troops2 += Pasukan(ElmtTab(T(GameStatus), i));
                    buildings2++;
                }
            }

            // Check win condition
            if (buildings1 == 0) {
                printf("%s", RED);
                printf("            ___ _                  _      _                           \n");
                printf("           /   (_)_ __ ___  /\\   /(_) ___| |_ ___  _ __ _   _         \n");
                printf("          / /\\ / | '__/ _ \\ \\ \\ / / |/ __| __/ _ \\| '__| | | |        \n");
                printf("         / /_//| | | |  __/  \\ V /| | (__| || (_) | |  | |_| |        \n");
                printf("        /___,' |_|_|  \\___|   \\_/ |_|\\___|\\__\\___/|_|   \\__, |        \n");
                printf("                                                        |___/         \n");
                printf("\n%s════════════════════════════ %sGAME  ENDED%s ════════════════════════════\n\n", MAGENTA, NORMAL, MAGENTA);
                printf("%s", NORMAL);
                exit(0);
            }
            if (buildings2 == 0) {
                printf("%s", GREEN);
                printf("   __           _ _             _          _      _                   \n");
                printf("  /__\\ __ _  __| (_) __ _ _ __ | |_ /\\   /(_) ___| |_ ___  _ __ _   _ \n");
                printf(" / \\/// _` |/ _` | |/ _` | '_ \\| __|\\ \\ / / |/ __| __/ _ \\| '__| | | |\n");
                printf("/ _  \\ (_| | (_| | | (_| | | | | |_  \\ V /| | (__| || (_) | |  | |_| |\n");
                printf("\\/ \\_/\\__,_|\\__,_|_|\\__,_|_| |_|\\__|  \\_/ |_|\\___|\\__\\___/|_|   \\__, |\n");
                printf("                                                                |___/ \n");
                printf("\n%s════════════════════════════ %sGAME  ENDED%s ════════════════════════════\n\n", MAGENTA, NORMAL, MAGENTA);
                printf("%s", NORMAL);
                exit(0);
            }

            if (ActivePlayer(GameStatus) == 1) {
                printf("\n%s═════════════════════════════%s NEXT MOVE %s═════════════════════════════%s\n", GREEN, NORMAL, GREEN, NORMAL);
            } else {
                printf("\n%s═════════════════════════════%s NEXT MOVE %s═════════════════════════════%s\n", RED, NORMAL, RED, NORMAL);
            }

            Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus), Q1(GameStatus), Q2(GameStatus)));
            printf("                    Current forces: %s%d%s - %s%d%s - %s%d%s                         \n", GREEN, troops1, NORMAL, YELLOW, troops0, NORMAL, RED, troops2, NORMAL);
            printf("                    Current buildings: %s%d%s - %s%d%s - %s%d%s                      \n", GREEN, buildings1, NORMAL, YELLOW, buildings0, NORMAL, RED, buildings2, NORMAL);

            if (ActivePlayer(GameStatus) == 1) {
                printf("%s                          Player 1's Turn                             %s\n\n", GREEN, NORMAL);
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
                printf("%s                          Player 2's Turn                             %s\n\n", RED, NORMAL);
                if (IsQueueEmpty(Q2(GameStatus))) {
                    printf("You currently have no skills available.\n");
                } else {
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
            if (ActivePlayer(GameStatus) == 1) {
                printf("%sYour command: %s", GREEN, NORMAL);
            } else {
                printf("%sYour command: %s", RED, NORMAL);
            }
            ScanKata(&command);

            if (EQKata(command, MakeKata("ATTACK\n")) || EQKata(command, MakeKata("A\n"))) {
                berhasil = AttackCommand();
            } else if (EQKata(command, MakeKata("LEVEL_UP\n")) || EQKata(command, MakeKata("Q\n"))) {
                berhasil = LevelUpCommand();
            } else if (EQKata(command, MakeKata("SKILL\n")) || EQKata(command, MakeKata("S\n"))) {
                berhasil = SkillCommand();
            } else if (EQKata(command, MakeKata("UNDO\n")) || EQKata(command, MakeKata("U\n"))) {
                Pop(&StatusPemain(GameStatus), &tmp);
                berhasil = UndoCommand();
            } else if (EQKata(command, MakeKata("END_TURN\n")) || EQKata(command, MakeKata("E\n"))) {
                berhasil = EndTurnCommand();
                finishTurn = true;
            } else if (EQKata(command, MakeKata("SAVE\n")) || EQKata(command, MakeKata("V\n"))) {
                SaveCommand();
            } else if (EQKata(command, MakeKata("LOAD\n")) || EQKata(command, MakeKata("L\n"))) {
                berhasil = LoadCommand();
                if (berhasil) {
                    finishTurn = true;
                }
            } else if (EQKata(command, MakeKata("MOVE\n")) || EQKata(command, MakeKata("M\n"))) {
                berhasil = MoveCommand();
            } else if (EQKata(command, MakeKata("EXIT\n")) || EQKata(command, MakeKata("X\n"))) {
                printf("Babai :)\n");
                printf("\n%s════════════════════════════ %sGAME  ENDED%s ════════════════════════════\n\n", MAGENTA, NORMAL, MAGENTA);
                printf("%s", NORMAL);
                exit(0);
            } else if (EQKata(command, MakeKata("HELP\n")) || EQKata(command, MakeKata("H\n"))) {
                HelpCommand();
            } else if (EQKata(command, MakeKata("BUILDINGS\n")) || EQKata(command, MakeKata("B\n"))) {
                BuildingsCommand();
            } else if (EQKata(command, MakeKata("THAXX\n"))) {
                berhasil = TroopHack();
            } else if (EQKata(command, MakeKata("OHAXX\n"))) {
                berhasil = OwnerHack();
            } else {
                printf("Wrong Command! Type HELP for help.\n");
            }

            if (!berhasil) {
                Pop(&StatusPemain(GameStatus), &tmp);
            }
        }
    }
    return;
}

/*** Kelompok Fungsi Command ***/
boolean AttackCommand() {
/* Melaksanakan command ATTACK */
/* Mengembalikan true jika attack berhasil, dan sebaliknya */
    // Kamus lokal
    int counter, i, attackBuilding, defendBuilding, usedTroops, startingBuilding1 = 0, startingBuilding2 = 0, remainingBuilding = 0;
    // Algoritma
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if (Pemilik(ElmtTab(T(GameStatus), i)) == 1) startingBuilding1++;
        else if (Pemilik(ElmtTab(T(GameStatus), i)) == 2) startingBuilding2++;
    }

    // count number of owned towers
    int originalTower = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if ((Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) && (Tipe(ElmtTab(T(GameStatus), i)) == 'T')) originalTower++;
    }

    printf("Daftar bangunan:\n");
    counter = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
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
    ScanInt(&attackBuilding);
    if (attackBuilding <= 0 || attackBuilding > counter) {
        printf("Bro... Das not your building\n");
        return false;
    }
    counter = 0;
    // mencari id dari attackBuilding
    for (i = 1; i <= NBangunan(GameStatus); i++) {
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
        return false;
    }

    printf("Daftar bangunan yang dapat diserang: \n");
    counter = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if ((Pemilik(ElmtTab(T(GameStatus), i)) != ActivePlayer(GameStatus)) && (AdaEdge(Adjacency(GameStatus), attackBuilding, i))) {
            counter++;
            printf("%d. ", counter);
            TulisBangunan(ElmtTab(T(GameStatus), i));
            printf("\n");
        }
    }
    printf("Bangunan yang diserang: ");
    ScanInt(&defendBuilding);
    if (defendBuilding <= 0 || defendBuilding > counter) {
        printf("Um wat?\n");
        return false;
    }
    counter = 0;
    // mencari id dari defendBuilding
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if ((Pemilik(ElmtTab(T(GameStatus), i)) != ActivePlayer(GameStatus)) && (AdaEdge(Adjacency(GameStatus), attackBuilding, i))) {
            counter++;
            if (counter == defendBuilding) {
                defendBuilding = i;
                break;
            }
        }
    }

    int fortOriginalOwner = 0;
    // owner of building (if fort)
    if (Tipe(ElmtTab(T(GameStatus), defendBuilding)) == 'F') fortOriginalOwner = Pemilik(ElmtTab(T(GameStatus), defendBuilding));

    // attacking
    printf("Jumlah pasukan: ");
    ScanInt(&usedTroops);
    if (usedTroops <= 0 || usedTroops > Pasukan(ElmtTab(T(GameStatus), attackBuilding))) {
        printf("Serius dong mas\n");
        return false;
    }
    SudahSerang(ElmtTab(T(GameStatus), attackBuilding)) = true;
    Pasukan(ElmtTab(T(GameStatus), attackBuilding)) -= usedTroops;

    // check if enemy has a shield
    boolean adaShield = false;
    if (ActivePlayer(GameStatus) == 1 && SHIELD2(GameStatus) > 0) adaShield = true;
    if (ActivePlayer(GameStatus) == 2 && SHIELD1(GameStatus) > 0) adaShield = true;

    // check if player has attack up activated
    boolean adaAttackUp = false;
    if (ActivePlayer(GameStatus) == 1 && ATTACK_UP1(GameStatus) == 1) adaAttackUp = true;
    if (ActivePlayer(GameStatus) == 2 && ATTACK_UP2(GameStatus) == 1) adaAttackUp = true;

    // various attack modifiers
    if ((ActivePlayer(GameStatus) == 1 && CRITICAL_HIT1(GameStatus) == 1) || (ActivePlayer(GameStatus) == 2 && CRITICAL_HIT2(GameStatus) == 1)) {
        for (i = 1; i <= usedTroops; i++) {
            if (i*2 >= Pasukan(ElmtTab(T(GameStatus), defendBuilding))) {
                usedTroops -= i;
                Pemilik(ElmtTab(T(GameStatus), defendBuilding)) = ActivePlayer(GameStatus);
                printf("Critical Hit! This building is now yours!\n");
                Level(ElmtTab(T(GameStatus), defendBuilding)) = 1;
                AssignProperti(&ElmtTab(T(GameStatus), defendBuilding));
                Pasukan(ElmtTab(T(GameStatus), defendBuilding)) = usedTroops;
                usedTroops = 0;
                break;
            }
        }
        // if max troops can't kill (usedTroops == 0 if succeded before)
        if (usedTroops > 0) printf("Don't worry. You dealt a lot of damage to that building.\n");
        Pasukan(ElmtTab(T(GameStatus), defendBuilding)) -= usedTroops*2;
        usedTroops = 0;
        // reset crit
        if (ActivePlayer(GameStatus) == 1) CRITICAL_HIT1(GameStatus) = 0;
        if (ActivePlayer(GameStatus) == 2) CRITICAL_HIT2(GameStatus) = 0;
    } else if ((Pertahanan(ElmtTab(T(GameStatus), defendBuilding)) || adaShield) && (!adaAttackUp)) {
        // "When in doubt, bruteforce." - Thomas Alfa Edison
        for (i = 1; i <= usedTroops; i++) {
            if (i*3/4 >= Pasukan(ElmtTab(T(GameStatus), defendBuilding))) {
                usedTroops -= i;
                Pemilik(ElmtTab(T(GameStatus), defendBuilding)) = ActivePlayer(GameStatus);
                Level(ElmtTab(T(GameStatus), defendBuilding)) = 1;
                AssignProperti(&ElmtTab(T(GameStatus), defendBuilding));
                Pasukan(ElmtTab(T(GameStatus), defendBuilding)) = usedTroops;
                printf("Overcoming the defenses, this building is now yours!\n");
                usedTroops = 0;
                break;
            }
        }
        // if max troops can't kill (usedTroops == 0 if succeded before)
        if (usedTroops > 0) printf("F. Their deaths are not in vain. The walls are thicc.\n");
        Pasukan(ElmtTab(T(GameStatus), defendBuilding)) -= usedTroops*3/4;
        usedTroops = 0;
    } else /* No modifier or defense ignored by attack up skill */ {
        Pasukan(ElmtTab(T(GameStatus), defendBuilding)) -= usedTroops;
        if (Pasukan(ElmtTab(T(GameStatus), defendBuilding)) <= 0) /* Success */ {
            Pasukan(ElmtTab(T(GameStatus), defendBuilding)) *= -1;
            usedTroops = Pasukan(ElmtTab(T(GameStatus), defendBuilding));
            Pemilik(ElmtTab(T(GameStatus), defendBuilding)) = ActivePlayer(GameStatus);
            Level(ElmtTab(T(GameStatus), defendBuilding)) = 1;
            AssignProperti(&ElmtTab(T(GameStatus), defendBuilding));
            Pasukan(ElmtTab(T(GameStatus), defendBuilding)) = usedTroops;
            printf("This building is now yours!\n");
        } else {
            printf("F. Their deaths are in vain.\n");
        }
    }

    // SHIELD
    if (ActivePlayer(GameStatus) == 1) {
        remainingBuilding = 0;
        for (i=1;i<=NBangunan(GameStatus);i++) {
            if (Pemilik(ElmtTab(T(GameStatus), i)) == 2) remainingBuilding++;
        }
        if (startingBuilding2 == 3 && remainingBuilding == 2 && !IsQueueFull(Q2(GameStatus))) {
            printf("Player 2 gets a SHIELD skill.\n");
            AddElQueue(&(Q2(GameStatus)), SHIELD);
        }
    } else {
        remainingBuilding = 0;
        for (i=1;i<=NBangunan(GameStatus);i++) {
            if (Pemilik(ElmtTab(T(GameStatus), i)) == 1) remainingBuilding++;
        }
        if (startingBuilding1 == 3 && remainingBuilding == 2 && !IsQueueFull(Q1(GameStatus))) {
            printf("Player 1 gets a SHIELD skill.\n");
            AddElQueue(&(Q1(GameStatus)), SHIELD);
        }
    }

    int fortNewOwner = 0;
    // owner of building (if fort)
    if (Tipe(ElmtTab(T(GameStatus), defendBuilding)) == 'F') fortNewOwner = Pemilik(ElmtTab(T(GameStatus), defendBuilding));

    // Extra Turn Granted?
    if (fortOriginalOwner == 2 && fortNewOwner == 1 && !IsQueueFull(Q2(GameStatus))) {
        printf("Player 2 gets UNO REVERSE CARD.\n");
        AddElQueue(&(Q2(GameStatus)), EXTRA_TURN);
    }
    if (fortOriginalOwner == 1 && fortNewOwner == 2 && !IsQueueFull(Q1(GameStatus))) {
        printf("Player 1 gets UNO REVERSE CARD.\n");
        AddElQueue(&(Q1(GameStatus)), EXTRA_TURN);
    }

    // count number of (newly) owned towers
    int newTower = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if ((Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) && (Tipe(ElmtTab(T(GameStatus), i)) == 'T')) newTower++;
    }

    // Attack Up Granted?
    if (originalTower == 2 && newTower == 3) {
        if (ActivePlayer(GameStatus) == 1 && !IsQueueFull(Q1(GameStatus))) {
            printf("Player 1 gets Attack Up skill.\n");
            AddElQueue(&(Q1(GameStatus)), ATTACK_UP);
        } else if (ActivePlayer(GameStatus) == 2 && !IsQueueFull(Q2(GameStatus))) {
            printf("Player 2 gets Attack Up skill.\n");
            AddElQueue(&(Q2(GameStatus)), ATTACK_UP);
        }
    }

    // Barrage Granted?
    if (ActivePlayer(GameStatus) == 1) {
        remainingBuilding = 0;
        for (i=1;i<=NBangunan(GameStatus);i++) {
            if (Pemilik(ElmtTab(T(GameStatus), i)) == 1) remainingBuilding++;
        }
        if (startingBuilding1 == 9 && remainingBuilding == 10 && !IsQueueFull(Q2(GameStatus))) {
            printf("STOP! He's already dead! Here's a consolation prize. Player 2 gets a Barrage skill.\n");
            AddElQueue(&(Q2(GameStatus)), BARRAGE);
        }
    } else {
        remainingBuilding = 0;
        for (i=1;i<=NBangunan(GameStatus);i++) {
            if (Pemilik(ElmtTab(T(GameStatus), i)) == 2) remainingBuilding++;
        }
        if (startingBuilding2 == 9 && remainingBuilding == 10 && !IsQueueFull(Q1(GameStatus))) {
            printf("STOP! He's already dead! Here's a consolation prize. Player 1 gets a Barrage skill.\n");
            AddElQueue(&(Q1(GameStatus)), BARRAGE);
        }
    }

    return true;
}

boolean LevelUpCommand() {
/* Melaksanakan command LEVEL_UP */
/* Mengembalikan true jika level up berhasil, dan sebaliknya */
    // Kamus lokal
    int counter, i, lvUpBuilding, costTroops;
    // Algoritma
    // Daftar bangunan
    printf("Daftar bangunan:\n");
    counter = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
            counter++;
            printf("%d. ", counter);
            TulisBangunan(ElmtTab(T(GameStatus), i));
            printf("\n");
        }
    }
    printf("Masukkan angka bangunan yang ingin dinaikkan levelnya: ");
    ScanInt(&lvUpBuilding);
    if (lvUpBuilding <= 0 || lvUpBuilding > counter) {
        printf("Bro... Das not your building\n");
        return false;
    }
    // Cari ID dari lvUpBuilding
    counter = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
            counter++;
            if (counter == lvUpBuilding) {
                lvUpBuilding = i;
                break;
            }
        }
    }
    // Level up bangunan
    costTroops = Maksimum(ElmtTab(T(GameStatus), lvUpBuilding)) / 2;
    if (Pasukan(ElmtTab(T(GameStatus), lvUpBuilding)) < costTroops) {
        printf("Pasukan anda tidak cukup, master...\n");
        return false;
    } else if (Level(ElmtTab(T(GameStatus), lvUpBuilding)) >= 4) {
        printf("Bangunan ini sudah sangat kuat, master...\n");
        return false;
    } else {
        Pasukan(ElmtTab(T(GameStatus), lvUpBuilding)) -= costTroops;
        Level(ElmtTab(T(GameStatus), lvUpBuilding)) += 1;
        AssignProperti(&ElmtTab(T(GameStatus), lvUpBuilding));
        printf("Keputusan yang bijak, master...\n");
        printf("Bangunan ini sekarang menjadi level %d\n", Level(ElmtTab(T(GameStatus), lvUpBuilding)));
        return true;
    }
}

boolean SkillCommand() {
/* Melaksanakan command SKILL dan membersikhkan undo stack */
/* Mengembalikan true jika pemakaian skill berhasil, dan sebaliknya */
    int activeSkill = -1;
    if (ActivePlayer(GameStatus) == 1) {
        if (IsQueueEmpty(Q1(GameStatus))) {
            printf("No skill. Noob.\n");
            return false;
        }
        DelElQueue(&(Q1(GameStatus)), &activeSkill);
        if (activeSkill == 1) {
            printf("The buildings are now stronger...\n");
            for (int i = 1; i <= NBangunan(GameStatus); i++) {
                if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus) && Level(ElmtTab(T(GameStatus), i)) < 4) {
                    Level(ElmtTab(T(GameStatus), i))++;
                    AssignProperti(&ElmtTab(T(GameStatus), i));
                }
            }
        } else if (activeSkill == 2) {
            printf("S.H.I.E.L.D. activated.\n");
            SHIELD1(GameStatus) = 3;    // kenapa 3? karena dia berkurang di awal turn musuh, kalo 2 di turn ke 2 dia udah 0.
        } else if (activeSkill == 3) {
            printf("UNO SKIP CARD activated. You gained an extra turn.\n");
            EXTRA_TURN1(GameStatus) = 1;
            if (!IsQueueFull(Q2(GameStatus))) {
                printf("Your enemy gained a critical hit skill though...\n");
                AddElQueue(&(Q2(GameStatus)), CRITICAL_HIT);
            }
        } else if (activeSkill == 4) {
            printf("Piercing Hit! All enemy defenses neutralized.\n");
            ATTACK_UP1(GameStatus) = 1;
        } else if (activeSkill == 5) {
            printf("Critical Hit activated. Your attack becomes twice as powerful!\nP.S. You nullified their defenses too.\n");
            CRITICAL_HIT1(GameStatus) = 1;
        } else if (activeSkill == 6) {
            printf("All of your buildings become more crowded (by 5).\n");
            for (int i = 1; i <= NBangunan(GameStatus); i++) {
                if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
                    Pasukan(ElmtTab(T(GameStatus), i)) += 5;
                }
            }
        } else if (activeSkill == 7) {
            printf("All of your enemy's buildings seems to be less crowded (by 10).\n");
            for (int i = 1; i <= NBangunan(GameStatus); i++) {
                if (Pemilik(ElmtTab(T(GameStatus), i)) == 3 - ActivePlayer(GameStatus)) {
                    Pasukan(ElmtTab(T(GameStatus), i)) -= 10;
                    if (Pasukan(ElmtTab(T(GameStatus), i)) < 0) Pasukan(ElmtTab(T(GameStatus), i)) = 0;
                }
            }
        }
        MakeEmptyStack(&(StatusPemain(GameStatus)));
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus), Q1(GameStatus), Q2(GameStatus)));
        return true;
    } else {
        if (IsQueueEmpty(Q2(GameStatus))) {
            printf("No skill. Noob.\n");
            return false;
        }
        DelElQueue(&(Q2(GameStatus)), &activeSkill);
        if (activeSkill == 1) {
            printf("The buildings are now stronger...\n");
            for (int i = 1; i <= NBangunan(GameStatus); i++) {
                if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus) && Level(ElmtTab(T(GameStatus), i)) < 4) {
                    Level(ElmtTab(T(GameStatus), i))++;
                    AssignProperti(&ElmtTab(T(GameStatus), i));
                }
            }
        } else if (activeSkill == 2) {
            printf("S.H.I.E.L.D. activated.\n");
            SHIELD2(GameStatus) = 3;
        } else if (activeSkill == 3) {
            printf("UNO SKIP CARD activated. You gained an extra turn.\n");
            EXTRA_TURN2(GameStatus) = 1;
            if (!IsQueueFull(Q1(GameStatus))) {
                printf("Your enemy gained a critical hit skill though...\n");
                AddElQueue(&(Q1(GameStatus)), CRITICAL_HIT);
            }
        } else if (activeSkill == 4) {
            printf("Piercing Hit! All enemy defenses neutralized.\n");
            ATTACK_UP2(GameStatus) = 1;
        } else if (activeSkill == 5) {
            printf("Critical Hit activated. Your attack becomes twice as powerful!\nP.S. You nullified their defenses too.\n");
            CRITICAL_HIT2(GameStatus) = 1;
        } else if (activeSkill == 6) {
            printf("All of your buildings become more crowded (by 5).\n");
            for (int i = 1; i <= NBangunan(GameStatus); i++) {
                if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
                    Pasukan(ElmtTab(T(GameStatus), i)) += 5;
                }
            }
        } else if (activeSkill == 7) {
            printf("All of your enemy's buildings seems to be less crowded (by 10).\n");
            for (int i = 1; i <= NBangunan(GameStatus); i++) {
                if (Pemilik(ElmtTab(T(GameStatus), i)) == 3 - ActivePlayer(GameStatus)) {
                    Pasukan(ElmtTab(T(GameStatus), i)) -= 10;
                    if (Pasukan(ElmtTab(T(GameStatus), i)) < 0) Pasukan(ElmtTab(T(GameStatus), i)) = 0;
                }
            }
        }
        MakeEmptyStack(&(StatusPemain(GameStatus)));
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus), Q1(GameStatus), Q2(GameStatus)));
        return true;
    }
}

boolean UndoCommand() {
/* Melaksanakan command UNDO */
/* Selalu mengembalikan true, baik saat terjadi undo maupun undo tidak tersedia */
    // Kamus lokal
    ElTypeStack tmp;
    // Algoritma
    if (Top(StatusPemain(GameStatus)) == 1) {
        printf("Mau mundur kemana mas?\n");
    } else {
        Pop(&(StatusPemain(GameStatus)), &tmp);
        CopyTabBangunan(&(T(GameStatus)), TB(tmp));
        CopyTabSkill(&S1(GameStatus), TS1(tmp));
        CopyTabSkill(&S2(GameStatus), TS2(tmp));
        CopyQueue(&Q1(GameStatus), QS1(tmp));
        CopyQueue(&Q2(GameStatus), QS2(tmp));
        printf("Berhasil undo!\n");
    }
    return true;
}

boolean EndTurnCommand() {
/* Melaksanakan command END_TURN */
/* Selalu mengembalikan true, karena end turn selalu berhasil */
    // Kamus lokal
    int i;
    // Algoritma

    // check extra turn
    boolean extra = false;
    if (ActivePlayer(GameStatus) == 1 && EXTRA_TURN1(GameStatus) == 1) {
        EXTRA_TURN1(GameStatus) = 0;
        extra = true;
    }
    if (ActivePlayer(GameStatus) == 2 && EXTRA_TURN2(GameStatus) == 1) {
        EXTRA_TURN2(GameStatus) = 0;
        extra = true;
    }

    // reset attack up
    ATTACK_UP1(GameStatus) = 0;
    ATTACK_UP2(GameStatus) = 0;

    // Instant Reinforcement Grant? All owned buildings' level must be 4
    boolean grantIR = true;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus) && Level(ElmtTab(T(GameStatus), i)) != 4) grantIR = false;
    }
    if (grantIR) {
        if (ActivePlayer(GameStatus) == 1 && !IsQueueFull(Q1(GameStatus))) {
            printf("Congratulations on maxing all of your buildings. Here, get an IR skill. Use it wisely.\n");
            AddElQueue(&(Q1(GameStatus)), INSTANT_REINFORCEMENT);
        }
        if (ActivePlayer(GameStatus) == 2 && !IsQueueFull(Q2(GameStatus))) {
            printf("Congratulations on maxing all of your buildings. Here, get an IR skill. Use it wisely.\n");
            AddElQueue(&(Q2(GameStatus)), INSTANT_REINFORCEMENT);
        }
    }

    if (extra) {
        printf("Sini main lagi hehe :p\n");
        // reset status bangunan
        for (i = 1; i <= NBangunan(GameStatus); i++) {
            SudahSerang(ElmtTab(T(GameStatus), i)) = false;
        }
        // membersihkan stack
        MakeEmptyStack(&(StatusPemain(GameStatus)));
    } else {
        printf("%s══════════════════════════%s PLAYER  CHANGED %s══════════════════════════%s\n\n", MAGENTA, NORMAL, MAGENTA, NORMAL);
        // reset status bangunan
        for (i = 1; i <= NBangunan(GameStatus); i++) {
            SudahSerang(ElmtTab(T(GameStatus), i)) = false;
        }
        // mengubah 1 -> 2, 2 -> 1
        ActivePlayer(GameStatus) = 3 - ActivePlayer(GameStatus);
        // menambah turn number
        if (ActivePlayer(GameStatus) == 1) Turn(GameStatus)++;
        // membersihkan stack
        MakeEmptyStack(&(StatusPemain(GameStatus)));
    }
    return true;
}

void SaveCommand() {
/* Melaksanakan command SAVE */
/* I.S. GameStatus terdefinisi */
/* F.S. Melakukan proses penyimpanan GameStatus ke path file yang diberikan */
    // Kamus lokal
    Kata K;
    // Algoritma
    printf("Filesave path (abs or rel path): ");
    ScanKata(&K);
    Char(K, (Length(K) + 1)) = '\x00';
    SaveGameStatus(TabKata(K) + sizeof(char));
    printf("\n%s════════════════════════════ %sGAME  SAVED%s ════════════════════════════\n\n", MAGENTA, NORMAL, MAGENTA);
    printf("%s", NORMAL);
}

boolean LoadCommand() {
/* Melaksanakan command LOAD */
/* Mengembalikan true saat load berhasil dan false saat gagal */
    // Kamus lokal
    Kata K;
    int error;
    // Algoritma
    printf("Fileload path (abs or rel path): ");
    ScanKata(&K);
    Char(K, (Length(K) + 1)) = '\x00';
    LoadGameStatus(TabKata(K) + sizeof(char), &error);
    if (error != 0) {
        printf("\n%s════════════════════════════ %sLOAD FAILED%s ════════════════════════════\n\n", MAGENTA, NORMAL, MAGENTA);
        printf("%s", NORMAL);
        return false;
    } else {
        printf("\n%s════════════════════════════ %sGAME LOADED%s ════════════════════════════\n\n", MAGENTA, NORMAL, MAGENTA);
        printf("%s", NORMAL);
        return true;
    }
}

boolean MoveCommand() {
/* Melaksanakan command MOVE */
/* Mengembalikan true jika move berhasil, dan sebaliknya */
    // Kamus lokal
    int numTroops, counter, i, srcBuilding, destBuilding;
    // Algoritma
    // Bangunan asal
    printf("Bangunan asal:\n");
    counter = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
            counter++;
            printf("%d. ", counter);
            TulisBangunan(ElmtTab(T(GameStatus), i));
            printf("\n");
        }
    }
    printf("Masukkan angka bangunan asal: ");
    ScanInt(&srcBuilding);
    if (srcBuilding <= 0 || srcBuilding > counter) {
        printf("Bro... Das not your building\n");
        return false;
    }
    counter = 0;
    // mencari id dari srcBuilding
    for (int i = 1; i <= NBangunan(GameStatus); i++) {
        if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
            counter++;
            if (counter == srcBuilding) {
                srcBuilding = i;
                break;
            }
        }
    }
    // Bangunan tujuan
    printf("Bangunan tujuan:\n");
    counter = 0;
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if (
          (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) &&
          (AdaEdge(Adjacency(GameStatus), srcBuilding, i))
        ) {
            counter++;
            printf("%d. ", counter);
            TulisBangunan(ElmtTab(T(GameStatus), i));
            printf("\n");
        }
    }
    if (counter == 0) {
        printf("Tidak ada bangunan yang memenuhi syarat\n");
        return false;
    }
    printf("Masukkan angka bangunan tujuan: ");
    ScanInt(&destBuilding);
    if (destBuilding <= 0 || destBuilding > counter) {
        printf("Um wat?\n");
        return false;
    }
    // Cari ID dari destBuidling
    counter = 0;
    for (int i = 1; i <= NBangunan(GameStatus); i++) {
        if (
            (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) &&
            (AdaEdge(Adjacency(GameStatus), srcBuilding, i))
        ) {
            counter++;
            if (counter == destBuilding) {
                destBuilding = i;
                break;
            }
        }
    }
    // Jumlah pasukan
    printf("Jumlah pasukan yang ingin dipindahkan: ");
    ScanInt(&numTroops);
    if ((numTroops <= 0) || (numTroops > Pasukan(ElmtTab(T(GameStatus), srcBuilding)))) {
        printf("Well, that is invalid dude...\n");
        return false;
    }
    // Move pasukan
    printf("Sesuai perintah master, %d pasukan telah dipindahtugaskan...\n", numTroops);
    Pasukan(ElmtTab(T(GameStatus), srcBuilding)) -= numTroops;
    Pasukan(ElmtTab(T(GameStatus), destBuilding)) += numTroops;
    return true;
}

void HelpCommand() {
/* Melaksanakan command HELP */
/* I.S. Kondisi sembarang */
/* F.S. Menampilkan panel bantuan ke layar */
    printf("%s", CYAN);
    printf("╔═══════════════════════════════ %sHELP%s ══════════════════════════════╗\n", NORMAL, CYAN);
    printf("║%s 1. ATTACK (A)     : Serang bangunan musuh.                        %s║\n", NORMAL, CYAN);
    printf("║%s 2. LEVEL_UP (Q)   : Naikkan level bangunan milik kita.            %s║\n", NORMAL, CYAN);
    printf("║%s 3. SKILL (S)      : Gunakan skill yang tersedia.                  %s║\n", NORMAL, CYAN);
    printf("║%s 4. UNDO (U)       : Batalkan pergerakan terakhir.                 %s║\n", NORMAL, CYAN);
    printf("║%s 5. END_TURN (E)   : Giliran selesai.                              %s║\n", NORMAL, CYAN);
    printf("║%s 6. SAVE (V)       : Simpan status game.                           %s║\n", NORMAL, CYAN);
    printf("║%s 7. LOAD (L)       : Mengembalikan status game.                    %s║\n", NORMAL, CYAN);
    printf("║%s 8. MOVE (M)       : Pindahkan pasukan dari dan ke bangunan kita.  %s║\n", NORMAL, CYAN);
    printf("║%s 9. EXIT (X)       : Keluar dari game.                             %s║\n", NORMAL, CYAN);
    printf("║%s 10. HELP (H)      : Tampilkan bantuan.                            %s║\n", NORMAL, CYAN);
    printf("║%s 11. BUILDINGS (B) : Tampilkan status seluruh bangunan.            %s║\n", NORMAL, CYAN);
    printf("╚═══════════════════════════════ %sHELP%s ══════════════════════════════╝\n", NORMAL, CYAN);
    printf("%s", NORMAL);
}

void BuildingsCommand() {
/* Melaksanakan command BUILDINGS */
/* I.S. GameStatus terdefinisi */
/* F.S. Menampilkan list Bangunan ke layar */
    // Kamus lokal
    int i;
    // Algoritma
    for (i = 1; i <= NBangunan(GameStatus); i++) {
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
}

boolean TroopHack() {
/* Menambahkan/mengurangkan jumlah pasukan pada building apapun */
    // Kamus lokal
    int i, chosenBuilding, troopChange;
    // Algoritma
    // Daftar bangunan
    printf("Daftar bangunan:\n");
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        printf("%d. ", i);
        TulisBangunan(ElmtTab(T(GameStatus), i));
        printf("\n");
    }
    printf("Nomor bangunan yang akan dimanipulasi: ");
    scanf("%d", &chosenBuilding);
    printf("Jumlah penambahan/pengurangan pasukan: ");
    scanf("%d", &troopChange);
    Pasukan(ElmtTab(T(GameStatus), chosenBuilding)) += troopChange;
    return true;
}

boolean OwnerHack() {
/* Mengganti kepemilikan building apapun, semua atribut dari building tersebut (selain pemilik) tetap sama */
    // Kamus lokal
    int i, chosenBuilding, chosenForce;
    // Algoritma
    // Daftar bangunan
    printf("Daftar bangunan:\n");
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        printf("%d. ", i);
        TulisBangunan(ElmtTab(T(GameStatus), i));
        printf("\n");
    }
    printf("Nomor bangunan yang akan dimanipulasi: ");
    scanf("%d", &chosenBuilding);
    printf("Masukkan pemilik baru bangunan tersebut.\n1. Neutral\n2. Radiant\n3. Dire\nPilihan: ");
    scanf("%d", &chosenForce);
    Pemilik(ElmtTab(T(GameStatus), chosenBuilding)) = chosenForce - 1;
    return true;
}
