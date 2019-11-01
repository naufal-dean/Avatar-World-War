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
/* Melakukan alokasi terhadap suatu elemen graph */

boolean IsEmptyGraph (Graph G);
/* Mengeluarkan true apabila graph kosong, dan false bila tidak */

void CreateEmptyGraph (Graph *G);
/* Menginisialisasi graph kosong */

void InsertGraph (Graph *G, ElTypeGraph U, ElTypeGraph V);
/* Menambahkan elemen ke dalam Graph */
/* Jika V == 0, maka menambahkan elemen V di dalam list adj U */
/* Jika V != 0, maka menambahkan elemen U di dalam G */

boolean AdaEdge(Graph G, ElTypeGraph U, ElTypeGraph V);
/* Mengeluarkan true bila ada edge dari vertex U ke V */

void PrintGraph (Graph G);
/* Mengeluarkan isi hraph */

#endif
