#include <stdio.h>
#include "console.h"

boolean AttackCommand() {
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
    printf("Bangunan yang digunakan untuk menyerang: ");
    int attackBuilding;
    scanf("%d", &attackBuilding);
    if (attackBuilding <= 0 || attackBuilding > counter) {
        printf("Bro... Das not your building\n");
        return false;
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
        return false;
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
        return false;
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
    if (usedTroops <= 0 || usedTroops > Pasukan(ElmtTab(T(GameStatus), attackBuilding))) {
        printf("Serius dong mas\n");
        return false;
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
    return true;
}

boolean LevelUpCommand() {
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
    for (int i = 1; i <= NBangunan(GameStatus); i++) {
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

boolean UndoCommand() {
    // Algoritma
    if (Top(StatusPemain(GameStatus)) == 1) {
        printf("Mau mundur kemana mas?\n");
    } else {
        ElTypeStack tmp;
        Pop(&(StatusPemain(GameStatus)), &tmp);
        CopyTabBangunan(&(T(GameStatus)), TB(tmp));
        CopyTabSkill(&S1(GameStatus), TS1(tmp));
        CopyTabSkill(&S2(GameStatus), TS2(tmp));
        printf("Berhasil undo!\n");
    }
    return true;
}

boolean EndTurnCommand() {
    printf("Player change!\n");
    // reset status bangunan
    for (int i = 1; i <= NBangunan(GameStatus); i++) {
        SudahSerang(ElmtTab(T(GameStatus), i)) = false;
    }
    // mengubah 1 -> 2, 2 -> 1
    ActivePlayer(GameStatus) = 3 - ActivePlayer(GameStatus);
    // menambah turn number
    if (ActivePlayer(GameStatus) == 1) Turn(GameStatus)++;
    // membersihkan stack
    MakeEmptyStack(&(StatusPemain(GameStatus)));
    return true;
}

boolean MoveCommand() {
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
}
