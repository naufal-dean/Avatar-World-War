#include "graph.h"
#include <stdio.h>

int main()
{
    Graph G,G1;
    ElTypeGraph U,V;
    int input;

    puts("Tester");
    puts("---------");
    MakeEmptyGraph(&G);
    MakeEmptyGraph(&G1);

    while (1)
    {
        puts("0 = Is\n1 = Insert\n2 = copy\nother = exit");
        printf("code: ");
        scanf("%d",&input);
        switch (input)
        {
        case 0:
            if (IsGraphEmpty(G))
            {
                puts("Graph Kosong");
            } else {
                puts("Masukkan node graph (format: U V)");
                scanf("%d %d",&U,&V);
                if (AdaEdge(G,U,V))
                {
                    puts("U dan V terhubung");
                }
            }
            break;
        
        case 1:
            puts("Masukkan node graph (format: U V)");
            scanf("%d %d",&U,&V);
            InsertElGraph(&G,U,V);
            break;

        case 2:
            CopyGraph(&G1,G);
            puts("Hasil copy graph");
            TulisGraph(G1);
            puts("");
            break;

        default:
            goto exit;
            break;
        }
    }
    
    exit:
    puts("Graph G:");
    TulisGraph(G);

    return 0;
}