#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "Piece.h"
#include "Functions.h"
#include "Rook.h"

using namespace std;

Rook::Rook()
  : Piece(){
    type = rook;
  };

bool Rook::isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
    int dF, PieceType& flag){

  // check if movge is logically valid for a rook piece
  if( ! (sR == dR || sF == dF)){
    flag = rook;
    return false;
  }

  // check for obstructions between source and destination
  if(sR == dR){
    if(hasHorizontalObstruction(square, sR, sF, dR, dF)){
      flag = rook;
      return false;
    }
  }
  else if (sF == dF){
    if(hasVerticalObstruction(square, sR, sF, dR, dF)){
      flag = rook;
      return false;
    }
  }

  // check if destination square has same colour piece as source
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
    flag = rook;
    return false;
  }

  // all rook checks complete and no invalidity so return true
  return true;
} 