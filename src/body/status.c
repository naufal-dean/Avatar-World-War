#include <stdio.h>
#include "../header/status.h"

Status GameStatus;

/*** Konstruktor ***/
void InitGameStatus (int NBMatriks, int NKMatriks, int MaxElTab) {
/* I.S. GameStatus sembarang */
/* F.S. Status GameStatus terdefinisi */
/* Proses: Melakukan alokasi, memanfaatkan konstruktor tiap komponen Status.
           ActivePlayer = 1. Turn = 1. */
    // Algoritma
    MakeMatriks(NBMatriks, NKMatriks, &Peta(GameStatus));
    MakeEmptyTab(&ListBangunan(GameStatus), MaxElTab);
    MakeEmptyStack(&StatusPemain(GameStatus));
    ActivePlayer(GameStatus) = 1;
    Turn(GameStatus) = 1;
}
