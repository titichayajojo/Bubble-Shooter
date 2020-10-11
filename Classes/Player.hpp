//
//  Player.hpp
//  Project-mobile
//
//  Created by JoJo on 10/4/2563 BE.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "RedBall.hpp"
#include "GreenBall.hpp"
#include "OrangeBall.hpp"
#include "PinkBall.hpp"
#include "PurpleBall.hpp"
#include "DarkBlueBall.hpp"
#include "LightBlueBall.hpp"
#include "YellowBall.hpp"

class Player{
public:
    int Rand();
    int getRand();
private:
    int num = 0;
};
#endif /* Player_hpp */
