#ifndef KING_H
#define KING_H

#include "Piece.h"

using namespace std;


class King : public Piece {
  public:
  King();
  bool isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

#endif