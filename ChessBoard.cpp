#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Piece.h"
#include "ChessBoard.h"
#include "Functions.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Game.h"

using namespace std;


// constructor which resets (or just sets in this case) a board
ChessBoard::ChessBoard()
{
  resetBoard();
}

// function for resetting the board. Points the pointers back to
// chess starting positions
void ChessBoard::resetBoard(){

  // white always starts a new game so
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
  // all middle squares set to empty (or nullptr)
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


void ChessBoard::printMoveToMake(int sR, int sF, int dR, int dF){
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
}

// destination square pointer now points to where the source square did
// the source square pointer points to nothing, signifying its emptiness
void ChessBoard::makeMove(int sR, int sF, int dR, int dF){
  square[dR][dF] = square[sR][sF];
  square[sR][sF] = nullptr;
}


void ChessBoard::submitMove(const char* source, const char* dest){
  int sourceRank, sourceFile, destRank, destFile;


  // converts coordinates from chess notation into array indices
  converter(source, sourceRank, sourceFile);
  converter(dest, destRank, destFile);

  // guards for valid input and return if error
  if(! (isValidInput(sourceRank, sourceFile, destRank, destFile))){
    cout << "Invalid input error. " << endl;
    return;
  }

  // check for if there is a piece on that square and return if error
  if(!hasPiece(sourceRank, sourceFile)){
    cerr << "There is no piece at position " << source[0] << source[1] << endl;
    return;
  }

  // check if it is the correct colour's turn to move and return if error
  if(! (square[sourceRank][sourceFile]->getColour() == game.getTurn())){
    cerr << "It is not " << square[sourceRank][sourceFile]->getColour()
         << "'s turn to move. " << endl;
         return;
  }

  PieceType flag;
  // check for whether that move is legal for that piece and if not
  // output error statement before returning
  if( ! (square[sourceRank][sourceFile]->isValidMove(square, sourceRank, 
            sourceFile, destRank, destFile, flag))){
      string destOutput = convertBack(destRank, destFile);
      string sourceOutput = convertBack(sourceRank, sourceFile);
      cout << square[sourceRank][sourceFile]->getColour() << "'s ";
      switch(flag){
        case king:
          cout << king; break;
        case queen:
          cout << queen; break;
        case rook:
          cout << rook; break;
        case knight:
          cout << knight; break;
        case bishop:
          cout << bishop; break;
        case pawn:
          cout << pawn; break;
      }
      cout << " at " << sourceOutput[0] << sourceOutput[1] 
      << " cannot move to " << destOutput[0] << destOutput[1] << endl;
      return;
  }

  // Check that move doesn't put self in check
  Piece* temp = nullptr;
  game.makeTempMove(square, temp, sourceRank, sourceFile, destRank, destFile);
  // isInCheck function checks for if moving player is in check
  if(game.isInCheck(square)){
    cout << "Illegal move. Player cannot put self in check." << endl;
    return;
  }
  game.undoTempMove(square, temp, sourceRank, sourceFile, destRank, destFile);

  // after its validity is checked, the move can be made
  printMoveToMake(sourceRank, sourceFile, destRank, destFile);
  makeMove(sourceRank, sourceFile, destRank, destFile);
 
  // after move the turn is over
  game.toggleTurn();

  // and now we check for whether the game is over i.e. whether someone
  // is in checkmate or stalemate. If someone is in check but not checkmate
  // then message is outputted but the game continues
  if(game.isGameOver(square)){
    return;
  }

}
