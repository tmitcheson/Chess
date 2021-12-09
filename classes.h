#pragma once
#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <cstring>

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

class Piece{
  protected:
  Colour colour = White;
  PieceType type;
  bool movedYet;
  int file, rank;
  // string location ?
  
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
                            int destFile) = 0;
  void printObstructionError(Piece* square[][MAX_FILE],
                            int sR, int sF,
                            int dR, int dF,
                            int bR, int bF);
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


  // virtual bool isLegalMove();

};

/* SPACE FOR ALL THE DERIVED PIECES */

class King : public Piece {
  public:
  King();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF) override;
};

class Queen : public Piece {
  public:
  Queen();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF) override;
};

class Knight : public Piece {
  public:
  Knight();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF) override;
};

class Bishop : public Piece {
  public:
  Bishop();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF) override;
};

class Rook : public Piece {
  public:
  Rook();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF) override;
};

class Pawn : public Piece {
  public:
  Pawn();
  bool isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF) override;
};

/* PIECES SECTION FINISHED */

class Game {
  Colour turn = White;

  public:
  void toggleTurn();
  Colour getTurn(); 
  void resetTurn();
  bool inCheck();
  bool inCheckmate();
  bool inStatemate();
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
  void makeMove(int sourceRank, int sourceFile, int destRank, int destFile);
  

};





#endif