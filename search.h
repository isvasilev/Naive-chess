#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED


extern Move UCI_move;


std::string get_pv(uint8_t depth, Position current_position);

void update_hashkey(Move &move, Position prev_position, Position &new_position);

short quiescence_search(short alpha, short beta, const Position &current_position);

short alpha_beta(uint8_t depth, short alpha, short beta, const Position &current_position);

void search_root(uint8_t depth, short alpha, short beta, const Position &current_position);

void search_iterate(uint8_t depth, const Position &current_position);


#endif // SEARCH_H_INCLUDED
