//
//  YellowBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "YellowBall.hpp"

//function create sprite
Sprite* YellowBall::create(){
    //create sprite
    Sprite* YB = Sprite::create(YELLOW_BALL_FILEPATH);
    
    //create physics body
    auto yellowbody = PhysicsBody::createCircle(YB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    YB->setPhysicsBody(yellowbody);
    
    //allow object to colide with other objects
    yellowbody->setContactTestBitmask(true);
    
    //set collision bitmask to yellow
    yellowbody->setCollisionBitmask(YELLOW);
    return YB;
}



