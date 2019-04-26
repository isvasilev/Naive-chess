#include <chrono>
#include <iostream>

#include "attacks.h"
#include "evaluation.h"
#include "data.h"
#include "movegen.h"
#include "moves.h"
#include "search.h"
#include "hash.h"


Move UCI_move;
short UCI_score;
uint64_t nodes;

std::string    move_to_string(Move m);

void search_iterate(uint8_t depth, const Position &current_position)
{
    nodes = 0;                                                 /// reset node counter for this search
    auto start = std::chrono::high_resolution_clock::now();    /// store starting time for this search

    /// iterative deepening - start search repeatedly with increased depth
    for(uint8_t i = 1; i <= depth; ++i)
    {
        search_root(i, -32000, 32000, current_position);

        /// if time is over info wont be printed
        if(stop_search)    break;

        /// prepare the string with info for completed depth
        auto current = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_elapsed = current - start;
        unsigned int NPS = nodes / time_elapsed.count();
        std::string pv = get_pv(i, position);
        std::string info =
        "info depth " + std::to_string(i) + " score cp " + std::to_string(UCI_score) + " time " + std::to_string(time_elapsed.count())
                      + " nodes " + std::to_string(nodes) + " nps " + std::to_string(NPS)
                      + " pv " + pv;
        /// and print
        std::cout << info  << std::endl;
    }
}

void search_root(uint8_t depth, short alpha, short beta, const Position &current_position)
{
    ++nodes;
    uint8_t bestmove_id = 0;    /// store best move from current node to be saved in the hash table

    Move move_list[150];
    uint8_t move_count = generate_all(move_list, current_position);

    ///check hash table for move
    uint8_t tt_move_id = tt_pv();
    move_list[tt_move_id].order_score += 100;

    for(uint8_t i = 1; i < move_count; ++i)
    {
        ///find the move with the highest order score
        uint8_t move_to_check = i;
        for(uint8_t j = i + 1; j < move_count; ++j)
        {
            if(move_list[j].order_score > move_list[move_to_check].order_score) move_to_check = j;
        }
        Move temp = move_list[i];
        move_list[i] = move_list[move_to_check];
        move_list[move_to_check] = temp;

        Position next_position = current_position;
        make_move(move_list[i], next_position);

        if(is_attacked(piece_list[(stm ^ SIDE_SWITCH) + KING].square, stm))
        {
            unmake_move(move_list[i]);
            continue;
        }

        ++ply;
        ++hk_current;
        update_hashkey(move_list[i], current_position, next_position);

        short score = -alpha_beta(depth - 1, -beta, -alpha, next_position);

        --ply;
        --hk_current;
        unmake_move(move_list[i]);

        if(stop_search) return;

        if(score > alpha)
        {
            alpha = score;
            bestmove_id = move_list[i].id;
            UCI_move = move_list[i];
            UCI_score = alpha;
        }
    }
    tt_save(depth, alpha, EXACT, bestmove_id);
}

short alpha_beta(uint8_t depth, short alpha, short beta, const Position &current_position)
{
    ++nodes;
    short tt_score = 0;        /// store score from hash table to return if its usable
    uint8_t tt_flag = ALPHA;   /// to know what kind of score will be stored in hash table
    uint8_t tt_move_id = 0;    /// store move from the hash table
    uint8_t bestmove_id = 0;   /// store best move from current node to be saved in hash table
    bool in_check = false;
    uint8_t legal = 0;

    /// if time is over stop searching
    if(stop_search)    return 0;

    /// check for repetition and fifty move rule
    if(repetition(current_position.fifty) || current_position.fifty >= 100) return 0;

    /// if in check increase search depth, also wont enter quiescence search while in check
    in_check = is_attacked(piece_list[stm + KING].square, stm ^ SIDE_SWITCH);
    if(in_check) ++ depth;

    /// max depth is reached - call quiescence search
    if (depth == 0 || ply == MAX_PLY)    return quiescence_search(alpha, beta, current_position);

    ///check hash table for current position, will also update hash move if position is found
    if ((tt_score = tt_probe(depth, alpha, beta, tt_move_id)) != NO_SCORE)
    {
        /// if score is mate adjust distance from this position to distance from root
        if (abs(tt_score) > TT_MATE)
        {
            if (tt_score > 0)    tt_score -= ply;
            else                 tt_score += ply;
        }
        return tt_score;
    }

    /// generate moves from this position
    Move move_list[150];
    uint8_t move_count = generate_all(move_list, current_position);

    /// increase order score for hash move so it is searched first
    move_list[tt_move_id].order_score += 100;

    /// loop start from 1 to avoid using hash move from fail low node (which has big score but is on the dummy index 0)
    for(uint8_t i = 1; i < move_count; ++i)
    {
        ///find the move with the highest order score
        uint8_t move_to_check = i;
        for(uint8_t j = i + 1; j < move_count; ++j)
        {
            if(move_list[j].order_score > move_list[move_to_check].order_score) move_to_check = j;
        }
        Move temp = move_list[i];
        move_list[i] = move_list[move_to_check];
        move_list[move_to_check] = temp;

        /// position is copy/make
        Position next_position = current_position;
        make_move(move_list[i], next_position);
        if(is_attacked(piece_list[(stm ^ SIDE_SWITCH) + KING].square, stm))
        {
            unmake_move(move_list[i]);   /// if in check move is illegal
            continue;
        }

        ++ply;
        ++hk_current;
        ++legal;
        update_hashkey(move_list[i], current_position, next_position);

        short score = -alpha_beta(depth - 1, -beta, -alpha, next_position);

        --ply;
        --hk_current;
        unmake_move(move_list[i]);

        if(score > alpha)
        {
            alpha = score;
            bestmove_id = move_list[i].id;
            tt_flag = EXACT;
            if(score >= beta)
            {
                tt_save(depth, beta, BETA, bestmove_id);
                return beta;
            }
        }
    }

    if(legal == 0)
    {
        if(in_check)    return MATE + ply;
        else            return STALEMATE;
    }

    tt_save(depth, alpha, tt_flag, bestmove_id);
    return alpha;
}

short quiescence_search(short alpha, short beta, const Position &current_position)
{
    if(stop_search) return 0;
    short stand_pat = evaluate();
    if(stand_pat >= beta) return beta;
    if(stand_pat > alpha) alpha = stand_pat;

    Move move_list[100];
    uint8_t move_count = generate_caps(move_list, current_position);
    if(move_count == 1) return alpha;   /// no captures or promotions found

    for(uint8_t i = 1; i < move_count; ++i)
    {
        ///find the move with the highest order score
        uint8_t move_to_check = i;
        for(uint8_t j = i + 1; j < move_count; ++j)
        {
            if(move_list[j].order_score > move_list[move_to_check].order_score) move_to_check = j;
        }
        Move temp = move_list[i];
        move_list[i] = move_list[move_to_check];
        move_list[move_to_check] = temp;

        /// delta pruning
        short cap_value = piece_list[move_list[i].capture].value;   /// value of captured piece
        if(move_list[i].capture & PAWN) cap_value = 100;            /// pawns are 0 for faster make move so adjust here the value
        if(
           stand_pat + cap_value + 200 < alpha                                               /// not enough to exceed alpha with 200 bonus
           && piece_material[(stm ^ SIDE_SWITCH) >> 9] - cap_value > ENDGAME_PIECE_MATERIAL  /// not endgame
           && move_list[i].pawn == 0                                                         /// not promotion
          )
        continue;

        Position next_position = current_position;
        make_move(move_list[i], next_position);

        if(is_attacked(piece_list[(stm ^ SIDE_SWITCH) + KING].square, stm))
        {
            unmake_move(move_list[i]);
            continue;
        }

        short score = -quiescence_search(-beta, -alpha, next_position);

        unmake_move(move_list[i]);

        if(score > alpha)
        {
            alpha = score;
            if(score >= beta) return beta;
        }
    }
    return alpha;
}

void update_hashkey(Move &move, Position prev_position, Position &new_position)
{
    hashkey[hk_current]  = hashkey[hk_current - 1];
    hashkey[hk_current] ^= z_castle[prev_position.castle];
    hashkey[hk_current] ^= z_ep[EP_TO_INDEX[prev_position.ep]];
    hashkey[hk_current] ^= z_stm;
    hashkey[hk_current] ^= z_castle[new_position.castle];
    hashkey[hk_current] ^= z_ep[EP_TO_INDEX[new_position.ep]];
    hashkey[hk_current] ^= z_piece[PIECE_TO_INDEX[move.capture >> 4] + SQUARE_TO_INDEX[piece_list[move.capture].square]];
    if(move.pawn)  hashkey[hk_current] ^= z_piece[PIECE_TO_INDEX[move.pawn >> 4] + SQUARE_TO_INDEX[move.from]];
    else           hashkey[hk_current] ^= z_piece[PIECE_TO_INDEX[board[move.to] >> 4] + SQUARE_TO_INDEX[move.from]];
    hashkey[hk_current] ^= z_piece[PIECE_TO_INDEX[board[move.to] >> 4] + SQUARE_TO_INDEX[move.to]];
    if(move.flags & CASTLE)                               /// update the rook keys if the move is castle
    {
        if(move.flags & WCS)         {hashkey[hk_current] ^= z_piece[319]; hashkey[hk_current] ^= z_piece[317];}
        else if(move.flags & WCL)    {hashkey[hk_current] ^= z_piece[312]; hashkey[hk_current] ^= z_piece[315];}
        else if(move.flags & BCS)    {hashkey[hk_current] ^= z_piece[647]; hashkey[hk_current] ^= z_piece[645];}
        else if(move.flags & BCL)    {hashkey[hk_current] ^= z_piece[640]; hashkey[hk_current] ^= z_piece[643];}
    }
    /// update fifty rule
    if(move.capture || (board[move.to] & PAWN) || move.pawn)    new_position.fifty = 0;
    else                                                      ++new_position.fifty;
}

std::string get_pv(uint8_t depth, Position current_position)
{
    std::string pv;
    if(depth > 0)
    {
        uint8_t pv_id = tt_pv();
        if(pv_id == 0) return pv;
        Move move_list[150];
        uint8_t move_count = generate_all(move_list, current_position);
        pv = move_to_string(move_list[pv_id]);
        Position next_position = current_position;
        make_move(move_list[pv_id], next_position);
        ++hk_current;
        update_hashkey(move_list[pv_id], current_position, next_position);
        pv += " " + get_pv(depth - 1, next_position);
        --hk_current;
        unmake_move(move_list[pv_id]);
    }
    return pv;
}
