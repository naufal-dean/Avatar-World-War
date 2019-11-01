/*** ADT LIST LINIER ***/
/* List menggunakan representasi fisik pointer */

#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"
#include <stddef.h>
#include <stdlib.h>

/* Kamus Umum */
#define NilGraph NULL
#define DummyElGraph 0

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

/*** Konstruktor ***/
void MakeEmptyGraph (Graph *G);
/* Menginisialisasi graph kosong */
/* I.S. G sembarang */
/* F.S. Terbentuk Graph kosong, FirstG(G) = NilGraph */

AddressGraph AlokasiElGraph (ElTypeGraph X);
/* Melakukan alokasi terhadap suatu elemen graph */

/*** Kelompok tes Graph kosong ***/
boolean IsGraphEmpty (Graph G);
/* Mengeluarkan true apabila graph kosong, dan false bila tidak */

/*** Kelompok insert dan cek elemen Graph ***/
void InsertElGraph (Graph *G, ElTypeGraph U, ElTypeGraph V);
/* Menambahkan elemen ke dalam Graph */
/* Jika V == DummyElGraph, maka menambahkan elemen V di dalam list adj U */
/* Jika V != DummyElGraph, maka menambahkan elemen U di dalam G */

boolean AdaEdge(Graph G, ElTypeGraph U, ElTypeGraph V);
/* Mengeluarkan true bila ada edge dari vertex U ke V */

/*** Kelompok operasi OUTPUT ***/
void TulisGraph (Graph G);
/* Menuliskan isi G ke layar */
/* I.S. Graph G terdefinisi */
/* F.S. Isi Graph G dituliskan ke layar */

/*** Kelompok operasi lain ***/
void CopyGraph(Graph * Gout, Graph Gin);
/* Melakukan penyalinan Gin ke Gout */
/* I.S. Gin terdefinisi, Gout sembarang */
/* F.S. Gout memiliki properti yang sama dengan Gin */

#endif
