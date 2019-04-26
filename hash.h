#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "data.h"


constexpr short SQUARE_TO_INDEX[188] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   2,   3,   4,   5,   6,   7,   0,   0,   0,   0,
    0,   0,   0,   0,   8,   9,  10,  11,  12,  13,  14,  15,   0,   0,   0,   0,
    0,   0,   0,   0,   16, 17,  18,  19,  20,  21,  22,  23,   0,   0,   0,   0,
    0,   0,   0,   0,   24, 25,  26,  27,  28,  29,  30,  31,   0,   0,   0,   0,
    0,   0,   0,   0,   32, 33,  34,  35,  36,  37,  38,  39,   0,   0,   0,   0,
    0,   0,   0,   0,   40, 41,  42,  43,  44,  45,  46,  47,   0,   0,   0,   0,
    0,   0,   0,   0,   48, 49,  50,  51,  52,  53,  54,  55,   0,   0,   0,   0,
    0,   0,   0,   0,   56, 57,  58,  59,  60,  61,  62,  63
};

constexpr short PIECE_TO_INDEX[84] =
{
  768,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  64, 128, 128, 192, 192, 192, 192, 256, 256,
  256, 256,   0,   0,   0,   0, 320, 320, 320, 320,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0, 384, 448, 512, 512, 576, 576, 576, 576, 640, 640, 640, 640,   0,   0,   0,   0, 704, 704, 704, 704
};

constexpr uint8_t EP_TO_INDEX[156] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    1,   2,   3,   4,   5,   6,   7,   8,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   1,   2,   3,   4,   5,   6,   7,   8
};

constexpr uint8_t ALPHA{1}, BETA{2}, EXACT{3}, NO_SCORE{0};

extern uint64_t z_piece[769];
extern uint64_t z_castle[16];
extern uint64_t z_ep[9];
extern uint64_t z_stm;

extern uint64_t hashkey[200];
extern uint8_t  hk_root;
extern uint8_t  hk_current;

struct Hash_entry
{
    uint64_t key{0};
    uint8_t depth{0};
    short score{0};
    uint8_t flag{0};
    uint8_t hash_move_id{0};
};
extern Hash_entry * tt;
extern unsigned tt_size;


void init_zobrist();

bool repetition(uint8_t fifty);

void tt_resize(uint64_t MB);

void tt_save(uint8_t depth, short score, uint8_t flag, uint8_t move_ID);

short tt_probe(uint8_t depth, short alpha, short beta, uint8_t &hash_move_id);

uint8_t tt_pv();


#endif // HASH_H_INCLUDED
