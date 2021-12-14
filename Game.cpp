#include <iostream>
#include <string>
#include <cstring>
#include "Functions.h"
#include "Piece.h"
#include "ChessBoard.h"
#include "Game.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

void Game::toggleTurn(){
    turn = (turn == Black) ? White : Black;
}

Colour Game::getTurn() const{
    return this->turn;
}

void Game::resetTurn(){
    turn = White;
}

// pair of functions working together to make hypotheticial moves by use
// of a reference to a pointer named temp, which keeps the history of the 
// source tile ready for re-entry after checks for check
void Game::makeTempMove(Piece* square[][MAX_FILE], Piece*& temp, int const sR, 
                        int const sF, int const dR, int const dF){
  temp = square[dR][dF];
  square[dR][dF] = square[sR][sF];
  square[sR][sF] = nullptr;
}

void Game::undoTempMove(Piece* square[][MAX_FILE], Piece*& temp, int const sR, 
                        int const sF, int const dR, int const dF){
  square[sR][sF] = square[dR][dF];
  square[dR][dF] = temp;
  temp = nullptr;
}

// kR and kF stand for kingRank and kingFile respectively
void Game::identifyOwnKing(Piece* const square[][MAX_FILE], int& kR,
  int& kF){
  for(kR = 0; kR < MAX_RANK; kR++){
    for(kF = 0; kF < MAX_FILE; kF++){
      if(square[kR][kF] != nullptr){
        if(square[kR][kF]->getType() == king){
          if(square[kR][kF]->getColour() == turn){
            return;
          }
        }
      }
    }
  }
}


bool Game::isInCheck(Piece* square[][MAX_FILE]) {
  // identify own king
  int kR, kF;
  identifyOwnKing(square, kR, kF);
  // algorithm requires iterating through all of possible moves for opposition
  // and seeing if any of them are able to legally reach our king. Hence we 
  // temporarily toggle turn to hypothetically run through moves
  toggleTurn();
  // for every square
  for(int i = 0; i < MAX_RANK; i++){
    for(int j = 0; j < MAX_FILE; j++){
      // which has a piece
      if(square[i][j] != nullptr){
        // of opposition turn's colour,
        if(square[i][j]->getColour() == turn){
          // if that piece has a valid move which finds own king
          PieceType flag;
          if(square[i][j]->isValidMove(square, i, j, kR, kF, flag)){
            // then we are in check. Toggle back to correct player's move and
            // return true
            toggleTurn();
            return true;
          }
        }
      }
    }
  }
  // if no pieces were able to access the king, we return false as we are not
  // in check
  toggleTurn();
  return false;
}

// helper function for determining checkmate. Also makes use of the temp move
// functions to see if we remain in check even after any hypothetical move is 
// made. Despite not being the most efficient as it runs a lot of iterations, 
// the function does account for: moving the king out of check, taking the 
// attacking piece, and obstructing the checking line. In this way it is 
// is comprehensive even if not efficent
bool Game::isStillInCheck(Piece* square[][MAX_FILE], int const sR, int const sF,
                                                     int const dR, int const dF){
  Piece* temp = nullptr;
  makeTempMove(square, temp, sR, sF, dR, dF);
  if(! (isInCheck(square))){
    undoTempMove(square, temp, sR, sF, dR, dF);
    return false;   
  }
  // if the king is still in check after the move
  undoTempMove(square, temp, sR, sF, dR, dF);
  return true;
}


bool Game::isInStalemate(Piece* square[][MAX_FILE]){
  // for every move
  for(int i = 0; i < MAX_RANK; i++){
    for(int j = 0; j < MAX_FILE; j++){
      for(int m = 0; m < MAX_RANK; m++){
        for(int n = 0; n < MAX_FILE; n++){
          // which has a piece of our turn's colour
          if(square[m][n] != nullptr){
            if(square[m][n]->getColour() == turn){
              PieceType flag;
              // if that piece has a valid move to make...
              if(square[m][n]->isValidMove(square, m, n, i, j, flag)){
                Piece* temp = nullptr;
                makeTempMove(square, temp, m, n, i, j);
                // which doesn't put ourselves in check
                if(!isInCheck(square)){
                  // then we are not in a stalemate
                  undoTempMove(square, temp, m, n, i, j);
                  return false;
                }
                undoTempMove(square, temp, m, n, i, j); 
              }
            }
          }
        }
      }
    }
  }
  // else if we have exhausted every eventuality without success we are 
  // in stalemate
  return true;
}

bool Game::isInCheckmate(Piece* square[][MAX_FILE]){
    int kR, kF;
    identifyOwnKing(square, kR, kF);
    // for any given move the checked side can make...
    for(int i = 0; i < MAX_RANK; i++){
      for(int j = 0; j < MAX_FILE; j++){
        for(int m = 0; m < MAX_RANK; m++){
          for(int n = 0; n < MAX_FILE; n++){
            if(square[m][n] != nullptr){
              if(square[m][n]->getColour() == turn){
                PieceType flag;
                if(square[m][n]->isValidMove(square, m, n, i, j, flag)){
                  // if they are not in check after that move is made
                  if(! (isStillInCheck(square, m, n, i, j))){
                    // then they are not in checkmate
                    return false;
                  }
                }
              }
            }
          }
        }
      }   
    }
    // if the king has no valid moves to make which don't keep him in check then 
    // we are in checkmate so return true
    return true;    
}

bool Game::isGameOver(Piece* square[][MAX_FILE]){
    if(isInCheck(square)){
        if(isInCheckmate(square)){
          cout << getTurn() << " is in checkmate" << endl;
          return true;
        }
        cout << getTurn() << " is in check" << endl;
    }
    if(isInStalemate(square)){
      cout << getTurn() << " is in stalemate " << endl;
      return true;
    }

  return false;
}

