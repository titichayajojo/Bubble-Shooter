//
//  RedBall.hpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#ifndef RedBall_hpp
#define RedBall_hpp

#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include "Ball.hpp"
#include "DEFINITIONS.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

//class for red ball
class RedBall: public Ball{
public:
    
    //function create sprite
    Sprite* create() override;
    
private:

};

#endif /* RedBall_hpp */
