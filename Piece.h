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
  
public:

  Piece();
  void setBlack();
  Colour getColour();
  PieceType getType();
  bool isFriendlyFire(Piece* const square[][MAX_FILE], 
                        int sourceRank, 
                        int sourceFile, 
                        int destRank, 
                        int destFile);
  virtual bool isValidMove(Piece* const square[][MAX_FILE], 
                            int sourceRank,
                            int sourceFile, 
                            int destRank,
                            int destFile, PieceType& flag) = 0;
  bool hasHorizontalObstruction(Piece* const square[][MAX_FILE],
                              int sR, int sF,
                              int dR, int dF);
  bool hasVerticalObstruction(Piece* const square[][MAX_FILE],
                              int sR, int sF,
                              int dR, int dF);
  bool hasDiagonalObstruction(Piece* const square[][MAX_FILE],
                              int sR, int sF,
                              int dR, int dF);


};

#endif