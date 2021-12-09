#include <iostream>
#include <string>
#include <cstring>
#include "classes.h"

using namespace std;

void Game::toggleTurn(){
    turn = (turn == Black) ? White : Black;
}

Colour Game::getTurn(){
    return this->turn;
}

void Game::resetTurn(){
    turn = White;
}