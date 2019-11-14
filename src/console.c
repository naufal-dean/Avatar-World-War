#include <stdio.h>
#include "console.h"

/*** Kelompok Fungsi Command ***/
boolean AttackCommand() {
/* Melaksanakan command ATTACK */
/* Mengembalikan true jika attack berhasil, dan sebaliknya */
    // Kamus lokal
    int counter, i, attackBuilding, defendBuilding, usedTroops, startingBuilding1, startingBuilding2, remainingBuilding;
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
                Pasukan(ElmtTab(T(GameStatus), defendBuilding)) = usedTroops;
                usedTroops = 0;
                Pemilik(ElmtTab(T(GameStatus), defendBuilding)) = ActivePlayer(GameStatus);
                printf("Critical Hit! This building is now yours!\n");
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
    } else /* No modifier or defense ignored by attack up skill */ {
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
                }
            }
        } else if (activeSkill == 2) {
            printf("S.H.I.E.L.D. activated.\n");
            SHIELD1(GameStatus) = 2;
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
        }
        MakeEmptyStack(&(StatusPemain(GameStatus)));
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus)));
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
                }
            }
        } else if (activeSkill == 2) {
            printf("S.H.I.E.L.D. activated.\n");
            SHIELD2(GameStatus) = 2;
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
        }
        MakeEmptyStack(&(StatusPemain(GameStatus)));
        Push(&(StatusPemain(GameStatus)), MakeElTypeStack(T(GameStatus), S1(GameStatus), S2(GameStatus)));
        return true;
    }
}

boolean UndoCommand() {
/* Melaksanakan command UNDO */
/* Selalu mengembalikan true, karena undo selalu berhasil */
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

    if (extra) {
        printf("Cie keskip :p\n");
        // reset status bangunan
        for (i = 1; i <= NBangunan(GameStatus); i++) {
            SudahSerang(ElmtTab(T(GameStatus), i)) = false;
        }
        // membersihkan stack
        MakeEmptyStack(&(StatusPemain(GameStatus)));
    } else {
        printf("Player change!\n");
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
    printf("# ============================== HELP =============================== #\n");
    printf("| 1. ATTACK (A)     : Serang bangunan musuh.                          |\n");
    printf("| 2. LEVEL_UP (Q)   : Naikkan level bangunan milik kita.              |\n");
    printf("| 3. SKILL (S)      : Gunakan skill yang tersedia.                    |\n");
    printf("| 4. UNDO (D)       : Batalkan pergerakan terakhir.                   |\n");
    printf("| 5. END_TURN (E)   : Giliran selesai.                                |\n");
    printf("| 6. SAVE (V)       : Simpan status game.                             |\n");
    printf("| 7. MOVE (W)       : Pindahkan pasukan dari dan ke bangunan kita.    |\n");
    printf("| 8. EXIT (P)       : Keluar dari game.                               |\n");
    printf("| 9. HELP (H)       : Tampilkan bantuan.                              |\n");
    printf("| 10. BUILDINGS (B) : Tampilkan status seluruh bangunan.              |\n");
    printf("# ============================== HELP =============================== #\n");
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
