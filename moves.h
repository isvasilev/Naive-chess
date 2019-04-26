#ifndef MOVES_H_INCLUDED
#define MOVES_H_INCLUDED

#include "data.h"


void put_piece(uint8_t square, unsigned short index);

void make_move(Move move, Position &next_position);

void unmake_move(Move move);


#endif // MOVES_H_INCLUDED
