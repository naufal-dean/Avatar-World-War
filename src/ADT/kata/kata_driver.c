#include "kata.h"
#include <stdio.h>

int main()
{
    Kata K,K1;
    char * C;
    int input;

    puts("Tester");
    puts("---------");
    MakeEmptyKata(&K);
    MakeEmptyKata(&K1);

    while (1)
    {
        puts("0 = relasional\n1 = operasi lain\nother = exit");
        printf("code: ");
        scanf("%d",&input);
        switch (input)
        {
        case 0:
            puts("EQPoint(P1,P2)");
            EQKata(K, K1) ? puts("EQKata(K,K1) bernilai true"):puts("EQKata(K,K1) bernilai false");
            break;
        case 1:
            puts("Baca Kata K:");
            scanf("%s",C);
            K = MakeKata(C);
            puts("Baca Kata K1:");
            scanf("%s",C);
            K1 = MakeKata(C);
            break;
        default:
            goto exit;
            break;
        }
    }
    
    exit:
    puts("Kata K:");
    TulisKata(K);
    puts("Kata K1:");
    TulisKata(K1);

    return 0;
}