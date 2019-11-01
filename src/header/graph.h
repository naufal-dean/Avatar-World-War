/*** ADT LIST LINIER ***/
/* List menggunakan representasi fisik pointer */

#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"
#include <stddef.h>
#include <stdlib.h>

/* Kamus Umum */
#define NilGraph NULL

typedef int ElTypeGraph;	// Info elemen list berupa type bentukan "Bangunan"
typedef struct tElmtGraph *AddressGraph;	// Alamat elemen list
typedef struct tElmtGraph {
	ElTypeGraph Info;
	AddressGraph FirstAdj;	// Alamat pertama adj list, berisi alamat bila elemen tersebut merupakan U dan Nil bila elemen tersebut merupakan V
	AddressGraph Next;
} ElmtGraph;
typedef struct {
	AddressGraph First;	// Alamat pertama list
} Graph;

/* Definisi list : */
/* List kosong : First(L) = NilList */
/* Setiap elemen dengan AddressList P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika AddressListnya Last, maka Next(Last)=NilList */

#define Info(P) (P)->Info
#define FirstAdj(P) (P)->FirstAdj
#define Next(P) (P)->Next
#define FirstG(G) ((G).First)

AddressGraph Alokasi (ElTypeGraph X);

boolean IsEmptyGraph (Graph G);

boolean IsU (AddressGraph P);

void CreateEmptyGraph (Graph *G);

void InsertGraph (Graph *G, ElTypeGraph X);

boolean AdaEdge(Graph G, ElTypeGraph U, ElTypeGraph V);

#endif
