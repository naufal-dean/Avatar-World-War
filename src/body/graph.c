#include "../header/graph.h"
#include <stddef.h>

AddressList Alokasi (ElTypeList X) {
    AddressList P;
    // Algoritma
    P=(ElmtList *)malloc(sizeof(ElmtList));
    if(P!=NilList){
        Info(P) = X;
        Next(P)=NilList;
    }
    return P;
}

boolean IsEmpty (List L) {
    return (First(L) == NilList);
}

boolean IsU (AddressList P) {
    return (FirstAdj(P) != NilList);
}

void CreateEmptyList (List *L) {
    First(*L) = NilList;
}

void Insert (List *L, ElTypeList X) {
    if (IsU(First(*L))) {
        AddressList P;
        P = Alokasi(X);
        if (P != NilList) {
            AddressList last;
            if (IsEmpty(*L)) {
                Next(P) = First(*L);
                First(*L) = P;
            } else {
                last = First(*L);
                while (Next(last) != NilList) {
                    last = Next(last);
                }
                Next(P) = Next(last);
                Next(last) = P;
            }
            AddressList PF;
            PF = Alokasi(0);    // dummy
            FirstAdj(P) = PF; 
        }
    } else {
        AddressList P;
        P = Alokasi(X);
        if (P != NilList) {
            AddressList last;
            if (IsEmpty(*L)) {
                Next(P) = First(*L);
                First(*L) = P;
            } else {
                last = First(*L);
                while (Next(last) != NilList) {
                    last = Next(last);
                }
                Next(P) = Next(last);
                Next(last) = P;
            }
            FirstAdj(P) = NilList; 
        }
    }
}

boolean AdaEdge(List L, ElTypeList U, ElTypeList V) {
    AddressList P = First(L);
    boolean FoundU = false;
    while (P != NilList && !FoundU) {
        if (Info(P) == U) {
            FoundU = true;
        } else {
            P = Next(P);
        }
    }
    if (FoundU) {
        AddressList PF = FirstAdj(P);
        boolean FoundV = false;
        while (PF != NilList && !FoundV) {
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