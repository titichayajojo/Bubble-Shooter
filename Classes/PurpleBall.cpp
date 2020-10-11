//
//  PurpleBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "PurpleBall.hpp"

//function create sprite
Sprite* PurpleBall::create(){
    
    //create sprite
    Sprite* PuB = Sprite::create(PURPLE_BALL_FILEPATH);
    
    //create physics body
    auto purplebody = PhysicsBody::createCircle(PuB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    PuB->setPhysicsBody(purplebody);
    
    //allow object to colide with other objects
    purplebody->setContactTestBitmask(true);
    
    //set collision bitmask to purple
    purplebody->setCollisionBitmask(PURPLE);
    return PuB;
}
