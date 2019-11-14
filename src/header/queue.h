/*** ADT Queue ***/
/* Memori tabel dinamik, head dan tail eksplisit */
/* Implementasi memakai model circular buffer */

#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"
#include "kata.h"

/* Kamus Umum */
#define NilQueue 0     // alamat tidak terdefinisi
// Nilai ElTypeQueue valid
#define INSTANT_UPGRADE 1
#define SHIELD 2
#define EXTRA_TURN 3
#define ATTACK_UP 4
#define CRITICAL_HIT 5
#define INSTANT_REINFORCEMENT 6
#define BARRAGE 7

/* Definisi elemen dan koleksi objek */
typedef int ElTypeQueue;    // nilai ElTypeQueue valid adalah yang terdefinisi di kamus umum
typedef int AddressQueue;
typedef struct {
    ElTypeQueue * T;        // container elemen
    AddressQueue Head;      // alamat penghapusan
    AddressQueue Tail;      // alamat penambahan
    int MaxEl;              // elemen maksimum yang bisa ditampung
} Queue;
/* Definisi:
   Queue kosong: Head = Nil; Tail = Nil */
/* Indeks 0 tidak dipakai */

/*** Selektor ***/
#define Head(Q) (Q).Head
#define Tail(Q) (Q).Tail
#define InfoHead(Q) (Q).T[(Q).Head]
#define InfoTail(Q) (Q).T[(Q).Tail]
#define MaxElQueue(Q) (Q).MaxEl

/* DEFINISI PROTOTIPE PRIMITIF */
/*** Konstruktor ***/
void MakeEmptyQueue (Queue * Q, int Max);
/* I.S. Q sembarang */
/* F.S. Jika alokasi berhasil, tabel memori dialokasi berukuran Max + 1
        Jika alokasi gagal, Q kosong dan MaxEl(Q) = 0 */
/* Proses: Melakukan alokasi, membuat sebuah Q kosong */

/*** Destruktor ***/
void DealokasiQueue(Queue * Q);
/* I.S. Q terdefinisi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) = 0 */
/* Proses: Memori Q dikembalikan ke system */

/*** Selektor Tambahan ***/
int NBElmtQueue (Queue Q);
/* Mengembalikan jumlah elemen efektif Q, 0 jika Q kosong */

/*** Kelompok tes queue kosong / penuh ***/
boolean IsQueueEmpty (Queue Q);
/* Mengembalikan true jika Q kosong, mengirimkan false jika tidak */
boolean IsQueueFull (Queue Q);
/* Mengembalikan true jika Q penuh, mengirimkan false jika tidak */

/*** Kelompok Add dan Del elemen ***/
void AddElQueue (Queue * Q, ElTypeQueue X);
/* Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q boleh kosong, tetapi tidak penuh */
/* F.S. X menjadi elemen di Tail yang baru,
        Tail "maju" dengan mekanisme circular buffer */
void DelElQueue (Queue * Q, ElTypeQueue * X);
/* Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak kosong */
/* F.S. X adalah nilai elemen Head Q sebelum penghapusan,
        Head "maju" dengan mekanisme circular buffer.
        Q mungkin menjadi kosong */

/*** Kelompok operasi lain ***/
void CopyQueue(Queue * Qout, Queue Qin);
/* Melakukan penyalinan Qin ke Qout */
/* I.S. Qin terdefinisi, Qout sembarang */
/* F.S. Semua elemen yang terdefinisi Qout sama dengan Qin,
        Head dan Tail mungkin berbeda */

#endif // QUEUE_H
