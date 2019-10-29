/*** ADT LIST LINIER ***/
/* List menggunakan representasi fisik pointer */

#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"

/* Kamus Umum */
#define NilList NULL

typedef int ElTypeUList;    // U vertex
typedef int ElTypeVList;    // V vertex
typedef struct tElmtUlist *AddressUList;	// Alamat elemen list U
typedef struct tElmtFirstVlist *AddressFirstVList;	// Alamat elemen pertama list V
typedef struct tElmtVlist *AddressVList;	// Alamat elemen list V

typedef struct tElmtUlist {
	ElTypeUList InfoU;
    AddressFirstVList FirstV;
	AddressUList NextU;
} ElmtUList;
typedef struct tElmtVlist {
	ElTypeVList InfoV;
	AddressVList NextV;
} ElmtVList;
typedef struct {
	AddressUList FirstU;	// Alamat pertama list U
} UList;
typedef struct {
	AddressVList FirstV;	// Alamat pertama list V
} VList;

/* Definisi list : */
/* List kosong : First(L) = NilList */
/* Setiap elemen dengan AddressList P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika AddressListnya Last, maka Next(Last)=NilList */

#define InfoU(P) (P)->InfoU
#define InfoV(P) (P)->InfoV
#define FirstU(P) (P)->FirstU
#define FirstV(P) (P)->FirstV
#define NextU(P) (P)->NextU
#define NextU(P) (P)->NextV

void CreateEmptyUList (UList *L);

void CreateEmptyVList (VList *L);


#endif // LISTLINIER_H
