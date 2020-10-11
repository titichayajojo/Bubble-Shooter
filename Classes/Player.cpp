//
//  Player.cpp
//  Project-mobile
//
//  Created by JoJo on 10/4/2563 BE.
//

#include "Player.hpp"
#include <time.h>

int Player::Rand(){
    srand(time(NULL));
    int nRandonNumber = rand()%8;
    num = nRandonNumber;
}

int Player::getRand(){
    return num;
}
