#include "data.h"


constexpr uint8_t CASTLE_MASK[256] =
{
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15,  7, 15, 15, 15,  3, 15, 15, 11, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 13, 15, 15, 15, 12, 15, 15, 14, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

void put_piece(uint8_t square, unsigned short index)
{
    piece_list[index].captured = false;
    piece_list[index].square = square;
    board[square] = index;
    piece_material[stm >> 9] += piece_list[index].value;
}

void make_move(Move move, Position &next_position)
{
    piece_list[move.capture].captured = true;              /// remove captured piece
    board[piece_list[move.capture].square] = EMPTY;

    if(move.flags & PROMOTE)                               /// promotion - replace pawn with piece
    {
        piece_list[board[move.from]].captured = true;
        if(stm == WHITE)
        {
            if     (move.flags & PROM_QUEEN)   {put_piece(move.from, wQE);  ++wQE;}
            else if(move.flags & PROM_ROOK)    {put_piece(move.from, wRE);  ++wRE;}
            else if(move.flags & PROM_BISHOP)  {put_piece(move.from, wBE);  ++wBE;}
            else                               {put_piece(move.from, wKE);  ++wKE;}
        }
        else
        {
            if     (move.flags & PROM_QUEEN)   {put_piece(move.from, bQE);  ++bQE;}
            else if(move.flags & PROM_ROOK)    {put_piece(move.from, bRE);  ++bRE;}
            else if(move.flags & PROM_BISHOP)  {put_piece(move.from, bBE);  ++bBE;}
            else                               {put_piece(move.from, bKE);  ++bKE;}
        }
    }

    piece_list[board[move.from]].square = move.to;         /// move piece
    board[move.to] = board[move.from];
    board[move.from] = EMPTY;

    next_position.ep = move.ep;                            /// prepare the new position
    next_position.castle &= CASTLE_MASK[move.from] & CASTLE_MASK[move.to];

    stm ^= SIDE_SWITCH;
    piece_material[stm >> 9] -= piece_list[move.capture].value;

    if(move.flags & CASTLE)                                /// move the rook if the move is castle
    {
        if(move.flags & WCS)
        {
            piece_list[board[H1]].square = F1;
            board[F1] = board[H1];
            board[H1] = EMPTY;
        }
        else if(move.flags & WCL)
        {
            piece_list[board[A1]].square = D1;
            board[D1] = board[A1];
            board[A1] = EMPTY;
        }
        else if(move.flags & BCS)
        {
            piece_list[board[H8]].square = F8;
            board[F8] = board[H8];
            board[H8] = EMPTY;
        }
        else if(move.flags & BCL)
        {
            piece_list[board[A8]].square = D8;
            board[D8] = board[A8];
            board[A8] = EMPTY;
        }
    }
}

void unmake_move(Move move)
{
    piece_material[stm >> 9] += piece_list[move.capture].value;
    stm ^= SIDE_SWITCH;

    piece_list[board[move.to]].square = move.from;           /// move piece back
    board[move.from] = board[move.to];
    board[move.to] = EMPTY;

    if(move.flags & PROMOTE)                                 /// promotion - restore pawn
    {
        piece_material[stm >> 9] -= piece_list[board[move.from]].value;
        piece_list[move.pawn].captured = false;
        board[move.from] = move.pawn;
        if(stm == WHITE)
        {
            if     (move.flags & PROM_QUEEN)   --wQE;
            else if(move.flags & PROM_ROOK)    --wRE;
            else if(move.flags & PROM_BISHOP)  --wBE;
            else                               --wKE;
        }
        else
        {
            if     (move.flags & PROM_QUEEN)   --bQE;
            else if(move.flags & PROM_ROOK)    --bRE;
            else if(move.flags & PROM_BISHOP)  --bBE;
            else                               --bKE;
        }
    }

    piece_list[move.capture].captured = false;                /// restore captured piece
    board[piece_list[move.capture].square] = move.capture;

    if(move.flags & CASTLE)                                   /// move the rook back if the move is castle
    {
        if(move.flags & WCS)
        {
            piece_list[board[F1]].square = H1;
            board[H1] = board[F1];
            board[F1] = EMPTY;
        }
        else if(move.flags & WCL)
        {
            piece_list[board[D1]].square = A1;
            board[A1] = board[D1];
            board[D1] = EMPTY;
        }
        else if(move.flags & BCS)
        {
            piece_list[board[F8]].square = H8;
            board[H8] = board[F8];
            board[F8] = EMPTY;
        }
        else if(move.flags & BCL)
        {
            piece_list[board[D8]].square = A8;
            board[A8] = board[D8];
            board[D8] = EMPTY;
        }
    }
}
