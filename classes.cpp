#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "classes.h"

using namespace std;

// function which converts coordinates from chess notation
// into array indices
void converter(const char* position, int& rank, int& file){
  rank = position[1] - '0';
  rank = 8 - rank;
  file = position[0] - 'A';
}

// function which converts array indices into chess notation
string convertBack(int rank, int file){
  string output;
  rank = 8 - rank;
  output[1] = rank + '0';
  output[0] = file + 'A';
  return output;
}

ostream &operator<<(ostream& o, Colour colour){
  const string stringColour[] = { "White", "Black" };
  return o << stringColour[colour];
}

ostream &operator<<(ostream& o, PieceType type){
  const string stringType[] = { "king", "queen", "rook", "knight", "bishop", "pawn" };
  return o << stringType[type];
}

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

bool Piece::isFriendlyFire(Piece* square[][MAX_FILE], int sourceRank, 
  int sourceFile, int destRank, int destFile){
    // if the destination square isn't empty...
    if(square[destRank][destFile] != nullptr){
      // and if the piece at dest is the same colour as the piece at source...
      if(square[sourceRank][sourceFile]->getColour()
              == square[destRank][destFile]->getColour()){
                // we have a problem, so error message and return true...
        //string output = convertBack(destRank, destFile);
        //cerr << square[sourceRank][sourceFile]->getColour() << "'s "
        //      << square[sourceRank][sourceFile]->getType()
        //      << " cannot attack own colour piece at " << output[0] << output[1] << endl;
        return true;
      }
      else return false;
    }
    return false;
}

bool Piece::hasHorizontalObstruction(Piece* square[][MAX_FILE],
  int sR, int dR,
  int sF, int dF){
    if(sF < dF){
      for(int i = sF+1; i < dF; i++){
        if(square[sR][i] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, sR, i);
          return true;
        }
      }
    }
    if(dF < sF){
      for(int i = sF-1; i > dF; i--){
        if(square[sR][i] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, sR, i);
          return true;
        }
      }
    }
    return false;
    }

bool Piece::hasVerticalObstruction(Piece* square[][MAX_FILE],
  int sR, int sF,
  int dR, int dF){
    if(sR < dR){
      for(int i = sR+1; i < dR; i++){
        if(square[i][sF] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, i, sF);
          return true;
        }
      }
    }
    if(dR < sR){
      for(int i = sR-1; i > dR; i--){
        if(square[i][dF] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, i, dF);
          return true;
        }
      }
    }
    return false;
  }

bool Piece::hasDiagonalObstruction(Piece* square[][MAX_FILE],
  int sR, int sF,
  int dR, int dF){
    if((sR < dR) && (sF < dF)){
      for(int i = sR+1, j = sF+1; i < dR && j < dF; i++, j++){
        if(square[i][j] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, i, j);
          return true;
        }
      }
    }
    else if((sR > dR) && (sF < dF)){
      for(int i = sR-1, j = sF+1; i > dR && j < dF; i--, j++){
        if(square[i][j] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, i, j);
          return true;
        }
      }
    }
    else if ((sR < dR) && (sF > dF)){
      for(int i = sR+1, j = sF-1; i < dR && j > dF; i++, j--){
        if(square[i][j] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, i, j);
          return true;
        }
      } 
    }
    else if ((sR > dR) && (sF > dF)){
      for(int i = sR-1, j = sF-1; i > dR && j > dF; i--, j--){
        if(square[i][j] != nullptr){
          // printObstructionError(square, sR, sF, dR, dF, i, j);
          return true;
        }
      }
    }
    return false;
  }


bool Piece::isBlack(){
  bool returner = (this->colour == Black) ? true : false;
  return returner;
}



// KING 



King::King()
  : Piece(){
    type = king;
  };

bool King::isValidMove (Piece* square[][MAX_FILE], int sR, int sF, int dR,
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


// QUEEN

Queen::Queen()
  : Piece(){
    type = queen;
  };

bool Queen::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR,
   int dF, PieceType& flag){

  if( ! ( ( sR == dR) || (sF == dF) || (abs(dR - sR) == abs(dF - sF)))){
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
  if(abs((dR - sR) == abs(dF - sF))){
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

// KNIGHT

Knight::Knight()
  : Piece(){
    type = knight;
  };

bool Knight::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
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

// bool Piece::hasDiagonalObstruction
// BISHOP

Bishop::Bishop()
  : Piece(){
    type = bishop;
  };

bool Bishop::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
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

// ROOK

Rook::Rook()
  : Piece(){
    type = rook;
  };

bool Rook::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
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

// PAWN

Pawn::Pawn()
  : Piece(){
    type = pawn;
    movedYet = false;
  };

void Pawn::moveConfirmed(bool movedYet){
  movedYet = (movedYet == false)? true: true;
}
/*
bool Pawn::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
    int dF, PieceType& flag){
  
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

  if((dR - sR) > 2 || abs(dF - sF) > 1 || (dR - sR) == 0){
    flag = pawn;
    return false;
  }

  if((dR - sR) == 2 && movedYet == true){
    flag = pawn;
    return false;
  }
  // if 'pawn is trying to move two forward on its first go' conditions
  if((dR - sR) == 2){
    if( abs(dF - sF) == 1){
      flag = pawn;
      return false;
    }
    if(square[destRank][destFile] != nullptr){
      flag = pawn;
      return false;
    }
  }
  // if pawn is trying to move one forward conditions
  if((dR - sR) == 1){
    if(sF == dF){
      if(square[destRank][destFile] != nullptr){
        flag = pawn;
        return false;
      }
    }
    if(abs(sF - dF) == 1){
      if(square[destRank][destFile] == nullptr){
        flag = pawn;
        return false;
      }
      if(square[destRank][destFile]->getColour() == this->colour){
        flag = pawn;
        return false;
      }
    }
  }
  moveConfirmed();
  return true;
} */

bool Pawn::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, 
    int dF, PieceType& flag){

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
      else if(abs(dF - sF) == 1 && square[destRank][destFile] != nullptr){
        this->moveConfirmed(movedYet);
        return true;
      } 
    }
    
    if(dR - sR == 2 && movedYet == false){
      if(dF - sF == 0){
        this->moveConfirmed(movedYet);
        return true;
      }
    }
    flag = pawn;
    return false;
    }
// BOARD FUNCTIONS //

