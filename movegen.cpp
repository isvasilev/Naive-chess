#include "attacks.h"
#include "data.h"


void gen_push(Move *moveList, uint8_t from, uint8_t to, unsigned short capture, uint8_t ep, uint8_t castle, uint8_t &moveCount)
{
    moveList[moveCount].from = from;
    moveList[moveCount].to = to;
    moveList[moveCount].capture = capture;
    if(capture) moveList[moveCount].order_score = piece_list[capture].mvv_lva * 10 - piece_list[board[from]].mvv_lva;
    moveList[moveCount].ep = ep;
    moveList[moveCount].flags += castle;
    moveList[moveCount].id = moveCount;
    ++moveCount;
}

void gen_promote(Move *moveList, uint8_t from, uint8_t to, unsigned short capture, uint8_t ep, uint8_t castle, uint8_t &moveCount)
{
   for(uint8_t i = 0; i < 4; ++i)
   {
       moveList[moveCount].from = from;
       moveList[moveCount].to = to;
       moveList[moveCount].capture = capture;
       moveList[moveCount].order_score = 55 - i;
       moveList[moveCount].ep = ep;
       moveList[moveCount].flags += castle;
       moveList[moveCount].flags += PROM_TYPE[i];
       moveList[moveCount].pawn = board[from];
       moveList[moveCount].id = moveCount;
       ++moveCount;
   }
}

uint8_t generate_all(Move *moveList, const Position &currentPos)
{
    uint8_t moveCount = 1;
    uint8_t square;
    uint8_t next;

    if(stm == WHITE)
    {
        for(unsigned short i = wPS; i < wPE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if(board[square + N] == EMPTY)
            {
                if(square + N < 76)             gen_promote(moveList, square, square + N, 0, 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + N, 0, 0, 0, moveCount);

                if(square > 163 && board[square + NN] == EMPTY) gen_push(moveList, square, square + NN, 0, square + N, 0, moveCount);
            }
            if(board[square + NE] & BLACK)
            {
                if(square + NE < 76)            gen_promote(moveList, square, square + NE, board[square + NE], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + NE, board[square + NE], 0, 0, moveCount);
            }
            if(board[square + NW] & BLACK)
            {
                if(square + NW < 76)            gen_promote(moveList, square, square + NW, board[square + NW], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + NW, board[square + NW], 0, 0, moveCount);
            }
        }
        for(unsigned short i = wKS; i < wKE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if      (board[square + NWW] == EMPTY)  gen_push(moveList, square, square + NWW,                   0, 0, 0, moveCount);
            else if (board[square + NWW] & BLACK)   gen_push(moveList, square, square + NWW, board[square + NWW], 0, 0, moveCount);
            if      (board[square + NNW] == EMPTY)  gen_push(moveList, square, square + NNW,                   0, 0, 0, moveCount);
            else if (board[square + NNW] & BLACK)   gen_push(moveList, square, square + NNW, board[square + NNW], 0, 0, moveCount);
            if      (board[square + NNE] == EMPTY)  gen_push(moveList, square, square + NNE,                   0, 0, 0, moveCount);
            else if (board[square + NNE] & BLACK)   gen_push(moveList, square, square + NNE, board[square + NNE], 0, 0, moveCount);
            if      (board[square + NEE] == EMPTY)  gen_push(moveList, square, square + NEE,                   0, 0, 0, moveCount);
            else if (board[square + NEE] & BLACK)   gen_push(moveList, square, square + NEE, board[square + NEE], 0, 0, moveCount);
            if      (board[square + SEE] == EMPTY)  gen_push(moveList, square, square + SEE,                   0, 0, 0, moveCount);
            else if (board[square + SEE] & BLACK)   gen_push(moveList, square, square + SEE, board[square + SEE], 0, 0, moveCount);
            if      (board[square + SSE] == EMPTY)  gen_push(moveList, square, square + SSE,                   0, 0, 0, moveCount);
            else if (board[square + SSE] & BLACK)   gen_push(moveList, square, square + SSE, board[square + SSE], 0, 0, moveCount);
            if      (board[square + SSW] == EMPTY)  gen_push(moveList, square, square + SSW,                   0, 0, 0, moveCount);
            else if (board[square + SSW] & BLACK)   gen_push(moveList, square, square + SSW, board[square + SSW], 0, 0, moveCount);
            if      (board[square + SWW] == EMPTY)  gen_push(moveList, square, square + SWW,                   0, 0, 0, moveCount);
            else if (board[square + SWW] & BLACK)   gen_push(moveList, square, square + SWW, board[square + SWW], 0, 0, moveCount);
        }
        for(unsigned short i = wBS; i < wBE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 4; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & WHITE_OR_OUT); next += INCR[i])
                {
                    if (board[next] == EMPTY)   gen_push(moveList, square, next,           0, 0, 0, moveCount);
                    else                       {gen_push(moveList, square, next, board[next], 0, 0, moveCount); break;}
                }
            }
        }
        for(unsigned short i = wRS; i < wRE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 4; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & WHITE_OR_OUT); next += INCR[i])
                {
                    if (board[next] == EMPTY)   gen_push(moveList, square, next,           0, 0, 0, moveCount);
                    else                       {gen_push(moveList, square, next, board[next], 0, 0, moveCount); break;}
                }
            }
        }
        for(unsigned short i = wQS; i < wQE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & WHITE_OR_OUT); next += INCR[i])
                {
                    if (board[next] == EMPTY)   gen_push(moveList, square, next,           0, 0, 0, moveCount);
                    else                       {gen_push(moveList, square, next, board[next], 0, 0, moveCount); break;}
                }
            }
        }
        square = piece_list[wKING].square;
        for(uint8_t i = 0 ; i < 8; ++i)
        {
            next = square + INCR[i];
            if (board[next] == EMPTY)   {gen_push(moveList, square, next,           0, 0, 0, moveCount); continue;}
            if (board[next] & BLACK)     gen_push(moveList, square, next, board[next], 0, 0, moveCount);
        }
        if(currentPos.castle & WCS && board[F1] == EMPTY && board[G1] == EMPTY
            && !(is_attacked(E1, stm ^ SIDE_SWITCH)) && !(is_attacked(F1, stm ^ SIDE_SWITCH)) && !(is_attacked(G1, stm ^ SIDE_SWITCH)))
            gen_push(moveList, E1, G1, 0, 0, WCS, moveCount);
        if(currentPos.castle & WCL && board[B1] == EMPTY && board[C1] == EMPTY && board[D1] == EMPTY
            && !(is_attacked(E1, stm ^ SIDE_SWITCH)) && !(is_attacked(C1, stm ^ SIDE_SWITCH)) && !(is_attacked(D1, stm ^ SIDE_SWITCH)))
            gen_push(moveList, E1, C1, 0, 0, WCL, moveCount);
    }
    else
    {
        for(unsigned short i = bPS; i < bPE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if(board[square + S] == EMPTY)
            {
                if(square + S > 179)            gen_promote(moveList, square, square + S, 0, 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + S, 0, 0, 0, moveCount);

                if(square < 92 && board[square + SS] == EMPTY ) gen_push(moveList, square, square + SS, 0, square + S, 0, moveCount);
            }
            if(board[square + SE] & WHITE)
            {
                if(square + SE > 179)           gen_promote(moveList, square, square + SE, board[square + SE], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + SE, board[square + SE], 0, 0, moveCount);
            }
            if(board[square + SW] & WHITE)
            {
                if(square + SW > 179)           gen_promote(moveList, square, square + SW, board[square + SW], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + SW, board[square + SW], 0, 0, moveCount);
            }
        }
        for(unsigned short i = bKS; i < bKE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if      (board[square + NWW] == EMPTY)  gen_push(moveList, square, square + NWW,                   0, 0, 0, moveCount);
            else if (board[square + NWW] & WHITE)   gen_push(moveList, square, square + NWW, board[square + NWW], 0, 0, moveCount);
            if      (board[square + NNW] == EMPTY)  gen_push(moveList, square, square + NNW,                   0, 0, 0, moveCount);
            else if (board[square + NNW] & WHITE)   gen_push(moveList, square, square + NNW, board[square + NNW], 0, 0, moveCount);
            if      (board[square + NNE] == EMPTY)  gen_push(moveList, square, square + NNE,                   0, 0, 0, moveCount);
            else if (board[square + NNE] & WHITE)   gen_push(moveList, square, square + NNE, board[square + NNE], 0, 0, moveCount);
            if      (board[square + NEE] == EMPTY)  gen_push(moveList, square, square + NEE,                   0, 0, 0, moveCount);
            else if (board[square + NEE] & WHITE)   gen_push(moveList, square, square + NEE, board[square + NEE], 0, 0, moveCount);
            if      (board[square + SEE] == EMPTY)  gen_push(moveList, square, square + SEE,                   0, 0, 0, moveCount);
            else if (board[square + SEE] & WHITE)   gen_push(moveList, square, square + SEE, board[square + SEE], 0, 0, moveCount);
            if      (board[square + SSE] == EMPTY)  gen_push(moveList, square, square + SSE,                   0, 0, 0, moveCount);
            else if (board[square + SSE] & WHITE)   gen_push(moveList, square, square + SSE, board[square + SSE], 0, 0, moveCount);
            if      (board[square + SSW] == EMPTY)  gen_push(moveList, square, square + SSW,                   0, 0, 0, moveCount);
            else if (board[square + SSW] & WHITE)   gen_push(moveList, square, square + SSW, board[square + SSW], 0, 0, moveCount);
            if      (board[square + SWW] == EMPTY)  gen_push(moveList, square, square + SWW,                   0, 0, 0, moveCount);
            else if (board[square + SWW] & WHITE)   gen_push(moveList, square, square + SWW, board[square + SWW], 0, 0, moveCount);
        }
        for(unsigned short i = bBS; i < bBE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 4; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & BLACK_OR_OUT); next += INCR[i])
                {
                    if (board[next] == EMPTY)   gen_push(moveList, square, next,           0, 0, 0, moveCount);
                    else                       {gen_push(moveList, square, next, board[next], 0, 0, moveCount); break;}
                }
            }
        }
        for(unsigned short i = bRS; i < bRE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 4; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & BLACK_OR_OUT); next += INCR[i])
                {
                    if (board[next] == EMPTY)   gen_push(moveList, square, next,           0, 0, 0, moveCount);
                    else                       {gen_push(moveList, square, next, board[next], 0, 0, moveCount); break;}
                }
            }
        }
        for(unsigned short i = bQS; i < bQE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & BLACK_OR_OUT); next += INCR[i])
                {
                    if (board[next] == EMPTY)   gen_push(moveList, square, next,           0, 0, 0, moveCount);
                    else                       {gen_push(moveList, square, next, board[next], 0, 0, moveCount); break;}
                }
            }
        }
        square = piece_list[bKING].square;
        for(uint8_t i = 0 ; i < 8; ++i)
        {
            next = square + INCR[i];
            if (board[next] == EMPTY)   {gen_push(moveList, square, next,           0, 0, 0, moveCount); continue;}
            if (board[next] & WHITE)     gen_push(moveList, square, next, board[next], 0, 0, moveCount);
        }
        if(currentPos.castle & BCS && board[F8] == EMPTY && board[G8] == EMPTY
          && !(is_attacked(E8, stm ^ SIDE_SWITCH)) && !(is_attacked(F8, stm ^ SIDE_SWITCH)) && !(is_attacked(G8, stm ^ SIDE_SWITCH)))
            gen_push(moveList, E8, G8, 0, 0, BCS, moveCount);
        if(currentPos.castle & BCL && board[B8] == EMPTY && board[C8] == EMPTY && board[D8] == EMPTY
          && !(is_attacked(E8, stm ^ SIDE_SWITCH)) && !(is_attacked(C8, stm ^ SIDE_SWITCH)) && !(is_attacked(D8, stm ^ SIDE_SWITCH)))
            gen_push(moveList, E8, C8, 0, 0, BCL, moveCount);
    }
    if(currentPos.ep)
    {
        if(stm == WHITE)
        {
            if(board[currentPos.ep + SE] & PAWN && board[currentPos.ep + SE] & WHITE)
                gen_push(moveList, currentPos.ep + SE, currentPos.ep, board[currentPos.ep + S], 0, 0, moveCount);
            if(board[currentPos.ep + SW] & PAWN && board[currentPos.ep + SW] & WHITE)
                gen_push(moveList, currentPos.ep + SW, currentPos.ep, board[currentPos.ep + S], 0, 0, moveCount);
        }
        else
        {
            if(board[currentPos.ep + NE] & PAWN && board[currentPos.ep + NE] & BLACK)
                gen_push(moveList, currentPos.ep + NE, currentPos.ep, board[currentPos.ep + N], 0, 0, moveCount);
            if(board[currentPos.ep + NW] & PAWN && board[currentPos.ep + NW] & BLACK)
                gen_push(moveList, currentPos.ep + NW, currentPos.ep, board[currentPos.ep + N], 0, 0, moveCount);
        }
    }
    return moveCount;
}

uint8_t generate_caps(Move *moveList, const Position &currentPos)
{
    uint8_t moveCount = 1;
    uint8_t square;
    uint8_t next;

    if(stm == WHITE)
    {
        for(unsigned short i = wPS; i < wPE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if(square + N < 76 && board[square + N] == EMPTY)     gen_promote(moveList, square, square + N, 0, 0, 0, moveCount);
            if(board[square + NE] & BLACK)
            {
                if(square + NE < 76)            gen_promote(moveList, square, square + NE, board[square + NE], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + NE, board[square + NE], 0, 0, moveCount);
            }
            if(board[square + NW] & BLACK)
            {
                if(square + NW < 76)            gen_promote(moveList, square, square + NW, board[square + NW], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + NW, board[square + NW], 0, 0, moveCount);
            }
        }
        for(unsigned short i = wKS; i < wKE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if (board[square + NWW] & BLACK)   gen_push(moveList, square, square + NWW, board[square + NWW], 0, 0, moveCount);
            if (board[square + NNW] & BLACK)   gen_push(moveList, square, square + NNW, board[square + NNW], 0, 0, moveCount);
            if (board[square + NNE] & BLACK)   gen_push(moveList, square, square + NNE, board[square + NNE], 0, 0, moveCount);
            if (board[square + NEE] & BLACK)   gen_push(moveList, square, square + NEE, board[square + NEE], 0, 0, moveCount);
            if (board[square + SEE] & BLACK)   gen_push(moveList, square, square + SEE, board[square + SEE], 0, 0, moveCount);
            if (board[square + SSE] & BLACK)   gen_push(moveList, square, square + SSE, board[square + SSE], 0, 0, moveCount);
            if (board[square + SSW] & BLACK)   gen_push(moveList, square, square + SSW, board[square + SSW], 0, 0, moveCount);
            if (board[square + SWW] & BLACK)   gen_push(moveList, square, square + SWW, board[square + SWW], 0, 0, moveCount);
        }
        for(unsigned short i = wBS; i < wBE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 4; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & WHITE_OR_OUT); next += INCR[i])
                {
                    if (board[next] != EMPTY)
                    {
                        gen_push(moveList, square, next, board[next], 0, 0, moveCount);
                        break;
                    }
                }
            }
        }
        for(unsigned short i = wRS; i < wRE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 4; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & WHITE_OR_OUT); next += INCR[i])
                {
                    if (board[next] != EMPTY)
                    {
                        gen_push(moveList, square, next, board[next], 0, 0, moveCount);
                        break;
                    }
                }
            }
        }
        for(unsigned short i = wQS; i < wQE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & WHITE_OR_OUT); next += INCR[i])
                {
                    if (board[next] != EMPTY)
                    {
                        gen_push(moveList, square, next, board[next], 0, 0, moveCount);
                        break;
                    }
                }
            }
        }
        square = piece_list[wKING].square;
        for(uint8_t i = 0 ; i < 8; ++i)
        {
            next = square + INCR[i];
            if (board[next] & BLACK)     gen_push(moveList, square, next, board[next], 0, 0, moveCount);
        }
    }
    else
    {
        for(unsigned short i = bPS; i < bPE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if(square + S > 179 && board[square + S] == EMPTY)    gen_promote(moveList, square, square + S, 0, 0, 0, moveCount);
            if(board[square + SE] & WHITE)
            {
                if(square + SE > 179)           gen_promote(moveList, square, square + SE, board[square + SE], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + SE, board[square + SE], 0, 0, moveCount);
            }
            if(board[square + SW] & WHITE)
            {
                if(square + SW > 179)           gen_promote(moveList, square, square + SW, board[square + SW], 0, 0, moveCount);
                else                            gen_push   (moveList, square, square + SW, board[square + SW], 0, 0, moveCount);
            }
        }
        for(unsigned short i = bKS; i < bKE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            if (board[square + NWW] & WHITE)   gen_push(moveList, square, square + NWW, board[square + NWW], 0, 0, moveCount);
            if (board[square + NNW] & WHITE)   gen_push(moveList, square, square + NNW, board[square + NNW], 0, 0, moveCount);
            if (board[square + NNE] & WHITE)   gen_push(moveList, square, square + NNE, board[square + NNE], 0, 0, moveCount);
            if (board[square + NEE] & WHITE)   gen_push(moveList, square, square + NEE, board[square + NEE], 0, 0, moveCount);
            if (board[square + SEE] & WHITE)   gen_push(moveList, square, square + SEE, board[square + SEE], 0, 0, moveCount);
            if (board[square + SSE] & WHITE)   gen_push(moveList, square, square + SSE, board[square + SSE], 0, 0, moveCount);
            if (board[square + SSW] & WHITE)   gen_push(moveList, square, square + SSW, board[square + SSW], 0, 0, moveCount);
            if (board[square + SWW] & WHITE)   gen_push(moveList, square, square + SWW, board[square + SWW], 0, 0, moveCount);
        }
        for(unsigned short i = bBS; i < bBE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 4; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & BLACK_OR_OUT); next += INCR[i])
                {
                    if (board[next] != EMPTY)
                    {
                        gen_push(moveList, square, next, board[next], 0, 0, moveCount);
                        break;
                    }
                }
            }
        }
        for(unsigned short i = bRS; i < bRE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 4; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & BLACK_OR_OUT); next += INCR[i])
                {
                    if (board[next] != EMPTY)
                    {
                        gen_push(moveList, square, next, board[next], 0, 0, moveCount);
                        break;
                    }
                }
            }
        }
        for(unsigned short i = bQS; i < bQE; ++i)
        {
            if(piece_list[i].captured) continue;
            square = piece_list[i].square;
            for(uint8_t i = 0; i < 8; ++i)
            {
                for(next = square + INCR[i]; !(board[next] & BLACK_OR_OUT); next += INCR[i])
                {
                    if (board[next] != EMPTY)
                    {
                        gen_push(moveList, square, next, board[next], 0, 0, moveCount);
                        break;
                    }
                }
            }
        }
        square = piece_list[bKING].square;
        for(uint8_t i = 0 ; i < 8; ++i)
        {
            next = square + INCR[i];
            if (board[next] & WHITE)     gen_push(moveList, square, next, board[next], 0, 0, moveCount);
        }
    }
    if(currentPos.ep)
    {
        if(stm == WHITE)
        {
            if(board[currentPos.ep + SE] & PAWN && board[currentPos.ep + SE] & WHITE)
                gen_push(moveList, currentPos.ep + SE, currentPos.ep, board[currentPos.ep + S], 0, 0, moveCount);
            if(board[currentPos.ep + SW] & PAWN && board[currentPos.ep + SW] & WHITE)
                gen_push(moveList, currentPos.ep + SW, currentPos.ep, board[currentPos.ep + S], 0, 0, moveCount);
        }
        else
        {
            if(board[currentPos.ep + NE] & PAWN && board[currentPos.ep + NE] & BLACK)
                gen_push(moveList, currentPos.ep + NE, currentPos.ep, board[currentPos.ep + N], 0, 0, moveCount);
            if(board[currentPos.ep + NW] & PAWN && board[currentPos.ep + NW] & BLACK)
                gen_push(moveList, currentPos.ep + NW, currentPos.ep, board[currentPos.ep + N], 0, 0, moveCount);
        }
    }
    return moveCount;
}
