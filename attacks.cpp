#include "data.h"


/// look up arrays for vector attacks
constexpr int8_t KNIGHT_ATTACK[240] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,NNW,  0,NNE,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,NWW,  0,  0,  0,NEE,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,SWW,  0,  0,  0,SEE,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,SSW,  0,SSE,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

constexpr int8_t BISHOP_ATTACK[240] =
{
    0, NW,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, NE,
    0,  0, NW,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, NE,  0,
    0,  0,  0, NW,  0,  0,  0,  0,  0,  0,  0,  0,  0, NE,  0,  0,
    0,  0,  0,  0, NW,  0,  0,  0,  0,  0,  0,  0, NE,  0,  0,  0,
    0,  0,  0,  0,  0, NW,  0,  0,  0,  0,  0, NE,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, NW,  0,  0,  0, NE,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, NW,  0, NE,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, SW,  0, SE,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, SW,  0,  0,  0, SE,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, SW,  0,  0,  0,  0,  0, SE,  0,  0,  0,  0,
    0,  0,  0,  0, SW,  0,  0,  0,  0,  0,  0,  0, SE,  0,  0,  0,
    0,  0,  0, SW,  0,  0,  0,  0,  0,  0,  0,  0,  0, SE,  0,  0,
    0,  0, SW,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, SE,  0,
    0, SW,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, SE
};

constexpr int8_t ROOK_ATTACK[240] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0,  0,
    0,  W,  W,  W,  W,  W,  W,  W,  0,  E,  E,  E,  E,  E,  E,  E,
    0,  0,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0,  0
};

constexpr int8_t QUEEN_ATTACK[240] =
{
    0, NW,  0,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0,  0, NE,
    0,  0, NW,  0,  0,  0,  0,  0,  N,  0,  0,  0,  0,  0, NE,  0,
    0,  0,  0, NW,  0,  0,  0,  0,  N,  0,  0,  0,  0, NE,  0,  0,
    0,  0,  0,  0, NW,  0,  0,  0,  N,  0,  0,  0, NE,  0,  0,  0,
    0,  0,  0,  0,  0, NW,  0,  0,  N,  0,  0, NE,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, NW,  0,  N,  0, NE,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, NW,  N, NE,  0,  0,  0,  0,  0,  0,
    0,  W,  W,  W,  W,  W,  W,  W,  0,  E,  E,  E,  E,  E,  E,  E,
    0,  0,  0,  0,  0,  0,  0, SW,  S, SE,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, SW,  0,  S,  0, SE,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, SW,  0,  0,  S,  0,  0, SE,  0,  0,  0,  0,
    0,  0,  0,  0, SW,  0,  0,  0,  S,  0,  0,  0, SE,  0,  0,  0,
    0,  0,  0, SW,  0,  0,  0,  0,  S,  0,  0,  0,  0, SE,  0,  0,
    0,  0, SW,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0, SE,  0,
    0, SW,  0,  0,  0,  0,  0,  0,  S,  0,  0,  0,  0,  0,  0, SE
};

constexpr int8_t KING_ATTACK[240] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, NW,  N, NE,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  W,  0,  E,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, SW,  S, SE,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

constexpr uint8_t OFFSET{120};

bool is_attacked(uint8_t square, unsigned short by_side)
{
    if(by_side == WHITE)
    {
        for(unsigned short i = wKS; i < wKE; ++i)
        {
            if(piece_list[i].captured) continue;
            if(KNIGHT_ATTACK[OFFSET + piece_list[i].square - square])  return true;
        }
        for(unsigned short i = wBS; i < wBE; ++i)
        {
            if(piece_list[i].captured) continue;
            int8_t incr = BISHOP_ATTACK[OFFSET + piece_list[i].square - square];
            if(incr)
            {
                for(uint8_t next = square + incr; !(board[next] & NOT_WB_NOT_EMPTY); next += incr)
                {
                    if(next == piece_list[i].square) return true;
                }
            }
        }
        for(unsigned short i = wRS; i < wRE; ++i)
        {
            if(piece_list[i].captured) continue;
            int8_t incr = ROOK_ATTACK[OFFSET + piece_list[i].square - square];
            if(incr)
            {
                for(uint8_t next = square + incr; !(board[next] & NOT_WR_NOT_EMPTY); next += incr)
                {
                    if(next == piece_list[i].square) return true;
                }
            }
        }
        for(unsigned short i = wQS; i < wQE; ++i)
        {
            if(piece_list[i].captured) continue;
            int8_t incr = QUEEN_ATTACK[OFFSET + piece_list[i].square - square];
            if(incr)
            {
                for(uint8_t next = square + incr; !(board[next] & NOT_WQ_NOT_EMPTY); next += incr)
                {
                    if(next == piece_list[i].square) return true;
                }
            }
        }
        if(KING_ATTACK[OFFSET + piece_list[wKING].square - square])        return true;
        if(!(board[square + SE] & NOT_WP))   return true;
        if(!(board[square + SW] & NOT_WP))   return true;
    }
    else
    {
        for(unsigned short i = bKS; i < bKE; ++i)
        {
            if(piece_list[i].captured) continue;
            if(KNIGHT_ATTACK[OFFSET + piece_list[i].square - square])  return true;
        }
        for(unsigned short i = bBS; i < bBE; ++i)
        {
            if(piece_list[i].captured) continue;
            int8_t incr = BISHOP_ATTACK[OFFSET + piece_list[i].square - square];
            if(incr)
            {
                for(uint8_t next = square + incr; !(board[next] & NOT_BB_NOT_EMPTY); next += incr)
                {
                    if(next == piece_list[i].square) return true;
                }
            }
        }
        for(unsigned short i = bRS; i < bRE; ++i)
        {
            if(piece_list[i].captured) continue;
            int8_t incr = ROOK_ATTACK[OFFSET + piece_list[i].square - square];
            if(incr)
            {
                for(uint8_t next = square + incr; !(board[next] & NOT_BR_NOT_EMPTY); next += incr)
                {
                    if(next == piece_list[i].square) return true;
                }
            }
        }
        for(unsigned short i = bQS; i < bQE; ++i)
        {
            if(piece_list[i].captured) continue;
            int8_t incr = QUEEN_ATTACK[OFFSET + piece_list[i].square - square];
            if(incr)
            {
                for(uint8_t next = square + incr; !(board[next] & NOT_BQ_NOT_EMPTY); next += incr)
                {
                    if(next == piece_list[i].square) return true;
                }
            }
        }
        if(KING_ATTACK[OFFSET + piece_list[bKING].square - square])         return true;
        if(!(board[square + NE] & NOT_BP))    return true;
        if(!(board[square + NW] & NOT_BP))    return true;
    }
    return false;
}
