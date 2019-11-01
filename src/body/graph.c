#include "../header/graph.h"
#include <stddef.h>

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

void Insert (Graph *G, ElTypeGraph U, ElTypeGraph V) {
    if (U != 0) {
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
        while (Next(P) != NilGraph) {
            P = Next(P);
        }
        AddressGraph New = Alokasi(U);
        Next(New) = Next(P);
        Next(P) = New;
        FirstAdj(New) = Alokasi(0);
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