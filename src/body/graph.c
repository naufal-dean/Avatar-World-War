#include "../header/graph.h"
#include <stddef.h>
#include <stdio.h>

AddressGraph Alokasi (ElTypeGraph X) {
    AddressGraph P;
    // Algoritma
    P=(ElmtGraph *)malloc(sizeof(ElmtGraph));
    if(P!=NilGraph){
        Info(P) = X;
        Next(P)=NilGraph;
    }
    return P;
}

boolean IsEmptyGraph (Graph G) {
    return (FirstG(G) == NilGraph);
}

void CreateEmptyGraph (Graph *L) {
    FirstG(*L) = NilGraph;
}

void InsertGraph (Graph *G, ElTypeGraph U, ElTypeGraph V) {
    if (V != 0) {
        AddressGraph P = FirstG(*G);
        boolean FoundU = false;
        while (P != NilGraph && !FoundU) {
            if (Info(P) == U) {
                FoundU = true;
            } else {
                P = Next(P);
            }
        }
        if (FoundU) {
            AddressGraph PF = FirstAdj(P);
            while (Next(PF) != NilGraph) {
                PF = Next(PF);
            }
            AddressGraph New = Alokasi(V);
            Next(New) = Next(PF);
            Next(PF) = New;
        }
    } else {
        AddressGraph P = FirstG(*G);
        if (P == NilGraph) {
            FirstG(*G) = Alokasi(U);
            Next(FirstG(*G)) = NilGraph;
            FirstAdj(FirstG(*G)) = Alokasi(0);
            Next(FirstAdj(FirstG(*G))) = NilGraph;
        } else {
            while (Next(P) != NilGraph) {
                P = Next(P);
            }
            AddressGraph New = Alokasi(U);
            Next(New) = Next(P);
            Next(P) = New;
            FirstAdj(New) = Alokasi(0);
            Next(FirstAdj(New)) = NilGraph;
        }
    }
}

boolean AdaEdge(Graph L, ElTypeGraph U, ElTypeGraph V) {
    AddressGraph P = FirstG(L);
    boolean FoundU = false;
    while (P != NilGraph && !FoundU) {
        if (Info(P) == U) {
            FoundU = true;
        } else {
            P = Next(P);
        }
    }
    if (FoundU) {
        AddressGraph PF = FirstAdj(P);
        boolean FoundV = false;
        while (PF != NilGraph && !FoundV) {
            if (Info(PF) == V) {
                FoundV = true;
            } else {
                PF = Next(PF);
            }
        }
        return FoundV;
    } else {
        return false;
    }
}

void PrintGraph (Graph G) {
    AddressGraph P = FirstG(G);
    while (Next(P) != NilGraph) {
        printf("%d --> ", Info(P));
        AddressGraph PF = FirstAdj(P);
        while (Next(PF) != NilGraph) {
            printf("%d ", Info(PF));
            PF = Next(PF);
        }
        P = Next(P);
        printf("\n");
    }
}