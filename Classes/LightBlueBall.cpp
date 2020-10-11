//
//  LightBlueBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "LightBlueBall.hpp"

//function create sprite
Sprite* LightBlueBall::create(){
    
    //create sprite
    Sprite* LB = Sprite::create(LIGHT_BLUE_BALL_FILEPATH);
    
    //create physics body
    auto lightbody = PhysicsBody::createCircle(LB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    LB->setPhysicsBody(lightbody);
    
    //allow object to colide with other objects
    lightbody->setContactTestBitmask(true);
    
    //set collision bitmask to light blue
    lightbody->setCollisionBitmask(LIGHT_BLUE);
    return LB;
}
