#include <stdio.h>
#include <stdlib.h>
#include "../header/queue.h"

/*** Konstruktor ***/
void MakeEmptyQueue (Queue * Q, int Max) {
/* I.S. Q sembarang */
/* F.S. Jika alokasi berhasil, tabel memori dialokasi berukuran Max + 1
Jika alokasi gagal, Q kosong dan MaxElQ(Q) = 0 */
/* Proses: Melakukan alokasi, membuat sebuah Q kosong */
    // Algoritma
    (*Q).T = (ElTypeQ*) malloc ((Max + 1) * sizeof(ElTypeQ));
    if ((*Q).T == NULL) {
        MaxElQ(*Q) = 0;
    } else {
        MaxElQ(*Q) = Max;
    }
    Head(*Q) = NilQ;
    Tail(*Q) = NilQ;
}

/*** Destruktor ***/
void DealokasiQueue(Queue * Q) {
/* I.S. Q terdefinisi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQ(Q) = 0 */
/* Proses: Memori Q dikembalikan ke system */
    // Algoritma
    free((*Q).T);
    Head(*Q) = NilQ;
    Tail(*Q) = NilQ;
    MaxElQ(*Q) = 0;
}

/*** Selektor Tambahan ***/
int NBElmt (Queue Q) {
/* Mengembalikan jumlah elemen efektif Q, 0 jika Q kosong */
    // Kamus lokal
    int count;
    // Algoritma
    count = (IsQueueEmpty(Q)) ? (0) : (((Tail(Q) - Head(Q) + MaxElQ(Q)) % MaxElQ(Q)) + 1);
    return (count);
}

/*** Kelompok tes queue kosong / penuh ***/
boolean IsQueueEmpty (Queue Q) {
/* Mengembalikan true jika Q kosong, mengirimkan false jika tidak */
    return ((Head(Q) == NilQ) && (Tail(Q) == NilQ));
}
boolean IsQueueFull (Queue Q) {
/* Mengembalikan true jika Q penuh, mengirimkan false jika tidak */
    return ((Tail(Q) % MaxElQ(Q)) + 1 == Head(Q));
}

/*** Kelompok Add dan Del elemen ***/
void AddElQueue (Queue * Q, ElTypeQ X) {
/* Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q boleh kosong, tetapi tidak penuh */
/* F.S. X menjadi elemen di Tail yang baru,
Tail "maju" dengan mekanisme circular buffer */
    // Algoritma
    if (IsQueueEmpty(*Q)) {
        Head(*Q) = 1;
        Tail(*Q) = 1;
        InfoTail(*Q) = X;
    } else { // Not empty
        Tail(*Q) = (Tail(*Q) % MaxElQ(*Q)) + 1;
        InfoTail(*Q) = X;
    }
}
void DelElQueue (Queue * Q, ElTypeQ * X) {
/* Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak kosong */
/* F.S. X adalah nilai elemen Head Q sebelum penghapusan,
Head "maju" dengan mekanisme circular buffer.
Q mungkin menjadi kosong */
    // Algoritma
    if (NBElmt(*Q) == 1) {
        (*X) = InfoHead(*Q);
        Head(*Q) = NilQ;
        Tail(*Q) = NilQ;
    } else { // NBElmt(*Q) > 1
        (*X) = InfoHead(*Q);
        Head(*Q) = (Head(*Q) % MaxElQ(*Q)) + 1;
    }
}
