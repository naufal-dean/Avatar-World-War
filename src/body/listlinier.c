#include "../header/listlinier.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */
/* TEST LIST KOSONG */
boolean IsEmptyList (List L){
/* Mengirim true jika list kosong */
    return(First(L)==NilList);
}

/* PEMBUATAN LIST KOSONG */
void CreateEmptyList (List *L){
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
    First(*L)=NilList;
}

/* Manajemen Memori */
address AlokasiElList (infotype X){
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
    // Kamus lokal
    address P;
    // Algoritma
    P=(ElmtList *)malloc(sizeof(ElmtList));
    if(P!=NilList){
        Info(P)=X;
        Next(P)=NilList;
    }
    return P;
}
void DealokasiElList (address *P){
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
    free(*P);
}
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address SearchInfo (List L, infotype X){
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
    // Kamus lokal
    address P;
    boolean found;
    // Algoritma
    found=false;
    P=First(L);
    while(P!=NilList && !found){
        if(Tipe(Info(P))==Tipe(X) && Pemilik(Info(P))==Pemilik(X)){ //ini ngesearchnya berdasarkan apa ya ?
            found=true;
        }
        else{
            P=Next(P);
        }
    }
    return P;
}

/*** PRIMITIF BERDASARKAN NILAI ***/
/* PENAMBAHAN ELEMEN */
void InsVFirst (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
    // Kamus lokal
    address P;
    // Algoritma
    P=AlokasiElList(X);
    if(P!=NilList){
        InsertFirst(L,P);
    }
}
void InsVLast (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    // Kamus lokal
    address P;
    // Algoritma
    P=AlokasiElList(X);
    if(P!=NilList){
        InsertLast(L,P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X){
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
    // Kamus lokal
    address P;
    // Algoritma
    DelFirst(L,&P);
    *X=Info(P);
    DealokasiElList(&P);
}
void DelVLast (List *L, infotype *X){
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
    // Kamus lokal
    address P;
    // Algoritma
    DelLast(L,&P);
    *X=Info(P);
    DealokasiElList(&P);
}
/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
    Next(P)=First(*L);
    First(*L)=P;
}
void InsertAfter (List *L, address P, address Prec){
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
    Next(P)=Next(Prec);
    Next(Prec)=P;
}
void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
    // Kamus lokal
    address last;
    // Algoritma
    if(IsEmptyList(*L)){
        InsertFirst(L,P);
    }
    else{
        last=First(*L);
        while(Next(last)!=NilList){
            last=Next(last);
        }
        InsertAfter(L,P,last);
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
    // Algoritma
    *P=First(*L);
    First(*L)=Next(First(*L));
    Next(*P)=NilList;
}
void DelP (List *L, infotype X){
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
    // Kamus lokal
    address P,Prec;
    // Algoritma
    P=SearchInfo(*L,X);
    if(P!=NilList){
        Prec=First(*L);
        if(P==Prec){
            DelFirst(L,&P);
        }
        else{
            while(Next(Prec)!=P){
                Prec=Next(Prec);
            }
            DelAfter(L,&P,Prec);
        }
    }
}
void DelLast (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
    // Kamus lokal
    address last,prec;
    // Algoritma
    last=First(*L);
    prec=NilList;
    while(Next(last)!=NilList){
        prec=last;
        last=Next(last);
    }
    *P=last;
    if(prec==NilList){
        First(*L)=NilList;
    }
    else{
        Next(prec)=NilList;
    }
}
void DelAfter (List *L, address *Pdel, address Prec){
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
    // Algoritma
    *Pdel=Next(Prec);
    Next(Prec)=Next(Next(Prec));
    Next(*Pdel)=NilList;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    // Kamus lokal
    address P;
    if(IsEmptyList(L)){
        printf("[]");
    }
    else{
        P=First(L);
        printf("[");
        while(P!=NilList){
            TulisBangunan(Info(P));
            P=Next(P);
            if(P!=NilList){
                printf(",");
            }
        }
        printf("]");
    }
}
int NbElmtList (List L){
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    // Kamus lokal
    int count;
    address P;
    // Algoritma
    count=0;
    P=First(L);
    while(P!=NilList){
        count++;
        P=Next(P);
    }
    return count;
}
/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3){
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
    // Kamus lokal
    address P;
    // Algoritma
    P = First(*L1);
    CreateEmptyList(L3);
    if(P==NilList){
        First(*L3)=First(*L2);
        P=First(*L2);
        if(P!=NilList){
            while(Next(P)!=NilList){
                P=Next(P);
            }
        }
       while(P!=NilList){
           P=Next(P);
       }
    }
    else{
        First(*L3)=First(*L1);
        P=First(*L1);
        if(P!=NilList){
            while(Next(P)!=NilList){
                P=Next(P);
            }
        }
        Next(P)=First(*L2);
    }
    CreateEmptyList(L1);
    CreateEmptyList(L2);
}
