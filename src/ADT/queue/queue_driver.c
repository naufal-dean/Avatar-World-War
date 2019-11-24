#include "queue.h"
#include <stdio.h>

int main()
{
    Queue Q1,Q2;
    ElTypeQueue X;
    int input,max;

    puts("Tester");
    puts("---------");
    puts("Max elemen queue:");
    scanf("%d",&max);
    MakeEmptyQueue(&Q1,max);
    MakeEmptyQueue(&Q2,max);

    while (1)
    {
        puts("0 = Is/NbElmt\n1 = Add/Del\n2 = Copy\nother = exit");
        printf("code: ");
        scanf("%d",&input);
        switch (input)
        {
        case 0:
            if (IsQueueEmpty(Q1))
            {
                puts("Q kosong");
            } else if (IsQueueFull(Q1))
            {
                puts("Q penuh");
            } else
            {
                puts("Q tidak kosong dan belum penuh");
            }
            printf("Banyak Elemen Q: %d\n",NBElmtQueue(Q1));
            break;
        
        case 1:
            puts("0 = Add\n1 = Del");
            scanf("%d",&input);
            switch (input)
            {
            case 0:
                if (!IsQueueFull(Q1)){
                    puts("Masukkan elemen tambahan X");
                    scanf("%d", &X);
                    AddElQueue(&Q1,X);
                }
                else {puts("Q penuh");}
                
                break;
            
            case 1:
                if (!IsQueueEmpty(Q1))
                {
                    DelElQueue(&Q1,&X);
                    printf("elemen dihapus: %d\n", X);
                } else
                {
                    puts("Q kosong");
                }
                break;
            }
            break;

        case 2:
            CopyQueue(&Q2,Q1);
            break;

        default:
            goto exit;
            break;
        }
    }
    
    exit:

    return 0;
}