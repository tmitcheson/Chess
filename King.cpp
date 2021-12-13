#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "Piece.h"
#include "Functions.h"
#include "King.h"

using namespace std;


King::King()
  : Piece(){
    type = king;
  };

bool King::isValidMove (Piece* const square[][MAX_FILE], int sR, int sF, int dR,
  int dF, PieceType& flag) {

  // check if it is a logically valid move for a king
  if( ! ((abs(dR - sR) <= 1) && (abs(dF - sF) <= 1))){
    flag = king;
    return false;
  }

  // no obstruction checks necessary
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
    flag = king;
    return false;
  }

  // logically valid
  return true;
}