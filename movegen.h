#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "data.h"


void gen_push(Move *moveList, uint8_t from, uint8_t to, unsigned short capture, uint8_t ep, uint8_t castle, uint8_t &moveCount);

void gen_promote(Move *moveList, uint8_t from, uint8_t to, unsigned short capture, uint8_t ep, uint8_t castle, uint8_t &move_Count);

uint8_t generate_all(Move *moveList, const Position &currentPos);

uint8_t generate_caps(Move *moveList, const Position &currentPos);


#endif // MOVEGEN_H_INCLUDED
