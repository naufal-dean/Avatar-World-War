#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*** Konstruktor ***/
void MakeEmptyQueue (Queue * Q, int Max) {
/* I.S. Q sembarang */
/* F.S. Jika alokasi berhasil, tabel memori dialokasi berukuran Max + 1
Jika alokasi gagal, Q kosong dan MaxElQueue(Q) = 0 */
/* Proses: Melakukan alokasi, membuat sebuah Q kosong */
    // Algoritma
    (*Q).T = (ElTypeQueue*) malloc ((Max + 1) * sizeof(ElTypeQueue));
    if ((*Q).T == NULL) {
        MaxElQueue(*Q) = 0;
    } else {
        MaxElQueue(*Q) = Max;
    }
    Head(*Q) = NilQueue;
    Tail(*Q) = NilQueue;
}

/*** Destruktor ***/
void DealokasiQueue(Queue * Q) {
/* I.S. Q terdefinisi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQueue(Q) = 0 */
/* Proses: Memori Q dikembalikan ke system */
    // Algoritma
    free((*Q).T);
    Head(*Q) = NilQueue;
    Tail(*Q) = NilQueue;
    MaxElQueue(*Q) = 0;
}

/*** Selektor Tambahan ***/
int NBElmtQueue (Queue Q) {
/* Mengembalikan jumlah elemen efektif Q, 0 jika Q kosong */
    // Kamus lokal
    int count;
    // Algoritma
    count = (IsQueueEmpty(Q)) ? (0) : (((Tail(Q) - Head(Q) + MaxElQueue(Q)) % MaxElQueue(Q)) + 1);
    return (count);
}

/*** Kelompok tes queue kosong / penuh ***/
boolean IsQueueEmpty (Queue Q) {
/* Mengembalikan true jika Q kosong, mengirimkan false jika tidak */
    return ((Head(Q) == NilQueue) && (Tail(Q) == NilQueue));
}
boolean IsQueueFull (Queue Q) {
/* Mengembalikan true jika Q penuh, mengirimkan false jika tidak */
    return ((Tail(Q) % MaxElQueue(Q)) + 1 == Head(Q));
}

/*** Kelompok Add dan Del elemen ***/
void AddElQueue (Queue * Q, ElTypeQueue X) {
/* Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q boleh kosong, tetapi tidak penuh */
/* F.S. X menjadi elemen di Tail yang baru,
Tail "maju" dengan mekanisme circular buffer */
    // Algoritma
    if (IsQueueEmpty(*Q)) {
        Head(*Q) = 1;
        Tail(*Q) = 1;
    } else { // Not empty
        Tail(*Q) = (Tail(*Q) % MaxElQueue(*Q)) + 1;
    }
    InfoTail(*Q) = X;
}
void DelElQueue (Queue * Q, ElTypeQueue * X) {
/* Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak kosong */
/* F.S. X adalah nilai elemen Head Q sebelum penghapusan,
Head "maju" dengan mekanisme circular buffer.
Q mungkin menjadi kosong */
    // Algoritma
    (*X) = InfoHead(*Q);
    if (NBElmtQueue(*Q) == 1) {
        Head(*Q) = NilQueue;
        Tail(*Q) = NilQueue;
    } else { // NBElmtQueue(*Q) > 1
        Head(*Q) = (Head(*Q) % MaxElQueue(*Q)) + 1;
    }
}

/*** Kelompok operasi lain ***/
void CopyQueue(Queue * Qout, Queue Qin) {
/* Melakukan penyalinan Qin ke Qout */
/* I.S. Qin terdefinisi, Qout sembarang */
/* F.S. Semua elemen yang terdefinisi Qout sama dengan Qin,
        Head dan Tail mungkin berbeda */
    // Kamus lokal
    ElTypeQueue X;
    // Algoritma
    MakeEmptyQueue(Qout, MaxElQueue(Qin));
    while (!IsQueueEmpty(Qin)) {
        DelElQueue(&Qin, &X);
        AddElQueue(Qout, X);
    }
}
