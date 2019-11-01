/*** ADT LIST LINIER ***/
/* List menggunakan representasi fisik pointer */

#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"
#include <stddef.h>
#include <stdlib.h>

/* Kamus Umum */
#define NilList NULL

typedef int ElTypeList;	// Info elemen list berupa type bentukan "Bangunan"
typedef struct tElmtlist *AddressList;	// Alamat elemen list
typedef struct tElmtlist {
	ElTypeList Info;
	AddressList FirstAdj;	// Alamat pertama adj list, berisi alamat bila elemen tersebut merupakan U dan Nil bila elemen tersebut merupakan V
	AddressList Next;
} ElmtList;
typedef struct {
	AddressList First;	// Alamat pertama list
} List;

/* Definisi list : */
/* List kosong : First(L) = NilList */
/* Setiap elemen dengan AddressList P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika AddressListnya Last, maka Next(Last)=NilList */

#define Info(P) (P)->Info
#define FirstAdj(P) (P)->FirstAdj
#define Next(P) (P)->Next
#define First(L) ((L).First)

AddressList Alokasi (ElTypeList X);

boolean IsEmpty (List *L);

boolean IsU (AddressList P);

void CreateEmptyList (List *L);

void Insert (List *L, ElTypeList X);

boolean AdaEdge(List L, ElTypeList U, ElTypeList V);

#endif
