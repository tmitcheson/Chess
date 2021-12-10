#include <iostream>
#include <string>
#include <cstring>
#include "classes.h"

using namespace std;

void Game::toggleTurn(){
    turn = (turn == Black) ? White : Black;
}

Colour Game::getTurn(){
    return this->turn;
}

void Game::resetTurn(){
    turn = White;
}

void Game::makeMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF){
  square[dR][dF] = square[sR][sF];
  square[sR][sF] = nullptr;
  
}

void Game::makeTempMove(Piece* square[][MAX_FILE], Piece*& temp, int sR, int sF, int dR, int dF){
  temp = square[dR][dF];
  square[dR][dF] = square[sR][sF];
  square[sR][sF] = nullptr;
}

void Game::undoTempMove(Piece* square[][MAX_FILE], Piece*& temp, int sR, int sF, int dR, int dF){
  square[sR][sF] = square[dR][dF];
  square[dR][dF] = temp;
  temp = nullptr;
}

void Game::identifyOwnKing(Piece* square[][MAX_FILE], int& kR,
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

bool Game::InCheck(Piece* square[][MAX_FILE]){
    // identify opposition king
  int kR, kF;
  identifyOwnKing(square, kR, kF);
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
            toggleTurn();
            return true;
          }
        }
      }
    }
  }
  toggleTurn();
  return false;
}

bool Game::isStillInCheck(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF){
  Piece* temp = nullptr;
  makeTempMove(square, temp, sR, sF, dR, dF);
  if(! (InCheck(square))){
    undoTempMove(square, temp, sR, sF, dR, dF);
    
    return false;   
  }
  // if the king is still in check after the move
  undoTempMove(square, temp, sR, sF, dR, dF);
  return true;
}

bool Game::inCheckmate(Piece* square[][MAX_FILE]){
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
    if(InCheck(square)){
        if(inCheckmate(square)){
          cout << getTurn() << " is in checkmate." << endl;
          return true;
        }
        cout << getTurn() << " is in check." << endl;
    }


    // if there are no valid moves then checkmate
    /*if(inCheckmate(square)){
      toggleTurn();
      cout << getTurn() << " is in checkmate." << endl;
      toggleTurn();
    }
  }

  // if there are no valid moves then stalemate

    */
   return false;
}

