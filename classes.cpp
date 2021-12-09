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

// PIECE FUNCTIONS //

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
        string output = convertBack(destRank, destFile);
        cerr << square[sourceRank][sourceFile]->getColour() << "'s "
              << square[sourceRank][sourceFile]->getType()
              << " cannot attack own colour piece at " << output << endl;
        return true;
      }
      else return false;
    }
    return false;
}

void Piece::printObstructionError(Piece* square[][MAX_FILE],
  int sR, int sF,
  int dR, int dF,
  int bR, int bF){
    // bR and bF here standing for blockingRank and blockingFile
      string sourceOutput = convertBack(sR, dR);
      string blockOutput = convertBack(bR, bF);
      string destOutput = convertBack(dR, dF);
      cerr << square[sR][sF]->getColour() << "'s "
      << square[sR][sF]->getType() << " at square " << sourceOutput[0] 
      << sourceOutput[1] << " is blocked from moving to "
      << destOutput[0] << destOutput[1] << " by " << square[bR][bF]->getColour()
      << "'s " << square[bR][bF]->getType() << " at square " 
      << blockOutput[0] << blockOutput[1] << endl;
      return;
  }

bool Piece::hasHorizontalObstruction(Piece* square[][MAX_FILE],
  int sR, int dR,
  int sF, int dF){
    if(sF < dF){
      for(int i = sF+1; i < dF; i++){
        if(square[sR][i] != nullptr){
          printObstructionError(square, sR, sF, dR, dF, sR, i);
          return true;
        }
      }
    }
    if(dF < sF){
      for(int i = sF-1; i > dF; i--){
        if(square[sR][i] != nullptr){
          printObstructionError(square, sR, sF, dR, dF, sR, i);
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
          printObstructionError(square, sR, sF, dR, dF, i, sF);
          return true;
        }
      }
    }
    if(dR < sR){
      for(int i = sR-1; i > dR; i--){
        if(square[i][dF] != nullptr){
          printObstructionError(square, sR, sF, dR, dF, i, dF);
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
          printObstructionError(square, sR, sF, dR, dF, i, j);
          return true;
        }
      }
    }
    else if((sR > dR) && (sF < dF)){
      for(int i = sR-1, j = sF+1; i > dR && j < dF; i--, j++){
        if(square[i][j] != nullptr){
          printObstructionError(square, sR, sF, dR, dF, i, j);
          return true;
        }
      }
    }
    else if ((sR < dR) && (sF > dF)){
      for(int i = sR+1, j = sF-1; i < dR && j > dF; i++, j--){
        if(square[i][j] != nullptr){
          printObstructionError(square, sR, sF, dR, dF, i, j);
          return true;
        }
      } 
    }
    else if ((sR > dR) && (sF > dF)){
      for(int i = sR-1, j = sF-1; i > dR && j > dF; i--, j--){
        if(square[i][j] != nullptr){
          printObstructionError(square, sR, sF, dR, dF, i, j);
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

bool King::isValidMove (Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF) {

  // check if it is a logically valid move for a king
  if( ! ((abs(dR - sR) <= 1) && (abs(dF - sF) <= 1))){
    string output = convertBack(dR, dF);
    cerr << this->colour << "'s king cannot move to " << output[0] << output[1] 
    << endl;
    return false;
  }

  // no obstruction checks necessary
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
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

bool Queen::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF){
  if( ! ( ( sR == dR) || (sF == dF) || (abs(dR - sR) == abs(dF - sF)))){
    string output = convertBack(dR, dF);
    cerr << this->colour << "'s queen cannot move to " << output[0] << output[1]
    << endl;
    return false;
  }

  if(sR == dR){
    if(hasHorizontalObstruction(square, sR, sF, dR, dF)){
      return false;
    }
  }
  if(sF == dF){
    if(hasVerticalObstruction(square, sR, sF, dR, dF)){
      return false;
    }
  }
  if(abs((dR - sR) == abs(dF - sF))){
    if(hasDiagonalObstruction(square, sR, sF, dR, dF)){
     return false;
    }
  }
  
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
    return false;
  }
  return true;
}

// KNIGHT

Knight::Knight()
  : Piece(){
    type = knight;
  };

bool Knight::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF){
  
  // check if logically valid move for knight
  if( ! (((abs(dR - sR) == 2) && (abs(dF - sF) == 1)) 
      || ((abs(dR - sR) == 1) && (abs(dF - sF) == 2)))){
        string output = convertBack(dR, dF);
        cerr << this->colour << "'s knight cannot move to " << output[0] 
        << output[1] << endl;
        return false;
  }

  // no need to check for obstruction since knight can jump
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
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

bool Bishop::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF){
  
  // logic for whether bishop is making a valid move
  if( abs(dR - sR) != abs(dF - sF)){
    string output = convertBack(dR, dF);
    cerr << this->colour << "'s bishop cannot move to " << output[0] 
    << output[1] << endl;
    return false;
  }

  // checking for obstructions between source and destination
  if(hasDiagonalObstruction(square, sR, sF, dR, dF) == true){
    return false;
  }
  
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
    return false;
  }

  return true;
}

// ROOK

Rook::Rook()
  : Piece(){
    type = rook;
  };

bool Rook::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF){

  // check if movge is logically valid for a rook piece
  if( ! (sR == dR || sF == dF)){
    string output = convertBack(dR, dF);
    cerr << this-colour << "'s rook cannot move to " << output[0] << output[1]
      << endl;
    return false;
  }

  // check for obstructions between source and destination
  if(sR == dR){
    if(hasHorizontalObstruction(square, sR, sF, dR, dF)){
      return false;
    }
  }
  else if (sF == dF){
    if(hasVerticalObstruction(square, sR, sF, dR, dF)){
      return false;
    }
  }

  // check if destination square has same colour piece as source
  if(isFriendlyFire(square, sR, sF, dR, dF) == true){
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

bool Pawn::isValidMove(Piece* square[][MAX_FILE], int sR, int sF, int dR, int dF){

  if((dR - sR) > 2 || abs(dF - sF) > 1){
    cerr << "Illegal pawn move" << endl;
    return false;
  }
  if((dR - sR) == 2 && movedYet == true){
    cerr << "Pawn can only move forward two on first go. " << endl;
    return false;
  }
  // if pawn is trying to move two forward on it's first go conditions
  if((dR - sR) == 2){
    if( abs(dF - sF) == 1){
      cerr << "Pawn cannot move two up one to the side. Invalid Move. " << endl;
      return false;
    }
    if(square[dR][dF] != nullptr){
      cerr << "Occupied space, pawn cannot move there. " << endl;
      return false;
    }
  }
  // if pawn is trying to move one forward conditions
  if((dR - sR) == 1){
    if(sF == dF){
      if(square[dR][dF] != nullptr){
        cerr << "Occupied space, pawn cannot move there. " << endl;
        return false;
      }
    }
    if(abs(sF - dF) == 1){
      if(square[dR][dF] == nullptr){
        cerr << "Pawn cannot move diagonally with no piece to take. " << endl;
        return false;
      }
      if(square[dR][dF]->getColour() == this->colour){
        cerr << "Pawn cannot attack own team. " << endl;
        return false;
      }
    }
  }
  return true;
}

// BOARD FUNCTIONS //

