
#ifndef support_h
#define support_h

#include <stdio.h>
#include "provided.h"



int opp(int color);
// Returns true if the game is over (win or tie).
bool isDone(const Scaffold& s, int N, int& winner);

#endif

