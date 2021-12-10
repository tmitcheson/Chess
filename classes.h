#pragma once
#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
// #include "Piece.h"

int const MAX_FILE = 8;
int const MAX_RANK = 8;
int const ROOKS_PER_COLOUR = 2;
int const KNIGHTS_PER_COLOUR = 2;
int const BISHOPS_PER_COLOUR = 2;
int const PAWNS_PER_COLOUR = 8;

using namespace std;

enum Colour { White, Black };
enum PieceType { king, queen, rook, knight, bishop, pawn };

ostream &operator<<(ostream& o, Colour colour);
ostream &operator<<(ostream& o, PieceType type);
void converter(const char* position, int& rank, int& file);
string convertBack(int rank, int file);


/* SPACE FOR ALL THE DERIVED PIECES */

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
  bool isFriendlyFire(Piece* square[][MAX_FILE], 
                        int sourceRank, 
                        int sourceFile, 
                        int destRank, 
                        int destFile);
  virtual bool isValidMove(Piece* square[][MAX_FILE], 
                            int sourceRank,
                            int sourceFile, 
                            int destRank,
                            int destFile, PieceType& flag) = 0;
  bool hasHorizontalObstruction(Piece* square[][MAX_FILE],
                              int sR, int sF,
                              int dR, int dF);
  bool hasVerticalObstruction(Piece* square[][MAX_FILE],
                              int sR, int sF,
                              int dR, int dF);
  bool hasDiagonalObstruction(Piece* square[][MAX_FILE],
                              int sR, int sF,
                              int dR, int dF);

  bool isBlack();

};


class King : public Piece {
  public:
  King();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

class Queen : public Piece {
  public:
  Queen();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

class Knight : public Piece {
  public:
  Knight();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

class Bishop : public Piece {
  public:
  Bishop();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

class Rook : public Piece {
  public:
  Rook();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
};

class Pawn : public Piece {
  public:
  Pawn();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
                  int dF, PieceType& flag) override;
  void moveConfirmed(bool movedYet);
};

/* PIECES SECTION FINISHED */

class Game {
  Colour turn = White;

  public:
  void toggleTurn();
  Colour getTurn(); 
  void resetTurn();
  bool isGameOver(Piece* square[][MAX_FILE]);
  bool InCheck(Piece* square[][MAX_FILE]);
  void identifyOwnKing(Piece* square[][MAX_FILE], int& kR, int& kF);
  bool inCheckmate(Piece* square[][MAX_FILE]);
  bool isStillInCheck(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF);
  bool inStatemate();
  void makeTempMove(Piece* square[][MAX_FILE], Piece*& temp, int sR, int sF, int dR, int dF);
  void undoTempMove(Piece* square[][MAX_FILE], Piece*& temp, int sR, int sF, int dR, int dF);
  void makeMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF);
};


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