//
//  PinkBall.hpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#ifndef PinkBall_hpp
#define PinkBall_hpp
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include "Ball.hpp"
#include "DEFINITIONS.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

//class for pink ball
class PinkBall: public Ball{
public:
    //function to create sprite 
    Sprite* create() override;

private:
  
};

#endif /* PinkBall_hpp */
