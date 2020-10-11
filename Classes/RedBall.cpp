//
//  RedBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "RedBall.hpp"

//function create ball sprite
Sprite* RedBall::create(){
    
    //create sprite
    Sprite* RB = Sprite::create(RED_BALL_FILEPATH);
    
    //create physics body
    auto redbody = PhysicsBody::createCircle(RB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    RB->setPhysicsBody(redbody);
    
    //allow object to colide with other objects
    redbody->setContactTestBitmask(true);
    
    //set collision bit mask to red
    redbody->setCollisionBitmask(RED);
    return RB;
}


