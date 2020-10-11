//
//  OrangeBall.hpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#ifndef OrangeBall_hpp
#define OrangeBall_hpp

#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include "Ball.hpp"
#include "DEFINITIONS.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

//class for orange ball
class OrangeBall: public Ball{
public:
    //function to create sprite
    Sprite* create() override;

private:

};
#endif /* OrangeBall_hpp */
