//
//  Ball.hpp
//  Project-mobile

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include "DEFINITIONS.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

//class for ball
class Ball{
public:
    //abstract method of create sprite
    virtual Sprite* create(){return NULL;}
    
private:
    

};
    
#endif /* Ball_hpp */
