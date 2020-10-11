//
//  DarkBlueBall.cpp
//  Project
//
//  Created by JoJo on 9/4/2563 BE.
//

#include "DarkBlueBall.hpp"

//function create sprite
Sprite* DarkBlueBall::create(){
    
    //create sprite
    Sprite* DB = Sprite::create(DARK_BLUE_BALL_FILEPATH);
    
    //create physics body
    auto darkbody = PhysicsBody::createCircle(DB->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //set physics body
    DB->setPhysicsBody(darkbody);
    
    //allow object to colide with other objects
    darkbody->setContactTestBitmask(true);
    
    //set collision bitmask to darkblue
    darkbody->setCollisionBitmask(DARK_BLUE);
    return DB;
}
