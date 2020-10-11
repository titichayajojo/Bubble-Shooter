//
//  OrangeBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "OrangeBall.hpp"

//function create ball sprite
Sprite* OrangeBall::create(){
    
    //create sprite
    Sprite* OB = Sprite::create(ORANGE_BALL_FILEPATH);
    
    //create physics body
    auto orangebody = PhysicsBody::createCircle(OB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    OB->setPhysicsBody(orangebody);
    
    //allow object to colide with other objects
    orangebody->setContactTestBitmask(true);
    
    //set coliisoin bitmask to orange
    orangebody->setCollisionBitmask(ORANGE);
    return OB;
}
