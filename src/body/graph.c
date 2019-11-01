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

boolean IsU (AddressGraph P) {
    return (FirstAdj(P) != NilGraph);
}

void CreateEmptyGraph (Graph *L) {
    FirstG(*L) = NilGraph;
}

void Insert (Graph *G, ElTypeGraph X) {
    if (IsU(FirstG(*G))) {
        AddressGraph P;
        P = Alokasi(X);
        if (P != NilGraph) {
            AddressGraph last;
            if (IsEmptyGraph(*G)) {
                Next(P) = FirstG(*G);
                FirstG(*G) = P;
            } else {
                last = FirstG(*G);
                while (Next(last) != NilGraph) {
                    last = Next(last);
                }
                Next(P) = Next(last);
                Next(last) = P;
            }
            AddressGraph PF;
            PF = Alokasi(0);    // dummy
            FirstAdj(P) = PF; 
        }
    } else {
        AddressGraph P;
        P = Alokasi(X);
        if (P != NilGraph) {
            AddressGraph last;
            if (IsEmptyGraph(*G)) {
                Next(P) = FirstG(*G);
                FirstG(*G) = P;
            } else {
                last = FirstG(*G);
                while (Next(last) != NilGraph) {
                    last = Next(last);
                }
                Next(P) = Next(last);
                Next(last) = P;
            }
            FirstAdj(P) = NilGraph; 
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