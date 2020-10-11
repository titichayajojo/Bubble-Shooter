//
//  GameVariable.hpp
//  Project
//
//  Created by JoJo on 14/4/2563 BE.
//

#ifndef GameVariable_hpp
#define GameVariable_hpp


#include <vector>
#include <stdio.h>
using namespace std;
using namespace cocos2d;

//class to store variable
class GameVariable{
public:
    
    //function add score
    void AddScore(int newScore);
    
    //function get score
    int GetScore();
    
    //score variable
    static int score;
    
private:
    
};


#endif /* GameVariable_hpp */
