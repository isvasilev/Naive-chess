#include "data.h"


unsigned short board[256];               /// square - empty or outside or index of the piece in the pieceList
Position position;                       /// copy - make for ep, castling rights and fifty rule
unsigned short stm;                      /// side to move
Piece piece_list[1344];                  /// is piece captured  / where on the board is the piece / order value
unsigned short wPE, wKE, wBE, wRE, wQE;  /// white pieces end indexes in the piece list
unsigned short bPE, bKE, bBE, bRE, bQE;  /// black pieces end indexes in the piece list
short ply;
short piece_material[3];                 /// used for delta pruning in q search

bool stop_search;
