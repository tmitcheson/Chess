#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Functions.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Game.h"

using namespace std;

class ChessBoard {
  Piece* square[8][8];
  Game game;
  
  Pawn whitePawn[PAWNS_PER_COLOUR];
  Rook whiteRook[ROOKS_PER_COLOUR];
  Knight whiteKnight[KNIGHTS_PER_COLOUR];
  Bishop whiteBishop[BISHOPS_PER_COLOUR];
  King whiteKing;
  Queen whiteQueen;
  Pawn blackPawn[PAWNS_PER_COLOUR];
  Rook blackRook[ROOKS_PER_COLOUR];
  Knight blackKnight[KNIGHTS_PER_COLOUR];
  Bishop blackBishop[BISHOPS_PER_COLOUR];
  King blackKing;
  Queen blackQueen;

public:
  ChessBoard();
  void submitMove(const char* source, const char* dest);
  void resetBoard();
  bool hasPiece(int rank, int file);
  void printMoveToMake(int sourceRank, int sourceFile, int destRank, int destFile);
  void makeMove(int sourceRank, int sourceFile, int destRank, int destFile);
  bool isInCheck(Piece* square[][MAX_FILE]);
  void identifyOppositionKing(Piece* square[][MAX_FILE], int& kR, int& kF);

};

#endif