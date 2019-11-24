#include "point.h"
#include <stdio.h>

int main()
{
    Point P1,P2;
    int input;

    puts("Tester");
    puts("---------");

    while (1)
    {
        puts("Point P1:");
        BacaPoint(&P1);
        puts("Point P2:");
        BacaPoint(&P2);

        puts("0 = relasional\n1 = operasi lain\nother = exit");
        printf("code: ");
        scanf("%d",&input);
        switch (input)
        {
        case 0:
            puts("EQPoint(P1,P2)");
            (EQPoint(P1,P2)) ? puts("EQPoint(P1,P2) bernilai true"):puts("EQPoint(P1,P2) bernilai false");
            break;
        case 1:
            puts("CopyPoint()");
            puts("P1:");
            TulisPoint(P1);
            puts("");
            puts("P2 sebelum P1 di copy");
            TulisPoint(P2);
            puts("");
            CopyPoint(&P2,P1);
            puts("P2 setelah di copy:");
            TulisPoint(P2);
            break;
        default:
            goto exit;
            puts("P1:");
            TulisPoint(P1);
            puts("");
            puts("P2:");
            TulisPoint(P2);
            puts("");
            break;
        }
    }
    
    exit:

    return 0;
}