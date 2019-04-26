#include <random>

#include "hash.h"


/// will store zobrist keys(large random numbers)
uint64_t z_piece[769] = {};
uint64_t z_castle[16] = {};
uint64_t z_ep[9] = {};
uint64_t z_stm{0};

/// store hash keys
uint64_t hashkey[200] = {};
uint8_t hk_root{0};
uint8_t hk_current{0};

/// hash table
Hash_entry *tt;
unsigned tt_size;

/// initialize zobrist keys with random numbers
void init_zobrist()
{
    std::mt19937_64 rng(7235673537);
    for(int i = 0; i < 768; ++i)    z_piece[i] = rng();
    for(int i = 0; i < 16; ++i)     z_castle[i] = rng();
    for(int i = 0; i < 9; ++i)      z_ep[i] = rng();
    z_stm = rng();
}

/// check for repetition of the current search position
bool repetition(uint8_t fifty)
{
    /// check for repetition in previous positions
    /// to distance according to fifty move rule (no captures or pawn moves)
    for(int i = hk_current - 1; i >= hk_current - fifty; --i)
    {
        if(hashkey[i] == hashkey[hk_current]) /// repetition is found
        {
            if(i <= hk_root) /// if the repetition is in the game check if one more repetition exist
            {
                for(int j = i - 1; j >= hk_current - fifty; --j)
                {
                    if(hashkey[j] == hashkey[hk_current])    return true; /// found second repetition
                }
                return false;     /// no second repetition
            }
            else    return true;  /// one repetition is enough in search positions
        }
    }
    return false;
}

void tt_resize(uint64_t MB)
{
    uint64_t tt_bytes = MB << 20;
    tt_size = tt_bytes / sizeof(Hash_entry) - 1;
    tt = new Hash_entry[tt_size];
}

void tt_save(uint8_t depth, short score, uint8_t flag, uint8_t bestmove_id)
{
    if(stop_search)    return;   /// no save if search is stopped

    Hash_entry *save = &tt[hashkey[hk_current] & tt_size];

    save -> key = hashkey[hk_current];
    save -> depth = depth;
    save -> score = score;
    save -> flag = flag;
    save -> hash_move_id = bestmove_id;
}

short tt_probe(uint8_t depth, short alpha, short beta, uint8_t &move_id)
{
    Hash_entry *probe = &tt[hashkey[hk_current] & tt_size];

    /// if position is the same
    if(probe -> key == hashkey[hk_current])
    {
        /// copy best move found
        move_id = probe -> hash_move_id;

        /// if depth is enough try to return score
        if(probe -> depth >= depth)
        {
            if(probe -> flag == ALPHA && probe -> score <= alpha)    return alpha;
            if(probe -> flag == BETA  && probe -> score >= beta)     return beta;
            if(probe -> flag == EXACT)    return probe -> score;
        }
    }

    return NO_SCORE;
}

uint8_t tt_pv()
{
    Hash_entry *pv = &tt[hashkey[hk_current] & tt_size];
    if(pv -> key == hashkey[hk_current] && pv -> flag == EXACT)    return pv -> hash_move_id;
    return 0;
}
