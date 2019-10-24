#include <stdio.h>
#include "header/array.h"
#include "header/bangunan.h"
#include "header/boolean.h"
#include "header/kata.h"
#include "header/listlinier.h"
#include "header/matriks.h"
#include "header/mesinkar.h"
#include "header/mesinkata.h"
#include "header/point.h"
#include "header/queue.h"
#include "header/stack.h"
#include "header/status.h"

int main() {
    printf("Hello world\n");
    Bangunan B1, B2;
    TabBangunan T;
    printf("Initializing Tab\n");
    MakeEmptyTab(&T, 100);
    printf("Done...\n");
    CopyBangunan(&ElmtTab(T, 1), MakeBangunan(1, 'C', MakePoint(1, 3)));
    CopyBangunan(&ElmtTab(T, 2), ValUndefTab);

    BacaIsiTab(&T);
    // TulisBangunan(ValUndefTab);
    TulisIsiTab(T);

    return 0;
}
