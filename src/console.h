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

boolean AttackCommand();
boolean LevelUpCommand();
boolean EndTurnCommand();
boolean MoveCommand();
void HelpCommand();
void BuildingsCommand();
boolean UndoCommand();

int GetBuildingID(int choice);

#endif // CONSOLE_H
