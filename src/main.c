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
#include "header/point.h"
#include "header/pcolor.h"
#include "header/queue.h"
#include "header/stack.h"
#include "header/status.h"

int main() {
    int X, error;
    Kata K;
    char C = 'a';
    printf("%s%s%s\n", YELLOW, "Hello world", NORMAL);

    printf("Initializing GameStatus...\n");
    SetupConfigGameStatus("../data/config.txt", &error);
    printf("Initialization done...\n");

    TulisMatriksPeta(Peta(GameStatus), T(GameStatus));

    return 0;
}
