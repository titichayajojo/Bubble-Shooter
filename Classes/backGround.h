#pragma once

#include "cocos2d.h"
#include <vector>
#include "Ball.hpp"
#include "GameVariable.hpp"
using namespace cocos2d;

class GraphicsScene : public cocos2d::Layer
{
public:
    //function create scene
    static cocos2d::Scene* createScene();
    
    //function game loop
    virtual bool init();
    CREATE_FUNC(GraphicsScene);
    
    //function shoot ball
    bool onTouchBegan(Touch *touch, Event *unused_event);
    
    //function generate balls
    void GenerateBalls(int Row , int Col);
    
    //function create game over line
    void Redline();
    
    //function create player
    void Player();
    
    //function draw sprite player's ball for the 1st loop
    void DrawPlayerBallFirstLoop();
    
    //functino draw sprite player's ball after the 1st loop and delete the previous ball
    void DrawPlayerBallAfterFirstLoop();
    
    //function draw text on screen
    void DrawText(Size visibleSize);
    
    //function create mouse event
    void EventListener();
    
    //function create collision event
    void ContactListener();
    
    //function preload sound effect
    void PreLoadEffect();
    
    //global variable
    int RAND;
    GameVariable Game;



    
private:
    //variable for sprite player
    Sprite* _player;
    
    //variable for game over line
    Sprite* _line;
    
    //variable for physics world
    PhysicsWorld *sceneWorld;
    
    //variable for score lable
    Label *scoreLable;
    
    //variable for score
    __String *tempScore;
    
    //function set physics world
    void SetPhysicsWorld(PhysicsWorld *world){sceneWorld = world;}
    
    //functino detect collision
    bool onContactBegin(PhysicsContact &contact);
    
    vector<Sprite*> sprites;
    vector<int> colors;
    
    vector<Sprite*> curBall;
    int curColor;

};
