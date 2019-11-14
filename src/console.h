#ifndef CONSOLE_H
#define CONSOLE_H

#include "header/array.h"
#include "header/bangunan.h"
#include "header/boolean.h"
#include "header/graph.h"
#include "header/kata.h"
#include "header/listlinier.h"
#include "header/matriks.h"
#include "header/mesinkar.h"
#include "header/mesinkata.h"
#include "header/pcolor.h"
#include "header/point.h"
#include "header/queue.h"
#include "header/stack.h"
#include "header/status.h"

/*** Kelompok Fungsi Command ***/
boolean AttackCommand();
/* Melaksanakan command ATTACK */
/* Mengembalikan true jika attack berhasil, dan sebaliknya */
boolean LevelUpCommand();
/* Melaksanakan command LEVEL_UP */
/* Mengembalikan true jika level up berhasil, dan sebaliknya */
boolean UndoCommand();
/* Melaksanakan command UNDO */
/* Selalu mengembalikan true, karena undo selalu berhasil */
boolean EndTurnCommand();
/* Melaksanakan command END_TURN */
/* Selalu mengembalikan true, karena end turn selalu berhasil */
void SaveCommand();
/* Melaksanakan command SAVE */
/* I.S. GameStatus terdefinisi */
/* F.S. Melakukan proses penyimpanan GameStatus ke path file yang diberikan */
void LoadCommand();
/* Melaksanakan command LOAD */
/* I.S. GameStatus sembarang, file load terdefinisi dan valid */
/* F.S. Melakukan proses loading data pada file load yang diberikan ke GameStatus */
boolean MoveCommand();
/* Melaksanakan command MOVE */
/* Mengembalikan true jika move berhasil, dan sebaliknya */
void HelpCommand();
/* Melaksanakan command HELP */
/* I.S. Kondisi sembarang */
/* F.S. Menampilkan panel bantuan ke layar */
void BuildingsCommand();
/* Melaksanakan command BUILDINGS */
/* I.S. GameStatus terdefinisi */
/* F.S. Menampilkan list Bangunan ke layar */

#endif // CONSOLE_H
