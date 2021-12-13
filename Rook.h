#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

using namespace std;

class Rook : public Piece {
  public:
  Rook();
  bool isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

#endif