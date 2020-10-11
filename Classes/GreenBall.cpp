//
//  GreenBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "GreenBall.hpp"

//function create sprite
Sprite* GreenBall::create(){
    
    //create sprite
    Sprite* GB = Sprite::create(GREEN_BALL_FILEPATH);
    
    //create physics body
    auto greenbody = PhysicsBody::createCircle(GB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    GB->setPhysicsBody(greenbody);
    
    //allow object to colide with other objects
    greenbody->setContactTestBitmask(true);
    
    //set collsion bitmask to green
    greenbody->setCollisionBitmask(GREEN);
    return GB;
}
