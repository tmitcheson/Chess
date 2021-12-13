#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "Piece.h"
#include "Functions.h"
#include "Knight.h"

using namespace std;

Knight::Knight()
  : Piece(){
    type = knight;
  };

bool Knight::isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
    int dF, PieceType& flag){
  
  // check if logically valid move for knight
  if( ! (((abs(dR - sR) == 2) && (abs(dF - sF) == 1)) 
      || ((abs(dR - sR) == 1) && (abs(dF - sF) == 2)))){
        flag = knight;
        return false;
  }

  // no need to check for obstruction since knight can jump
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
    flag = knight;
    return false;
  }

  // knight checks completed
  return true;

}