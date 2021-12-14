#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "Functions.h"

using namespace std;

// function which converts coordinates from chess notation
// into array indices, which includes swapping their order
void converter(const char* position, int& rank, int& file){
  rank = position[1] - '0';
  rank = 8 - rank;
  file = position[0] - 'A';
}

// function which converts array indices back into chess notation
string convertBack(int rank, int file){
  string output;
  rank = 8 - rank;
  output[1] = rank + '0';
  output[0] = file + 'A';
  return output;
}

// checks that input is within chessboard boundaries
bool isValidInput(int sR, int sF, int dR, int dF){
  int test[4];
  test[0] = sR;
  test[1] = sF;
  test[2] = dR;
  test[3] = dF;
  for(int i = 0; i < 4; i++){
    if(test[i] >= 8 || test[i] < 0){
      return false;
    }
  }
  return true;
}

// two functions of overloaded insertion operators which help
// with identifying errors in error messages
ostream &operator<<(ostream& o, Colour colour){
  const string stringColour[] = { "White", "Black" };
  return o << stringColour[colour];
}

ostream &operator<<(ostream& o, PieceType type){
  const string stringType[] = { "King", "Queen", "Rook",
                                "Knight", "Bishop", "Pawn" };
  return o << stringType[type];
}

