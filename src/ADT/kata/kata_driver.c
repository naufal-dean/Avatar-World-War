#include <stdio.h>
#include "kata.h"
#include "../mesinkata/mesinkata.h"
#include "../mesinkar/mesinkar.h"

int main () {
    printf("Matahari terbit di ... ");
    Kata K;
    MakeEmptyKata(&K);
    ScanKata(&K);
    if (EQKata(K, MakeKata("Timur\n"))) {
        printf("Ya benar!\n");
    } else {
        printf("Salah :(, jawabannya Timur\n");
    }
    return 0;
}
