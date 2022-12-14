#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

#include "Piece.h"
#include "Functions.h"

using namespace std;

Piece::Piece(){};

void Piece::setBlack(){
  this->colour = Black;
}

Colour Piece::getColour() const {
  return this->colour;
}

PieceType Piece::getType() const {
  return this->type;
}

// function checks for if the piece on the destination square is the same team
bool Piece::isFriendlyFire(Piece* const square[][MAX_FILE], 
  int const sourceRank, int const sourceFile, int const destRank, 
  int const destFile){
    // if the destination square isn't empty...
    if(square[destRank][destFile] != nullptr){
      // and if the piece at dest is the same colour as the piece at source...
      if(square[sourceRank][sourceFile]->getColour()
              == square[destRank][destFile]->getColour()){
                // we have a problem, so error message and return true...
                return true;
      }
    }
    return false;
}

// following three functions check for if there is an obstruction between 
// the source square (sR = sourceRank, etc.) and destination square
bool Piece::hasHorizontalObstruction(Piece* const square[][MAX_FILE],
  int const sR, int const sF,
  int const dR, int const dF){
    if(sF < dF){
      for(int i = sF+1; i < dF; i++){
        if(square[sR][i] != nullptr){
          return true;
        }
      }
    }
    if(dF < sF){
      for(int i = sF-1; i > dF; i--){
        if(square[sR][i] != nullptr){
          return true;
        }
      }
    }
    return false;
  }

bool Piece::hasVerticalObstruction(Piece* const square[][MAX_FILE],
  int const sR, int const sF,
  int const dR, int const dF){
    if(sR < dR){
      for(int i = sR+1; i < dR; i++){
        if(square[i][sF] != nullptr){
          return true;
        }
      }
    }
    if(dR < sR){
      for(int i = sR-1; i > dR; i--){
        if(square[i][dF] != nullptr){
          return true;
        }
      }
    }
    return false;
  }

bool Piece::hasDiagonalObstruction(Piece* const square[][MAX_FILE],
  int const sR, int const sF,
  int const dR, int const dF){
    if((sR < dR) && (sF < dF)){
      for(int i = sR+1, j = sF+1; i < dR && j < dF; i++, j++){
        if(square[i][j] != nullptr){
          return true;
        }
      }
    }
    else if((sR > dR) && (sF < dF)){
      for(int i = sR-1, j = sF+1; i > dR && j < dF; i--, j++){
        if(square[i][j] != nullptr){
          return true;
        }
      }
    }
    else if ((sR < dR) && (sF > dF)){
      for(int i = sR+1, j = sF-1; i < dR && j > dF; i++, j--){
        if(square[i][j] != nullptr){
          return true;
        }
      } 
    }
    else if ((sR > dR) && (sF > dF)){
      for(int i = sR-1, j = sF-1; i > dR && j > dF; i--, j--){
        if(square[i][j] != nullptr){
          return true;
        }
      }
    }

    return false;
  }

