#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

using namespace std;

class Queen : public Piece {
  public:
  Queen();
  bool isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

#endif