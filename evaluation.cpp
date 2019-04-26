#include "data.h"


constexpr short WPAWN_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,  15,  15,  15,  25,  25,  15,  15,  15,   0,   0,   0,   0,
    0,   0,   0,   0,  10,  10,  10,  20,  20,  10,  10,  10,   0,   0,   0,   0,
    0,   0,   0,   0,   5,   5,   5,  15,  15,   5,   5,   5,   0,   0,   0,   0,
    0,   0,   0,   0,   3,   3,   3,  10,  10,   3,   3,   3,   0,   0,   0,   0,
    0,   0,   0,   0,   1,   1,   1,   0,   0,   1,   1,   1,   0,   0,   0,   0,
    0,   0,   0,   0,   5,   5,   5, -15, -15,   5,   5,   5,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

constexpr short BPAWN_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   5,   5,   5, -15, -15,   5,   5,   5,   0,   0,   0,   0,
    0,   0,   0,   0,   1,   1,   1,   0,   0,   1,   1,   1,   0,   0,   0,   0,
    0,   0,   0,   0,   3,   3,   3,  10,  10,   3,   3,   3,   0,   0,   0,   0,
    0,   0,   0,   0,   5,   5,   5,  15,  15,   5,   5,   5,   0,   0,   0,   0,
    0,   0,   0,   0,  10,  10,  10,  20,  20,  10,  10,  10,   0,   0,   0,   0,
    0,   0,   0,   0,  15,  15,  15,  25,  25,  15,  15,  15,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

constexpr short KNIGHT_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0, -10,  -8,  -4,  -4,  -4,  -4,  -4, -10,   0,   0,   0,   0,
    0,   0,   0,   0,  -8,   0,   0,   0,   0,   0,   0,  -8,   0,   0,   0,   0,
    0,   0,   0,   0,  -4,   0,   5,   5,   5,   5,   0,  -4,   0,   0,   0,   0,
    0,   0,   0,   0,  -4,   0,   5,   8,   8,   5,   0,  -4,   0,   0,   0,   0,
    0,   0,   0,   0,  -4,   0,   5,   8,   8,   5,   0,  -4,   0,   0,   0,   0,
    0,   0,   0,   0,  -4,   0,   5,   5,   5,   5,   0,  -4,   0,   0,   0,   0,
    0,   0,   0,   0,  -8,   0,   0,   0,   0,   0,   0,  -8,   0,   0,   0,   0,
    0,   0,   0,   0, -10,  -8,  -4,  -4,  -4,  -4,  -8, -10
};

constexpr short BISHOP_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   3,   3,   3,   3,   3,   3,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   3,   5,   5,   5,   5,   3,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   3,   5,   5,   5,   5,   3,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   3,   5,   5,   5,   5,   3,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   3,   5,   5,   5,   5,   3,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   3,   3,   3,   3,   3,   3,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

constexpr short WROOK_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   3,   3,   3,   3,   3,   3,   3,   3,   0,   0,   0,   0,
    0,   0,   0,   0,   4,   4,   4,   4,   4,   4,   4,   4,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   2,   2,   2,   0,   0
};

constexpr short BROOK_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   2,   2,   2,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   4,   4,   4,   4,   4,   4,   4,   4,   0,   0,   0,   0,
    0,   0,   0,   0,   3,   3,   3,   3,   3,   3,   3,   3
};


constexpr short QUEEN_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   2,   2,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   2,   2,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   2,   2,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   2,   2,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};


constexpr short KING_MIDGAME_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   8,   8,   5,   0,   0,   0,   8,   8,   0,   0,   0,   0,
    0,   0,   0,   0,   4,   4,   0,   0,   0,   0,   4,   4,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   4,   4,   0,   0,   0,   0,   4,   4,   0,   0,   0,   0,
    0,   0,   0,   0,   8,   8,   5,   0,   0,   0,   8,   8
};

constexpr short KING_ENDGAME_PSQT[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   2,   2,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   3,   3,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   3,   3,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   2,   2,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

constexpr short SHIELD_1{10}, SHIELD_2{7}, TEMPO_BONUS{20};

short evaluate()
{
    uint8_t square = 0;
    uint8_t next = 0;

    short score = 0;
    short wpiece = 0;
    short bpiece = 0;

    /// WHITE
    for(unsigned short i = wPS; i < wPE; ++i)
    {
        if(piece_list[i].captured) continue;
        score += VALUE_P + WPAWN_PSQT[piece_list[i].square];
    }
    for(unsigned short i = wKS; i < wKE; ++i)
    {
        if(piece_list[i].captured) continue;
        score += VALUE_N + KNIGHT_PSQT[piece_list[i].square];
        wpiece += VALUE_N;
    }
    for(unsigned short i = wBS; i < wBE; ++i)
    {
        if(piece_list[i].captured) continue;
        square = piece_list[i].square;
        for(uint8_t i = 0; i < 4; ++i)
        {
            for(next = square + INCR[i]; !(board[next] & WHITE_OR_OUT); next += INCR[i])
            {
                ++score;
            }
        }
        score += VALUE_B + BISHOP_PSQT[square];
        wpiece += VALUE_B;
    }
    for(unsigned short i = wRS; i < wRE; ++i)
    {
        if(piece_list[i].captured) continue;
        score += VALUE_R + WROOK_PSQT[piece_list[i].square];
        wpiece += VALUE_R;
    }
    for(unsigned short i = wQS; i < wQE; ++i)
    {
        if(piece_list[i].captured) continue;
        score += VALUE_Q + QUEEN_PSQT[piece_list[i].square];
        wpiece += VALUE_Q;
    }

    /// BLACK
    for(unsigned short i = bPS; i < bPE; ++i)
    {
        if(piece_list[i].captured) continue;
        score -= VALUE_P + BPAWN_PSQT[piece_list[i].square];
    }
    for(unsigned short i = bKS; i < bKE; ++i)
    {
        if(piece_list[i].captured) continue;
        score -= VALUE_N + KNIGHT_PSQT[piece_list[i].square];
        bpiece += VALUE_N;
    }
    for(unsigned short i = bBS; i < bBE; ++i)
    {
        if(piece_list[i].captured) continue;
        square = piece_list[i].square;
        for(uint8_t i = 0; i < 4; ++i)
        {
            for(next = square + INCR[i]; !(board[next] & BLACK_OR_OUT); next += INCR[i])
            {
                --score;
            }
        }
        score -= VALUE_B + BISHOP_PSQT[square];
        bpiece += VALUE_B;
    }
    for(unsigned short i = bRS; i < bRE; ++i)
    {
        if(piece_list[i].captured) continue;
        score -= VALUE_R + BROOK_PSQT[piece_list[i].square];
        bpiece += VALUE_R;
    }
    for(unsigned short i = bQS; i < bQE; ++i)
    {
        if(piece_list[i].captured) continue;
        score -= VALUE_Q + QUEEN_PSQT[piece_list[i].square];
        bpiece += VALUE_Q;
    }

    /// WHITE KING
    square = piece_list[wKING].square;
    if(bpiece > ENDGAME_PIECE_MATERIAL)
    {
        score += KING_MIDGAME_PSQT[square];
        if(!(board[square + N] & NOT_WP))   score += SHIELD_1;
        if(!(board[square + NE] & NOT_WP))  score += SHIELD_1;
        if(!(board[square + NW] & NOT_WP))  score += SHIELD_1;
        if(!(board[square + NN] & NOT_WP))  score += SHIELD_2;
        if(!(board[square + NNE] & NOT_WP)) score += SHIELD_2;
        if(!(board[square + NNW] & NOT_WP)) score += SHIELD_2;
    }
    else   score += KING_ENDGAME_PSQT[square];

    /// BLACK KING
    square = piece_list[bKING].square;
    if(wpiece > ENDGAME_PIECE_MATERIAL)
    {
        score -= KING_MIDGAME_PSQT[square];
        if(!(board[square + S] & NOT_BP))   score -= SHIELD_1;
        if(!(board[square + SE] & NOT_BP))  score -= SHIELD_1;
        if(!(board[square + SW] & NOT_BP))  score -= SHIELD_1;
        if(!(board[square + SS] & NOT_BP))  score -= SHIELD_2;
        if(!(board[square + SSE] & NOT_BP)) score -= SHIELD_2;
        if(!(board[square + SSW] & NOT_BP)) score -= SHIELD_2;
    }
    else    score -= KING_ENDGAME_PSQT[square];


    if (stm == WHITE) return  score + TEMPO_BONUS;
    else              return -score - TEMPO_BONUS;
}
