#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "attacks.h"
#include "data.h"
#include "movegen.h"
#include "moves.h"
#include "search.h"
#include "hash.h"

/// for time management
std::thread search_thread;
std::thread timer_thread;
std::mutex mutex;
std::condition_variable stop_timer;
bool uci_stop;

const std::string STARTPOS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const std::string SQUARE_STR[188] =
{
    "", "", "", "",   "",   "",   "",   "",   "",   "",   "",   "", "", "", "", "",
    "", "", "", "",   "",   "",   "",   "",   "",   "",   "",   "", "", "", "", "",
    "", "", "", "",   "",   "",   "",   "",   "",   "",   "",   "", "", "", "", "",
    "", "", "", "",   "",   "",   "",   "",   "",   "",   "",   "", "", "", "", "",
    "", "", "", "", "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "", "", "", "",
    "", "", "", "", "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "", "", "", "",
    "", "", "", "", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "", "", "", "",
    "", "", "", "", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "", "", "", "",
    "", "", "", "", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "", "", "", "",
    "", "", "", "", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "", "", "", "",
    "", "", "", "", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "", "", "", "",
    "", "", "", "", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};


void set_position(std::istringstream &ss);
void go(std::istringstream &ss);
void timer(unsigned int search_time);

/// convert input / output
void init_piece(uint8_t square, unsigned short piece);
void init_from_fen(std::string fen);
Move string_to_move(std::string str);
std::string move_to_string(Move m);

/// this functions were used when program was console move generator for debug
void print_square(unsigned short s);
void print_board();

/// functions for testing
void test();
uint64_t perft(uint8_t depth, const Position &currentPosition);
void perft_start(uint8_t depth);


int main()
{
    std::cout << "Naive Chess by Ivaylo Vasilev \n\n";
    std::cout << "This program is designed to run with GUY - tested with Arena\n";
    std::cout << "Console mode commands: \n";
    std::cout << "perft x - x is perft depth, all moves are made and then unmade \n";
    std::cout << "test - this runs 10 sec search in position fine70 \n";
    init_zobrist();
    tt_resize(1024);
    std::string input;
    std::string token;
    while(true)
    {
        getline(std::cin, input);
        std::istringstream ss(input);
        ss >> token;

        if(token == "uci")              std::cout << "id name Naive chess 0.81 \n" << "id author Ivaylo Vasilev \n" << "uciok " << std::endl;
        else if(token == "isready")     std::cout << "readyok " << std::endl;
        else if(token == "newgame")     ;
        else if(token == "position")    set_position(ss);
        else if(token == "go")          go(ss);
        else if(token == "stop")
        {
            std::unique_lock<std::mutex> lock(mutex);
            uci_stop = true;
            lock.unlock();
            stop_timer.notify_one();
            if(timer_thread.joinable()) timer_thread.join();
        }
        else if(token == "quit")
        {
            std::unique_lock<std::mutex> lock(mutex);
            uci_stop = true;
            lock.unlock();
            stop_timer.notify_one();
            if(timer_thread.joinable()) timer_thread.join();
            delete [] tt;
            break;
        }
        else if(token == "perft")
        {
            ss >> token;
            uint8_t depth = stoi(token);
            perft_start(depth);
        }
        else if(token == "test") test();
        else std::cout << "unknown command" << std::endl;
    }
}

/// send stop to search thread when signaled from main thread or when time is over
void timer(unsigned int search_time)
{
    std::unique_lock<std::mutex> lock(mutex);
    stop_timer.wait_for(lock, std::chrono::milliseconds(search_time), [] {return uci_stop;});  /// waiting
    stop_search = true;                 /// signal search to stop
    search_thread.join();               /// wait search thread to finish
    std::string to_UCI = "bestmove " + move_to_string(UCI_move);
    std::cout << to_UCI << std::endl;   /// send move to UCI GUI
}

void go(std::istringstream &ss)
{
    stop_search = false;
    search_thread = std::thread(search_iterate, MAX_DEPTH, position);   /// launch the search thread

    unsigned int search_time = 0;
    unsigned int time = 0;
    unsigned int incr = 0;
    unsigned int movestogo = 0;

    std::string token;
    while(true)
    {
        ss >> token;
        if(token.empty())    break;

        if     (token == "wtime" && stm == WHITE) {ss >> token; time = stoi(token);}
        else if(token == "wtime" && stm == BLACK) {ss >> token;}
        else if(token == "btime" && stm == BLACK) {ss >> token; time = stoi(token);}
        else if(token == "btime" && stm == WHITE) {ss >> token;}
        else if(token == "winc" && stm == WHITE)  {ss >> token; incr = stoi(token);}
        else if(token == "winc" && stm == BLACK)  {ss >> token;}
        else if(token == "binc" && stm == BLACK)  {ss >> token; incr = stoi(token);}
        else if(token == "binc" && stm == WHITE)  {ss >> token;}
        else if(token == "movestogo")             {ss >> token; movestogo = stoi(token);}
        else if(token == "movetime")
        {
            ss >> token;
            incr = stoi(token);
            break;
        }
        else if(token == "infinite")
        {
            incr = 1000000000;
            break;
        }
        token.clear();
    }

    if(movestogo > 0)  search_time = time / movestogo + incr;
    else if(time > 0)  search_time = time / 40 + incr;
    else               search_time = incr;

    search_time -= 50;
    uci_stop = false;

    if(timer_thread.joinable()) timer_thread.join();
    timer_thread = std::thread(timer, search_time);   /// launch the timer thread
}

void set_position(std::istringstream &ss)
{
    std::string token;
    std::string FEN;
    ss >> token;
    if(token == "startpos")
    {
        FEN = STARTPOS;
        ss >> token;
    }
    else    /// token is "fen"
    {
        token.clear();
        while(true)
        {
            ss >> token;
            if(token.empty() || token == "moves") break;
            FEN += token + " ";
            token.clear();
        }
    }
    init_from_fen(FEN);


    if(token != "moves")       return;

    while(true)
    {
        ss >> token;
        if(token.empty())      break;

        Move move = string_to_move(token);
        Position current_position = position;
        make_move(move, position);

        ++hk_root;
        ++hk_current;
        update_hashkey(move, current_position, position);

        if(position.fifty == 0)
        {
            hashkey[0] = hashkey[hk_current];
            hk_root = 0;
            hk_current = 0;
        }

        token.clear();
    }
}

void init_piece(uint8_t square, unsigned short piece)
{
    piece_list[piece].captured = false;
    piece_list[piece].square = square;
    board[square] = piece;
    hashkey[hk_current] ^= z_piece[PIECE_TO_INDEX[piece >> 4] + SQUARE_TO_INDEX[square]];
}

void init_from_fen(std::string fen)
{
    for(uint8_t i = 0; i < 255; ++i)  board[i] = OUTSIDE;
    for(unsigned short i = 0; i < 1344; ++ i)
    {
        piece_list[i].captured = true;
        piece_list[i].square = 0;
        piece_list[i].mvv_lva = 0;
    }
    piece_list[wKING].mvv_lva = 5;
    for(unsigned short i = wPS; i < wKS; ++i)   {piece_list[i].value = 0;       piece_list[i].mvv_lva = 1;}
    for(unsigned short i = wKS; i < wBS; ++i)   {piece_list[i].value = VALUE_N; piece_list[i].mvv_lva = 2;}
    for(unsigned short i = wBS; i < wRS; ++i)   {piece_list[i].value = VALUE_B; piece_list[i].mvv_lva = 2;}
    for(unsigned short i = wRS; i < wQS; ++i)   {piece_list[i].value = VALUE_R; piece_list[i].mvv_lva = 3;}
    for(unsigned short i = wQS; i < bKING; ++i) {piece_list[i].value = VALUE_Q; piece_list[i].mvv_lva = 4;}
    piece_list[bKING].mvv_lva = 5;
    for(unsigned short i = bPS; i < bKS; ++i)   {piece_list[i].value = 0;       piece_list[i].mvv_lva = 1;}
    for(unsigned short i = bKS; i < bBS; ++i)   {piece_list[i].value = VALUE_N; piece_list[i].mvv_lva = 2;}
    for(unsigned short i = bBS; i < bRS; ++i)   {piece_list[i].value = VALUE_B; piece_list[i].mvv_lva = 2;}
    for(unsigned short i = bRS; i < bQS; ++i)   {piece_list[i].value = VALUE_R; piece_list[i].mvv_lva = 3;}
    for(unsigned short i = bQS; i < 1344; ++i)  {piece_list[i].value = VALUE_Q; piece_list[i].mvv_lva = 4;}


    wPE = wPS; wKE = wKS; wBE = wBS; wRE = wRS; wQE = wQS;
    bPE = bPS; bKE = bKS; bBE = bBS; bRE = bRS; bQE = bQS;
    position.castle = 0;
    position.ep = 0;
    position.fifty = 0;
    hashkey[0] = 0;
    hk_root = 0;
    hk_current = 0;
    piece_material[1] = 0;
    piece_material[2] = 0;

    uint8_t i = 0;
    uint8_t square = 68;

    while(fen[i] != ' ')
    {
        if     (fen[i] == 'P') {init_piece(square, wPE);                                  ++wPE; ++square;}
        else if(fen[i] == 'N') {init_piece(square, wKE);   piece_material[1] += VALUE_N;  ++wKE; ++square;}
        else if(fen[i] == 'B') {init_piece(square, wBE);   piece_material[1] += VALUE_B;  ++wBE; ++square;}
        else if(fen[i] == 'R') {init_piece(square, wRE);   piece_material[1] += VALUE_R;  ++wRE; ++square;}
        else if(fen[i] == 'Q') {init_piece(square, wQE);   piece_material[1] += VALUE_Q;  ++wQE; ++square;}
        else if(fen[i] == 'K') {init_piece(square, wKING);                                       ++square;}
        else if(fen[i] == 'p') {init_piece(square, bPE);                                  ++bPE; ++square;}
        else if(fen[i] == 'n') {init_piece(square, bKE);   piece_material[2] += VALUE_N;  ++bKE; ++square;}
        else if(fen[i] == 'b') {init_piece(square, bBE);   piece_material[2] += VALUE_B;  ++bBE; ++square;}
        else if(fen[i] == 'r') {init_piece(square, bRE);   piece_material[2] += VALUE_R;  ++bRE; ++square;}
        else if(fen[i] == 'q') {init_piece(square, bQE);   piece_material[2] += VALUE_Q;  ++bQE; ++square;}
        else if(fen[i] == 'k') {init_piece(square, bKING);                                       ++square;}
        else if(fen[i] == '/') square += 8;
        else
        {
            for(uint8_t j = 0; j < fen[i] - '0'; ++ j)
            {
                board[square] = EMPTY;
                ++square;
            }
        }
        ++i;
    }
    ++i;

    if(fen[i] == 'w') stm = WHITE;
    else              stm = BLACK;
    if(stm == BLACK) hashkey[hk_current] ^= z_stm;
    i += 2;

    if(fen[i] == '-') i += 2;
    else
    {
        while(fen[i] != ' ')
        {
            if(fen[i] == 'K')       position.castle += 1;
            else if(fen[i] == 'Q')  position.castle += 2;
            else if(fen[i] == 'k')  position.castle += 4;
            else if(fen[i] == 'q')  position.castle += 8;
            ++i;
        }
        ++i;
    }
    hashkey[hk_current] ^= z_castle[position.castle];

    if(fen[i] == '-') i += 2;
    else
    {
        position.ep += fen[i] - 'a';
        ++i;
        position.ep += 196 - 16 * (fen[i] - '0');
        i += 2;
    }
    hashkey[hk_current] ^= z_ep[EP_TO_INDEX[position.ep]];

    position.fifty = fen[i] - '0';
    i += 2;
}

Move string_to_move(std::string str)
{
    Move move;
    move.from = str[0] + 99 - (str[1] - 48) * 16;
    move.to   = str[2] + 99 - (str[3] - 48) * 16;
    if(str.length() == 5)
    {
        if(str[4] == 'q')      move.flags += PROM_QUEEN;
        else if(str[4] == 'r') move.flags += PROM_ROOK;
        else if(str[4] == 'b') move.flags += PROM_BISHOP;
        else                   move.flags += PROM_KNIGHT;

        move.pawn = board[move.from];
    }

    if(board[move.to] != EMPTY) move.capture = board[move.to];

    if(stm == WHITE)
    {
        if(move.from == E1)
        {
            if(move.to == G1 && board[move.from] == wKING)    move.flags += WCS;
            if(move.to == C1 && board[move.from] == wKING)    move.flags += WCL;
        }
        if(board[move.from] & PAWN)
        {
            if(move.from + NN == move.to)    move.ep = move.from + N;
            if(move.to == position.ep)       move.capture = board[move.to + S];
        }
    }
    else
    {
        if(move.from == E8)
        {
            if(move.to == G8 && board[move.from] == bKING)    move.flags += BCS;
            if(move.to == C8 && board[move.from] == bKING)    move.flags += BCL;
        }
        if(board[move.from] & PAWN)
        {
            if(move.from + SS == move.to)    move.ep = move.from + S;
            if(move.to == position.ep)       move.capture = board[move.to + N];
        }
    }

    return move;
}

std::string move_to_string(Move m)
{
    std::string mts = SQUARE_STR[m.from] + SQUARE_STR[m.to];

    if(!(m.flags & PROMOTE))          return mts;
    else if(m.flags & PROM_QUEEN)     mts.push_back('q');
    else if(m.flags & PROM_ROOK)      mts.push_back('r');
    else if(m.flags & PROM_BISHOP)    mts.push_back('b');
    else                              mts.push_back('n');

    return mts;
}

void print_square(unsigned short s)
{
    if(board[s] == EMPTY)   {std::cout << "   |"; return;}
    if(board[s] & WHITE)
    {
        if(board[s] & PAWN)   {std::cout << " X |"; return;}
        if(board[s] & KNIGHT) {std::cout << " N |"; return;}
        if(board[s] & BISHOP) {std::cout << " B |"; return;}
        if(board[s] & ROOK)   {std::cout << " R |"; return;}
        if(board[s] & QUEEN)  {std::cout << " Q |"; return;}
        if(board[s] == wKING) {std::cout << " K |"; return;}
    }
    else
    {
        if(board[s] & PAWN)   {std::cout << " x |"; return;}
        if(board[s] & KNIGHT) {std::cout << " n |"; return;}
        if(board[s] & BISHOP) {std::cout << " b |"; return;}
        if(board[s] & ROOK)   {std::cout << " r |"; return;}
        if(board[s] & QUEEN)  {std::cout << " q |"; return;}
        if(board[s] == bKING) {std::cout << " k |"; return;}
    }
}

void print_board()
{
    for(unsigned short i = 68; i <= 180; i += 16)
    {
        for(unsigned short j = i; j < i + 8; ++j)
        {
            print_square(j);
        }
        if(i < 180) std::cout << "\n---|---|---|---|---|---|---|---|\n";
        else        std::cout << "\n--------------------------------\n";
    }
}

void test()
{
    std::string fen = "8/k7/3p4/p2P1p2/P2P1P2/8/8/K7 w - - 0";

    init_from_fen(fen);
    print_board();
    std::string input = "go movetime 10000 \n";
    std::istringstream ss(input);
    go(ss);
}

uint64_t perft(uint8_t depth, const Position &currentPosition)
{
    if(depth == 0) return 1;
    unsigned int nodes = 0;

    Move moveList[150];
    uint8_t moveCount = generate_all(moveList, currentPosition);

    for(uint8_t i = 1; i < moveCount; ++i)
    {
        Position nextPosition = currentPosition;

        make_move(moveList[i], nextPosition);
        if(!is_attacked(piece_list[(stm ^ SIDE_SWITCH) + KING].square, stm))
        {
            nodes += perft(depth - 1, nextPosition);
        }
        unmake_move(moveList[i]);
    }
    return nodes;
}

void perft_start(uint8_t depth)
{
    init_from_fen(STARTPOS);

    std::cout << "Starting perft " << (int)depth << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    unsigned nodes = perft(depth, position);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time = end-start;

    unsigned nps = nodes / time.count() ;
    std::cout << "\nperft " << (int)depth << " result:\n";
    std::cout << "Time: " << time.count() << "\n";
    std::cout << "Nodes: " << nodes << "\n";
    std::cout << "NPS: " << nps << "\n";
}
