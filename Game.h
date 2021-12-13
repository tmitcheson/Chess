#ifndef GAME_H
#define GAME_H

#include "Functions.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

class Game {
  Colour turn = White;

  public:
  void toggleTurn();
  Colour getTurn(); 
  void resetTurn();
  bool isGameOver(Piece* square[][MAX_FILE]);
  bool isInCheck(Piece* square[][MAX_FILE]);
  void identifyOwnKing(Piece* const square[][MAX_FILE], int& kR, int& kF);
  bool isInCheckmate(Piece* square[][MAX_FILE]);
  bool isStillInCheck(Piece* square[][MAX_FILE], int sR, int sF, 
                                                 int dR, int dF);
  bool isInStalemate(Piece* square[][MAX_FILE]);
  void makeTempMove(Piece* square[][MAX_FILE], Piece*& temp, int const sR,
                     int const sF, int const dR, int const dF);
  void undoTempMove(Piece* square[][MAX_FILE], Piece*& temp, int const sR, 
                     int const sF, int const dR, int const dF);
  void makeMove(Piece* square[][MAX_FILE], int const sR, int const sF, 
                                           int const dR, int const dF);
};


#endif