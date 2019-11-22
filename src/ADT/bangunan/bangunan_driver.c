#include <stdio.h>
#include "bangunan.h"

int main(){
  Bangunan B1,B2,B3;
  int input,ID,A,M;

  printf("Tester\n");
  printf("----------\n");
  
  while(true){
    printf("0 = I/O\n1 = Is\n2 = operasi\nother = exit\ncode : ");
    scanf("%d",&input);
    switch(input){
      case 0:
            puts("ID bangunan B1: ");
            scanf("%d",&ID);
            BacaBangunan(&B1,ID);

            puts("ID bangunan B2: ");
            scanf("%d",&ID);
            BacaBangunan(&B2,ID);

            puts("Bangunan B1");
            TulisBangunan(B1);
            puts("\nBangunan B2");
            TulisBangunan(B2);
            puts("");
        break;
      case 1:
            printf("EQBangunan(B1,B2) = %d\n",EQBangunan(B1,B2));
        break;
      case 2:
            puts("0 = upgrade level\n1 = tambah pasukan\n2 = assign property\n3 = assign property helper");
            printf("code: ");
            scanf("%d",&input);
            switch (input)
            {
            case 0:
                UpgradeLevel(&B1);
                break;
            case 1:
                printf("Pemain: ");
                scanf("%d",&input);
                TambahPasukan(&B1,input);
                break;
            case 2:
                AssignProperti(&B1);
                break;
            case 3:
                printf("nilai A: ");
                scanf("%d",&A);
                printf("nilai M: ");
                scanf("%d",&M);
                AssignPropertiHelper(&B1,A,M,1);
            }
            TulisBangunan(B1);
            puts("");
        break;
      default:
        TulisBangunan(B1);
        puts("");
        TulisBangunan(B2);
        puts("");
        goto exit;
    }
  }
  exit:
  return 0;
}
