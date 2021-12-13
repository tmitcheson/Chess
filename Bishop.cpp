#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "Piece.h"
#include "Functions.h"
#include "Bishop.h"


using namespace std;

Bishop::Bishop()
  : Piece(){
    type = bishop;
  };

bool Bishop::isValidMove(Piece* const square[][MAX_FILE], int sR, int sF, int dR, 
    int dF, PieceType& flag){
  
  // logic for whether bishop is making a valid move
  if( abs(dR - sR) != abs(dF - sF)){
    flag = bishop;
    return false;
  }

  // checking for obstructions between source and destination
  if(hasDiagonalObstruction(square, sR, sF, dR, dF) == true){
    flag = bishop;
    return false;
  }
  
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
    flag = bishop;
    return false;
  }

  return true;
}