#include "matriks.h"
#include <stdio.h>

int main()
{
    Matriks M;
    int input,Nb,Nk;
    int i,j;

    puts("Tester");
    puts("---------");
    puts("NB = ");
    scanf("%d",&Nb);
    puts("NK = ");
    scanf("%d",&Nk);
    MakeMatriks(Nb,Nk,&M);

    while (1)
    {
        puts("0 = BacaUkuranMatriks\n1 = Indeks\n2 = TulisMatriksPeta\nother = exit");
        printf("code: ");
        scanf("%d",&input);
        switch (input)
        {
        case 0:
            BacaUkuranMatriks(&M);
            break;
        
        case 1:
            puts("nilai i:");
            scanf("%d",&i);
            puts("indeks j:");
            scanf("%d",&j);

            puts("indeks (i,j):");
            IsIdxMatriksValid(i,j) ? puts("indeks valid") : puts("indeks tidak valid");
            IsIdxMatriksEff(M,i,j) ? puts("indeks effektif") : puts("bukan indeks effektif");
            printf("indeks baris pertama: %d\n",GetFirstIdxBrs(M));
            printf("indeks baris terakhir: %d\n",GetLastIdxBrs(M));
            printf("indeks kolom pertama: %d\n",GetFirstIdxKol(M));
            printf("indeks kolom terakhir: %d\n",GetLastIdxKol(M));
            break;

        case 2:
            puts("dibutuhkan tab bangunan untuk feature ini");
            break;

        default:
            goto exit;
            break;
        }
    }
    
    exit:

    return 0;
}