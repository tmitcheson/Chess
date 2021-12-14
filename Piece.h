#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include "Functions.h"

using namespace std;

// abstract class with a pure virtual function isValidMove()

// many functions make use of the notation sR, sF, dR, dF which stand for
// source piece rank, source piece file, destination piece rank, and
// destination piece file respectively

class Piece{
  protected:
  Colour colour = White;
  PieceType type;
  bool movedYet;
  bool isFriendlyFire(Piece* const square[][MAX_FILE], 
                        int const sourceRank, 
                        int const sourceFile, 
                        int const destRank, 
                        int const destFile);
  
  bool hasHorizontalObstruction(Piece* const square[][MAX_FILE],
                              int const sR, int const sF,
                              int const dR, int const dF);
  bool hasVerticalObstruction(Piece* const square[][MAX_FILE],
                              int const sR, int const sF,
                              int const dR, int const dF);
  bool hasDiagonalObstruction(Piece* const square[][MAX_FILE],
                              int const sR, int const sF,
                              int const dR, int const dF);
  
public:

  Piece();
  void setBlack();
  Colour getColour() const;
  PieceType getType() const;
  virtual bool isValidMove(Piece* const square[][MAX_FILE], 
                            int sourceRank,
                            int sourceFile, 
                            int destRank,
                            int destFile, PieceType& flag) = 0;
  


};

#endif