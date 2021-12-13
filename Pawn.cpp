#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "Piece.h"
#include "Functions.h"
#include "Pawn.h"

using namespace std;

Pawn::Pawn()
  : Piece(){
    type = pawn;
    movedYet = false;
  };

void Pawn::moveConfirmed(bool movedYet){
  movedYet = (movedYet == false)? true: true;
}


bool Pawn::isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
    int dF, PieceType& flag){

    int sourceRank = sR;
    int sourceFile = sF;
    int destRank = dR;
    int destFile = dF;

    if(square[sR][sF]->getColour() == White){
      int tempR = sR;
      sR = dR;
      dR = tempR;
      int tempF = sF;
      sF = dF;
      dF = tempF;
    }

    if(dR - sR == 1){ 
      if(dF - sF == 0 && square[destRank][destFile] == nullptr){
        this->moveConfirmed(movedYet);
        return true;
      }
      else if(abs(dF - sF) == 1 && square[destRank][destFile] != nullptr &&
          square[destRank][destFile]->getColour() != 
          square[sourceRank][sourceFile]->getColour()){
        this->moveConfirmed(movedYet);
        return true;
      } 
    }
    
    if(dR - sR == 2 && movedYet == false){
      if(dF - sF == 0){
        if(!(hasVerticalObstruction(square, sR, sF, dR, dF))){
          this->moveConfirmed(movedYet);
          return true;
        }
      }
    }
    flag = pawn;
    return false;
    }