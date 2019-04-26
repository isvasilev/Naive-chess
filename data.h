#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <cstdint>

/// increments for move generation
constexpr int8_t            NNW{-33},  NN{-32},   NNE{-31};
constexpr int8_t  NWW{-18}, NW{-17},   N{-16},    NE{-15},   NEE{-14};
constexpr int8_t            W{-1},                E{1};
constexpr int8_t  SWW{14},  SW{15},    S{16},     SE{17},    SEE{18};
constexpr int8_t            SSW{31},   SS{32},    SSE{33};
constexpr int8_t INCR[8] = {NW, NE, SE, SW, N, E, S, W};

/// squares used for castle generating/moving
constexpr uint8_t A1{180}, B1{181}, C1{182}, D1{183}, E1{184}, F1{185}, G1{186}, H1{187};
constexpr uint8_t A8{68},  B8{69},  C8{70},  D8{71},  E8{72},  F8{73},  G8{74},  H8{75};

///used with & to switch side to move
constexpr unsigned short SIDE_SWITCH{1536};

///the general numbers for board square
///combinations of these numbers can be created to check for anything on square
constexpr unsigned short WHITE{512}, BLACK{1024}, OUTSIDE{2048}, EMPTY{4096};
constexpr unsigned short KING{8}, PAWN{16}, KNIGHT{32}, BISHOP{64}, ROOK{128}, QUEEN{256};

///start position of type of pieces in the piece list
constexpr unsigned short wKING{520}, wPS{528}, wKS{544}, wBS{576}, wRS{640}, wQS{768};
constexpr unsigned short bKING{1032}, bPS{1040}, bKS{1056}, bBS{1088}, bRS{1152}, bQS{1280};

///made up of numbers above when I needed them
constexpr unsigned short WHITE_OR_OUT{2560}, NOT_WP{7656}, NOT_WB_NOT_EMPTY{3512}, NOT_WR_NOT_EMPTY(3448), NOT_WQ_NOT_EMPTY{3320};
constexpr unsigned short BLACK_OR_OUT{3072}, NOT_BP{7144}, NOT_BB_NOT_EMPTY{3000}, NOT_BR_NOT_EMPTY(2936), NOT_BQ_NOT_EMPTY{2808};

///numbers used for castling/promotions
constexpr uint8_t CASTLE{15}, WCS{1}, WCL{2}, BCS{4}, BCL{8};
constexpr uint8_t PROMOTE{240}, PROM_QUEEN{16}, PROM_ROOK{32}, PROM_BISHOP{64}, PROM_KNIGHT{128};
constexpr uint8_t PROM_TYPE[4] = {PROM_QUEEN, PROM_ROOK, PROM_BISHOP, PROM_KNIGHT};

constexpr short MATE{-30000}, TT_MATE{29000}, STALEMATE{0};
constexpr short MAX_PLY{50};
constexpr uint8_t MAX_DEPTH{50};

constexpr short VALUE_Q{940}, VALUE_R{500}, VALUE_B{310}, VALUE_N{308}, VALUE_P{100};
constexpr short ENDGAME_PIECE_MATERIAL{1300};

struct Position
{
    uint8_t castle{0};  /// 1- White short, 2 - White long, 4 - Black short, 8 - Black long
    uint8_t ep{0};      /// index of the ep square in the board array
    uint8_t fifty{0};   /// half moves from last capture or pawn move
};

struct Piece
{
    bool captured{true};   /// if TRUE piece will be skipped when iterating the pieceList
    uint8_t square{0};     /// location of the piece in the board array
    uint8_t mvv_lva{0};    /// used for MVV/LVA move ordering
    short value{0};        /// this is used to update piece material in make/unmake move
};

struct Move
{
    uint8_t from{0};
    uint8_t to{0};
    unsigned short capture{0};     /// what piece is captured
    uint8_t ep{0};                 /// ep square for next position
    uint8_t flags{0};              /// bits for castle and promotions
    unsigned short pawn{0};        /// to restore promoted pawn in unmake
    uint8_t order_score{0};        /// for move ordering inside the search;
    uint8_t id{0};                 /// used to save the best move in the hash table
};

extern unsigned short board[256];
extern Position position;
extern unsigned short stm;
extern Piece piece_list[1344];
extern unsigned short wPE, wKE, wBE, wRE, wQE;
extern unsigned short bPE, bKE, bBE, bRE, bQE;
extern short piece_material[3];
extern short ply;
extern bool stop_search;

#endif // DATA_H_INCLUDED
