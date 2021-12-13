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

Colour Piece::getColour(){
  return this->colour;
}

PieceType Piece::getType(){
  return this->type;
}

bool Piece::isFriendlyFire(Piece* const square[][MAX_FILE], int sourceRank, 
  int sourceFile, int destRank, int destFile){
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

bool Piece::hasHorizontalObstruction(Piece* const square[][MAX_FILE],
  int sR, int sF,
  int dR, int dF){
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
  int sR, int sF,
  int dR, int dF){
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
  int sR, int sF,
  int dR, int dF){
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

