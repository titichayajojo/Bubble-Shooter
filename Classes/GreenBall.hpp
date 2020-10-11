//
//  GreenBall.hpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#ifndef GreenBall_hpp
#define GreenBall_hpp
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include "Ball.hpp"
#include "DEFINITIONS.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

//class for green ball
class GreenBall: public Ball{
public:
    //function to create sprite
    Sprite* create() override;

private:

};
#endif /* GreenBall_hpp */
