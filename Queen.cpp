#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "Piece.h"
#include "Functions.h"
#include "Queen.h"

using namespace std;

Queen::Queen()
  : Piece(){
    type = queen;
  };

bool Queen::isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR,
   int dF, PieceType& flag){

  if( ! ( ( sR == dR) || (sF == dF) || (abs(dR - sR)) == (abs(dF - sF)))){
    flag = queen;
    return false;
  }

  if(sR == dR){
    if(hasHorizontalObstruction(square, sR, sF, dR, dF)){
      flag = queen;
      return false;
    }
  }
  if(sF == dF){
    if(hasVerticalObstruction(square, sR, sF, dR, dF)){
      flag = queen;
      return false;
    }
  }
  if((abs(dR - sR)) == (abs(dF - sF))){
    if(hasDiagonalObstruction(square, sR, sF, dR, dF)){
      flag = queen;
      return false;
    }
  }
  
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
    flag = queen;
    return false;
  }
  return true;
}