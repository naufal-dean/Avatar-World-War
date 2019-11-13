#include <stdio.h>
#include "console.h"

void AttackCommand() {
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
    ScanInt(&attackBuilding);
    if (attackBuilding <= 0 || attackBuilding > counter) {
        printf("Bro... Das not your building\n");
        return;
    }
    // Cari ID
    attackBuilding = GetBuildingID(attackBuilding);
    if (SudahSerang(ElmtTab(T(GameStatus), attackBuilding))) {
        printf("This building is busy. The attack could not commence.\n");
        return;
    }

    printf("Daftar bangunan yang dapat diserang: \n");
    counter = 0;
    for (int i = 1; i <= NBangunan(GameStatus); i++) {
        if (
          (Pemilik(ElmtTab(T(GameStatus), i)) != ActivePlayer(GameStatus)) &&
          (AdaEdge(Adjacency(GameStatus), attackBuilding, i))
        ) {
            counter++;
            printf("%d. ", counter);
            TulisBangunan(ElmtTab(T(GameStatus), i));
            printf("\n");
        }
    }
    if (counter == 0) {
        printf("Maaf master, tidak ada bangunan yang bisa diserang dari sini...\n");
        return;
    }
    printf("Bangunan yang diserang: ");
    int defendBuilding;
    ScanInt(&defendBuilding);
    if (defendBuilding <= 0 || defendBuilding > counter) {
        printf("Um wat?\n");
        return;
    }
    // Cari ID
    defendBuilding = GetBuildingID(defendBuilding);

    // attacking
    printf("Jumlah pasukan: ");
    int usedTroops;
    ScanInt(&usedTroops);
    if ((usedTroops <= 0) || (usedTroops > Pasukan(ElmtTab(T(GameStatus), attackBuilding)))) {
        printf("That is obviously an invalid number, dude...\n");
        return;
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
}

void LevelUpCommand() {
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
        return;
    }
    // Cari ID
    lvUpBuilding = GetBuildingID(lvUpBuilding);
    // Level up bangunan
    costTroops = Maksimum(ElmtTab(T(GameStatus), lvUpBuilding)) / 2;
    if (Pasukan(ElmtTab(T(GameStatus), lvUpBuilding)) < costTroops) {
        printf("Pasukan anda tidak cukup, master...\n");
    } else if (Level(ElmtTab(T(GameStatus), lvUpBuilding)) >= 4) {
        printf("Bangunan ini sudah sangat kuat, master...\n");
    } else {
        Pasukan(ElmtTab(T(GameStatus), lvUpBuilding)) -= costTroops;
        Level(ElmtTab(T(GameStatus), lvUpBuilding)) += 1;
        AssignProperti(&ElmtTab(T(GameStatus), lvUpBuilding));
        printf("Keputusan yang bijak, master...\n");
        printf("Bangunan ini sekarang menjadi level %d\n", Level(ElmtTab(T(GameStatus), lvUpBuilding)));
    }
}

void EndTurnCommand() {
    printf("Player change!\n");
    // reset status bangunan
    for (int i = 1; i <= NBangunan(GameStatus); i++) {
        SudahSerang(ElmtTab(T(GameStatus), i)) = false;
    }
    // mengubah 1 -> 2, 2 -> 1
    ActivePlayer(GameStatus) = 3 - ActivePlayer(GameStatus);
    // menambah turn number
    if (ActivePlayer(GameStatus) == 1) Turn(GameStatus)++;
}

void MoveCommand() {
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
        return;
    }
    // Cari ID
    srcBuilding = GetBuildingID(srcBuilding);
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
        return;
    }
    printf("Masukkan angka bangunan tujuan: ");
    ScanInt(&destBuilding);
    if (destBuilding <= 0 || destBuilding > counter) {
        printf("Um wat?\n");
        return;
    }
    // Cari ID
    destBuilding = GetBuildingID(destBuilding);
    // Jumlah pasukan
    printf("Jumlah pasukan yang ingin dipindahkan: ");
    ScanInt(&numTroops);
    if ((numTroops <= 0) || (numTroops > Pasukan(ElmtTab(T(GameStatus), destBuilding)))) {
        printf("Well, that is invalid dude...\n");
        return;
    }
    // Move pasukan
    printf("Sesuai perintah master, %d pasukan telah dipindahtugaskan...\n", numTroops);
    Pasukan(ElmtTab(T(GameStatus), srcBuilding)) -= numTroops;
    Pasukan(ElmtTab(T(GameStatus), destBuilding)) += numTroops;
}

void HelpCommand() {
    printf("# ============================ HELP ============================= #\n");
    printf("| 1. ATTACK     : Serang bangunan musuh.                          |\n");
    printf("| 2. LEVEL_UP   : Naikkan level bangunan milik kita.              |\n");
    printf("| 3. SKILL      : Gunakan skill yang tersedia.                    |\n");
    printf("| 4. UNDO       : Batalkan pergerakan terakhir.                   |\n");
    printf("| 5. END_TURN   : Giliran selesai.                                |\n");
    printf("| 6. SAVE       : Simpan status game.                             |\n");
    printf("| 7. MOVE       : Pindahkan pasukan dari dan ke bangunan kita.    |\n");
    printf("| 8. EXIT       : Keluar dari game.                               |\n");
    printf("| 9. HELP       : Tampilkan bantuan.                              |\n");
    printf("| 10. BUILDINGS : Tampilkan status seluruh bangunan.              |\n");
    printf("# ============================ HELP ============================= #\n");
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

int GetBuildingID(int choice) {
    // Kamus lokal
    int i, counter = 0;
    // Algoritma
    for (i = 1; i <= NBangunan(GameStatus); i++) {
        if (Pemilik(ElmtTab(T(GameStatus), i)) == ActivePlayer(GameStatus)) {
            counter++;
            if (counter == choice) {
                return (i);
            }
        }
    }
}
