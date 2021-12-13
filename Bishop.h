#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

using namespace std;

class Bishop : public Piece {
  public:
  Bishop();
  bool isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};


#endif