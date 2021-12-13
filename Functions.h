#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

int const MAX_FILE = 8;
int const MAX_RANK = 8;
int const ROOKS_PER_COLOUR = 2;
int const KNIGHTS_PER_COLOUR = 2;
int const BISHOPS_PER_COLOUR = 2;
int const PAWNS_PER_COLOUR = 8;

using namespace std;

enum Colour { White, Black };
enum PieceType { king, queen, rook, knight, bishop, pawn };

bool isValidInput(int sR, int sF, int dR, int dF);
void converter(const char* position, int& rank, int& file);
string convertBack(int rank, int file);
ostream &operator<<(ostream& o, Colour colour);
ostream &operator<<(ostream& o, PieceType type);



#endif