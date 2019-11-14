/* ADT Status */

#ifndef STATUS_H
#define STATUS_H

#include "boolean.h"
#include "array.h"
#include "bangunan.h"
#include "graph.h"
#include "kata.h"
#include "matriks.h"
#include "mesinkata.h"
#include "point.h"
#include "queue.h"
#include "stack.h"
#include "graph.h"

/* Definisi elemen dan koleksi objek */
typedef struct {
    int NBPeta, NKPeta, NBangunan;  // Baris, kolom, dan jumlah bangunan
    TabBangunan T;              // Tabel bangunan
    Queue Q1, Q2;               // List skill
    Matriks Peta;               // Peta game
    Graph Adjacency;            // Adjacency Bangunan pada game
    Stack StatusPemain;         // Status Pemain turn ini
                                // Mengandung ListBangunan dan Queue Skill
    TabSkill S1, S2;            // List skill aktif
    int ActivePlayer;           // Player aktif turn ini, 1 atau 2
    int Turn;                   // Urutan turn saat ini
} Status;

/* Kamus umum */
extern Status GameStatus;

/*** Selektor ***/
#define NBPeta(S) (S).NBPeta
#define NKPeta(S) (S).NKPeta
#define NBangunan(S) (S).NBangunan

#define T(S) (S).T
#define Q1(S) (S).Q1
#define Q2(S) (S).Q2
#define Peta(S) (S).Peta
#define Adjacency(S) (S).Adjacency
#define StatusPemain(S) (S).StatusPemain

#define S1(S) (S).S1
#define ElmtS1(S, i) ((S).S1)[(i)]
#define S2(S) (S).S2
#define ElmtS2(S, i) ((S).S2)[(i)]

#define ActivePlayer(S) (S).ActivePlayer
#define Turn(S) (S).Turn

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
void InitGameStatus (int NBPeta, int NKPeta, int NBangunan);
/* I.S. GameStatus sembarang */
/* F.S. Status GameStatus terdefinisi */
/* Proses: Melakukan alokasi, memanfaatkan konstruktor tiap komponen Status.
           ActivePlayer = 1. Turn = 1. */

/*** Setup ***/
void SetupConfigGameStatus(char * ConfigPath, int * error);
/* I.S. GameStatus terdefinisi
        Isi file config terdefinisi, jumlah bangunan >= 2, ukuran map valid */
/* F.S. Isi GameStatus sesuai dengan config */
/* Proses: Melakukan setup GameStatus sesuai isi file di ConfigPath */
Bangunan ParseInputBangunan(int ID);
/* Mengembalikan Bangunan sesuai input pada file
   Format input: "Tipe Lokasi(X) Lokasi(Y)"
   CKata awal ada di Tipe, CKata akhir ada di Lokasi(Y) */

/*** Save dan Load Game ***/
void SaveGameStatus(char * SavePath);
/* I.S. GameStatus terdefinisi */
/* F.S. Isi GameStatus tersimpan dalam file di SavePath */
/* Proses:  Melakukan penulisan isi GameStatus ke file di GameStatus
            Tidak menyimpan status undo */
void LoadGameStatus(char * LoadPath, int * error);
/* I.S. GameStatus terdefinisi
        Isi file load terdefinisi, jumlah bangunan >= 2, ukuran map valid */
/* F.S. Isi GameStatus sesuai dengan load */
/* Proses:  Melakukan setup GameStatus sesuai isi file di LoadPath
            Memanfaatkan prosedur SetupConfigGameStatus */

#endif // STATUS_H
