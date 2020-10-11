//
//  Scene.hpp
//  Project
//
//  Created by JoJo on 15/4/2563 BE.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "backGround.h"
#include "DEFINITIONS.hpp"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

//class for menu scene
class GameScene : public cocos2d::Scene{
    
public:
    
    //function create scene
    static cocos2d::Scene* createScene();
    
    //game loop
    virtual bool init();
    
    //change to other scene
    void ChangeScene(cocos2d::Ref* pSender);
     CREATE_FUNC(GameScene);
};

//class game over scene
class GameOverScene : public cocos2d::Scene{
public:
    
    //create scene
    static cocos2d::Scene* createScene();
    
    //game loop
    virtual bool init();
    
    //change to other scene
    void ChangeScene(cocos2d::Ref* pSender);
     CREATE_FUNC(GameOverScene);
    
private:
    
    //variable to create text
    Label *scoreLable;
    __String *tempScore;
};

class GameWin : public cocos2d::Scene{
    public:
        
        //create scene
        static cocos2d::Scene* createScene();
        
        //game loop
        virtual bool init();
        
        //change to other scene
        void ChangeScene(cocos2d::Ref* pSender);
         CREATE_FUNC(GameWin);
        
    private:
        
        //variable to create text
        Label *scoreLable;
        __String *tempScore;
};
#endif /* Scene_hpp */
