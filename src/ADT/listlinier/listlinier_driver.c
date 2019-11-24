#include <stdio.h>
#include "listlinier.h"

int main(){
	List L;
	ElTypeList x,y;
	AddressList pt,pt2;
	int input,exit = 0;
	CreateEmptyList(&L);

	while(!exit){
		printf("1. insertfirst\n2. insertlast\n3. delfirst\n4. dellast\n5. delp\n6. search\n7. insertafter\n8. deleteafter\n");
		scanf("%d",&input);
		switch(input){
			case 1:
				scanf("%d",&x);
				InsVFirst(&L,x);
				break;
			case 2:
				scanf("%d",&x);
				InsVLast(&L,x);
				break;
			case 3:
				DelVFirst(&L,&x);
				printf("deleted:%d\n",x);
				break;
			case 4:
				DelVLast(&L,&x);
				printf("deleted:%d\n",x);
				break;
			case 5:
				scanf("%d",&x);
				DelP(&L,x);
				break;
			case 6:
				scanf("%d",&x);
				pt=SearchInfo(L,x);
				if(pt==NilList){
					printf("not found\n");
				}else{
					printf("found in %d with value %d\n",pt,Info(pt));
				}
				break;
			case 7:
				printf("insert after element: ");scanf("%d",&x);
				printf("value to be inserted : ");scanf("%d",&y);
				pt2=AlokasiElList(y);
				pt=SearchInfo(L,x);
				InsertAfter(&L,pt2,pt);
				break;
			case 8:
				printf("delete after element: ");scanf("%d",&x);
				pt=SearchInfo(L,x);
				DelAfter(&L,&pt2,pt);
				printf("deleted: %d\n",Info(pt2));
				break;
			default :
				exit = 1;

		}
		PrintInfo(L);
		printf("\n\n");
	}
	return 0;
}