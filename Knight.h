#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

using namespace std;

class Knight : public Piece {
  public:
  Knight();
  bool isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};




#endif