//
//  PurpleBall.hpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#ifndef PurpleBall_hpp
#define PurpleBall_hpp

#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include "Ball.hpp"
#include "DEFINITIONS.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

//class for purple ball
class PurpleBall: public Ball{
public:
    
    //function create sprite
    Sprite* create() override;
private:

};


#endif /* PurpleBall_hpp */
