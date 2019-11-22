#include <stdio.h>
#include "array.h"
#include "../bangunan/bangunan.h"

int main(){
  TabBangunan T1,T2;
  Bangunan temp;
  int input,ID;

  printf("Tester\n");
  printf("----------\n");
  printf("Max Elemen Tab: ");
  scanf("%d",&input);
  MakeEmptyTab(&T1,input);
  MakeEmptyTab(&T2,input);
  
  while(true){
    printf("0 = index\n1 = I/O\n2 = Is2\n3 = operasi\ncode : ");
    scanf("%d",&input);
    switch(input){
      case 0:
        printf("Index = ");
        scanf("%d",&input);
        printf("IsIdxTabValid(T1,i) = %d\n",IsIdxTabValid(T1,input));
        printf("IsIdxTabEff(T1,i) = %d\n",IsIdxTabEff(T1,input));
        break;
      case 1:
        printf("Input 1\n");
        BacaIsiTab(&T1);

        printf("Input 2\n");
        BacaIsiTab(&T2);

        printf("[T1] \n");
        TulisIsiTab(T1);
        printf("\n");

        printf("[T2] \n");
        TulisIsiTab(T2);
        printf("\n");
        break;
      case 2:
        printf("IsTabEmpty(T1) = %d\n",IsTabEmpty(T1));
        printf("IsTabFull(T1) = %d\n",IsTabFull(T1));
        printf("NbElmtTab(T1) = %d\n",NbElmtTab(T1));
        printf("MaxElementTab(T1) = %d\n",MaxElementTab(T1));
        printf("GetFirstIdxTab(T1) = %d\n",GetFirstIdxTab(T1));
        printf("GetLastIdxTab(T1) = %d\n",GetLastIdxTab(T1));
        break;
      case 3:
        printf("[T1] \n");
        TulisIsiTab(T1);
        printf("\n");
        printf("1 = addElTab\n2 = delElTab\n3 = copyTab\ncode : ");
        scanf("%d",&input);
        switch(input){
          case 1:
            puts("ID bangunan");
            scanf("%d",&ID);
            BacaBangunan(&temp,ID);
            AddElTab(&T1,temp);
            TulisIsiTab(T1);
            break;
          case 2:
            DelElTab(&T1,&temp,ID);
            printf("ID Bangunan di delet: %d",ID);
            TulisBangunan(temp);
            TulisIsiTab(T1);
            break;
          case 3:
            CopyTabBangunan(&T2,T1);
            puts("Isi Tab T2, hasil copy T1");
            TulisIsiTab(T2);
            break;
        }
        break;
    }
  }

  return 0;
}
