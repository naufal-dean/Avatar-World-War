#include "../header/graph.h"
#include <stddef.h>
#include <stdio.h>

/*** Konstruktor ***/
void MakeEmptyGraph (Graph *L) {
/* Menginisialisasi graph kosong */
/* I.S. G sembarang */
/* F.S. Terbentuk Graph kosong, FirstG(G) = NilGraph */
    FirstG(*L) = NilGraph;
}

AddressGraph AlokasiElGraph (ElTypeGraph X) {
/* Melakukan alokasi terhadap suatu elemen graph */
    // Kamus lokal
    AddressGraph P;
    // Algoritma
    P=(ElmtGraph *)malloc(sizeof(ElmtGraph));
    if(P!=NilGraph){
        Info(P) = X;
        Next(P)=NilGraph;
    }
    return P;
}

/*** Kelompok tes Graph kosong ***/
boolean IsGraphEmpty (Graph G) {
/* Mengeluarkan true apabila graph kosong, dan false bila tidak */
    return (FirstG(G) == NilGraph);
}

/*** Kelompok insert dan cek elemen Graph ***/
void InsertElGraph (Graph *G, ElTypeGraph U, ElTypeGraph V) {
/* Menambahkan elemen ke dalam Graph */
/* Jika V == 0, maka menambahkan elemen V di dalam list adj U */
/* Jika V != 0, maka menambahkan elemen U di dalam G */
    // Kamus lokal
    AddressGraph P, PF, New;
    boolean FoundU;
    // Algoritma
    P = FirstG(*G);
    FoundU = false;
    while (P != NilGraph && !FoundU) {
        if (Info(P) == U) {
            FoundU = true;
        } else {
            P = Next(P);
        }
    }

    if (FoundU) { // Basis
        PF = FirstAdj(P);
        while (Next(PF) != NilGraph) {
            PF = Next(PF);
        }
        New = AlokasiElGraph(V);
        Next(New) = Next(PF);
        Next(PF) = New;
    } else { // Not found, create new node. Rekurens
        P = FirstG(*G);
        if (P == NilGraph) {
            FirstG(*G) = AlokasiElGraph(U);
            Next(FirstG(*G)) = NilGraph;
            FirstAdj(FirstG(*G)) = AlokasiElGraph(DummyElGraph);
            Next(FirstAdj(FirstG(*G))) = NilGraph;
            InsertElGraph(G, U, V);
        } else {
            while (Next(P) != NilGraph) {
                P = Next(P);
            }
            New = AlokasiElGraph(U);
            Next(New) = Next(P);
            Next(P) = New;
            FirstAdj(New) = AlokasiElGraph(DummyElGraph);
            Next(FirstAdj(New)) = NilGraph;
            InsertElGraph(G, U, V);
        }
    }
}

boolean AdaEdge(Graph L, ElTypeGraph U, ElTypeGraph V) {
/* Mengeluarkan true bila ada edge dari vertex U ke V */
    // Kamus lokal
    AddressGraph P, PF;
    boolean FoundU, FoundV;
    // Algoritma
    P = FirstG(L);
    FoundU = false;
    while (P != NilGraph && !FoundU) {
        if (Info(P) == U) {
            FoundU = true;
        } else {
            P = Next(P);
        }
    }
    if (FoundU) {
        PF = FirstAdj(P);
        FoundV = false;
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

/*** Kelompok operasi OUTPUT ***/
void TulisGraph (Graph G) {
/* Menuliskan isi G ke layar */
/* I.S. Graph G terdefinisi */
/* F.S. Isi Graph G dituliskan ke layar */
    // Kamus lokal
    AddressGraph P, PF;
    // Algoritma
    P = FirstG(G);
    while (P != NilGraph) {
        printf("%d --> ", Info(P));
        PF = Next(FirstAdj(P));
        while (PF != NilGraph) {
            printf("%d ", Info(PF));
            PF = Next(PF);
        }
        P = Next(P);
        printf("\n");
    }
}

/*** Kelompok operasi lain ***/
void CopyGraph(Graph * Gout, Graph Gin) {
/* Melakukan penyalinan Gin ke Gout */
/* I.S. Gin terdefinisi, Gout sembarang */
/* F.S. Gout memiliki properti yang sama dengan Gin */
    // Kamus lokal
    AddressGraph P, PF;
    // Algoritma
    MakeEmptyGraph(Gout);
    P = FirstG(Gin);
    while (P != NilGraph) {
        PF = Next(FirstAdj(P));
        while (PF != NilGraph) {
            InsertElGraph(Gout, Info(P), Info(PF));
            PF = Next(PF);
        }
        P = Next(P);
    }
}
