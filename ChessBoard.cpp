#include <iostream>
#include <string>
#include <cstring>
#include "classes.h"

using namespace std;


// constructor which resets (or just sets in this case) a board
ChessBoard::ChessBoard()
{
  resetBoard();
}

void ChessBoard::resetBoard(){

  game.resetTurn();
  // reset white starting positions
  // starting with pawns
  for(int i = 0; i < MAX_RANK; i++){
    square[6][i] = &whitePawn[i];
  }
  // and others
  square[7][0] = &whiteRook[0];
  square[7][1] = &whiteKnight[0];
  square[7][2] = &whiteBishop[0];
  square[7][3] = &whiteQueen;
  square[7][4] = &whiteKing;
  square[7][5] = &whiteBishop[1];
  square[7][6] = &whiteKnight[1];
  square[7][7] = &whiteRook[1];

  // reset black starting pieces
  // starting with pawns
  for(int i = 0; i < MAX_RANK; i++){
    square[1][i] = &blackPawn[i];
  }

  // and others
  square[0][0] = &blackRook[0];
  square[0][1] = &blackKnight[0];
  square[0][2] = &blackBishop[0];
  square[0][3] = &blackQueen;
  square[0][4] = &blackKing;
  square[0][5] = &blackBishop[1];
  square[0][6] = &blackKnight[1];
  square[0][7] = &blackRook[1];

  // set them all to black
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < MAX_FILE; j++){
      square[i][j]->setBlack();
    }
  }
  // all middle squares
  for(int i = 2; i < 6; i++){
    for(int j = 0; j < MAX_RANK; j++){
      square[i][j] = nullptr;
    }
  }

  cout << "A new chess game is started!" << endl;
}


bool ChessBoard::hasPiece(int rank, int file){
  if(square[rank][file] != nullptr){
    return true;
  }
  else return false;
}

void ChessBoard::makeMove(int sR, int sF, int dR, int dF){
  string outputSource = convertBack(sR, sF);
  string outputDest = convertBack(dR, dF);
  cout << square[sR][sF]->getColour() << "'s " << square[sR][sF]->getType()
       << " moves from " << outputSource[0] << outputSource[1] << " to "
       << outputDest[0] << outputDest[1];
  if(square[dR][dF] != nullptr){
    cout << " taking " << square[dR][dF]->getColour() << "'s "
         << square[dR][dF]->getType() << endl;
  }
  else cout << endl;
  square[dR][dF] = square[sR][sF];
  square[sR][sF] = nullptr;
  


}


void ChessBoard::submitMove(const char* source, const char* dest){
  int sourceRank, sourceFile, destRank, destFile;

  // converts coordinates from chess notation into array indices
  converter(source, sourceRank, sourceFile);
  converter(dest, destRank, destFile);

  // check for if there is a piece on that square
  if(!hasPiece(sourceRank, sourceFile)){
    cerr << "There is no piece at position " << source[0] << source[1] << endl;
    return;
  }

  // check if it is the correct colour's turn
  if(! (square[sourceRank][sourceFile]->getColour() == game.getTurn())){
    cerr << "It is not " << square[sourceRank][sourceFile]->getColour()
         << "'s turn to move. " << endl;
         return;
  }

  // check for whether that move is legal for that piece
  if( ! (square[sourceRank][sourceFile]->isValidMove(square, sourceRank, 
            sourceFile, destRank, destFile))){
      return;
  }
 
  makeMove(sourceRank, sourceFile, destRank, destFile);
  game.toggleTurn();

}

  // check that that move does not render the mover in check
  // if it has taken an opposition move, then we delete that piece



