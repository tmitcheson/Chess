#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

using namespace std;

class Pawn : public Piece {
  public:
  Pawn();
  bool isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
  void moveConfirmed(bool movedYet);
};



#endif