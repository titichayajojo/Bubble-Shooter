//
//  PinkBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "PinkBall.hpp"

//function create sprtie
Sprite* PinkBall::create(){
    
    //create sprite
    Sprite* PB = Sprite::create(PINK_BALL_FILEPATH);
    
    //create physics body
    auto pinkbody = PhysicsBody::createCircle(PB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    PB->setPhysicsBody(pinkbody);
    
    //allow object to colide with other objects
    pinkbody->setContactTestBitmask(true);
    
    //set collision bitmask to pink
    pinkbody->setCollisionBitmask(PINK);
    return PB;
}
