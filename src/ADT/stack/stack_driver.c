#include "stack.h"
#include "../queue/queue.h"
#include "../array/array.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Stack S;
    ElTypeStack X;
    TabBangunan T;
    Queue Q1, Q2;
    int *S1, *S2;
    int input, max = 4;

    puts("Tester");
    puts("---------");
    MakeEmptyStack(&S);

    while (1)
    {
        puts("0 = Is\n1 = Push/Pop\n2 = Operasi lain\nother = exit");
        printf("code: ");
        scanf("%d",&input);
        switch (input)
        {
        case 0:
            if (IsStackEmpty(S))
            {
                puts("Stack kosong");
            } else if (IsStackFull(S))
            {
                puts("Stack Penuh");
            } else
            {
                puts("Stack Berisi dan tidak penuh");
            }
            break;
        
        case 1:
            puts("0 = Push\n1 = Pop");
            printf("code: ");
            scanf("%d",&input);
            if (input)
            {
                MakeEmptyTab(&T,max);
                MakeEmptyQueue(&Q1, max);
                MakeEmptyQueue(&Q2, max);
                S1 = (int *) malloc (sizeof(int));
                S2 = (int *) malloc (sizeof(int));
                X = MakeElTypeStack(T, S1, S2, Q1, Q2);
                Pop(&S,&X);
            } else
            {
                if (IsStackEmpty(S))
                {
                    puts("Stack Kosong");
                }
                else
                {
                    Push(&S,X);
                    puts("Tab Skill 1: ");
                    PrintTabSkill(TS1(X));
                    puts("Tab Skill 2: ");
                    PrintTabSkill(TS2(X));
                }
            }

        default:
            goto exit;
            break;
        }
    }
    
    exit:
    PrintTabSkill(TS1(InfoTop(S)));
    PrintTabSkill(TS2(InfoTop(S)));

    return 0;
}