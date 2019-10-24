/* ADT Status */

#ifndef STATUS_H
#define STATUS_H

#include "boolean.h"
#include "array.h"
#include "matriks.h"
#include "stack.h"

/* Definisi elemen dan koleksi objek */
typedef struct {
    Matriks Peta;               // Peta game
    Stack StatusPemain;         // Status Pemain turn ini
    int ActivePlayer;           // Player aktif turn ini, 1 atau 2
    int Turn;                   // Urutan turn saat ini
} Status;

/* Kamus umum */
extern Status GameStatus;

/*** Selektor ***/
#define Peta(S) (S).Peta
#define StatusPemain(S) (S).StatusPemain
#define ActivePlayer(S) (S).ActivePlayer
#define Turn(S) (S).Turn

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
void InitGameStatus (int NBMatriks, int NKMatriks, int MaxElTab);
/* I.S. GameStatus sembarang */
/* F.S. Status GameStatus terdefinisi */
/* Proses: Melakukan alokasi, memanfaatkan konstruktor tiap komponen Status.
           ActivePlayer = 1. Turn = 1. */

#endif // STATUS_H
