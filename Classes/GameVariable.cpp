//
//  GameVar.cpp
//  Project-mobile
//
//  Created by JoJo on 14/4/2563 BE.
//

#include "GameVariable.hpp"

//set score to 0
int GameVariable::score = 0;

//function add score
void GameVariable::AddScore(int newScore){
    score += newScore;
}

//function get score
int GameVariable::GetScore(){
    return score;
}
