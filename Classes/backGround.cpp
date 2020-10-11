#include "backGround.h"
#include "RedBall.hpp"
#include "GreenBall.hpp"
#include "OrangeBall.hpp"
#include "PinkBall.hpp"
#include "PurpleBall.hpp"
#include "DarkBlueBall.hpp"
#include "LightBlueBall.hpp"
#include "YellowBall.hpp"
#include "Ball.hpp"
#include "GameVariable.hpp"
#include <vector>
#include <time.h>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "GameScene.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;


//Create scene function
Scene* GraphicsScene::createScene()
{
    //Create scene
    auto scene = Scene::createWithPhysics();
    
    //Use to see hitbox
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    //Set gravity to be 0
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    
    //create layer
    auto layer = GraphicsScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    
    return scene;
}

//Game loop
bool GraphicsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Create game window
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();
    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, Color4F(0.6,0.6,0.8,1.0));
    this->addChild(background);
    
    //Create game window
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x , visibleSize.height/2+origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    //Call function generate balls on screen
    //Parameter (row,column)
    GenerateBalls(ROW,COLUMN);
    
    //Call function create red line (Game over line)
    Redline();
    
    //Call function create player
    Player();
    
    //Call function draw sprite of player's ball for the 1st loop
    DrawPlayerBallFirstLoop();
    
    
    // click event
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [=](EventMouse *event) {
        //Left mouse event
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            //Remove the previuos sprite of player ball
            for(int i = 93 ; i <= 100 ; i++){
                removeChildByTag(i);
            }
            //Draw sprite player's ball after the 1st loop
            DrawPlayerBallAfterFirstLoop();
        }
    };
    
    //Add nouse event
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener,this);
    
    //Call function to create mouse event ( Shoot )
    EventListener();
    
    //Call function to create collision event
    ContactListener();
    
    //Call function display text on the screen
    DrawText(visibleSize);
    
    //Preload sound effect
    PreLoadEffect();
    return true;
}

//Create mouse event for function onTouchBegan ( Shoot )
void GraphicsScene::EventListener(){
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(GraphicsScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);
}

//Create Collisoion event for function onContactBegin (Collision)
void GraphicsScene::ContactListener(){
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GraphicsScene::onContactBegin,this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

//Create function to preload sound effect
void GraphicsScene::PreLoadEffect(){
    //Shoot sound effect
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SHOOT_EFFECT_FILEPATH);
    
    //Explosion sound effect
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EXPLOSION_EFFECT_FILEPATH);
}

//Shoot function
bool GraphicsScene::onTouchBegan(Touch *touch, Event *unused_event) {
    
    //Get touch location
    Vec2 touchLocation = touch->getLocation();
    
    //Offset for shoot
    Vec2 offset = touchLocation - _player->getPosition();
    
    //Set player ball to red at first
    //Call class red ball
    RedBall RB;
    
    //Cal function create red ball
    auto projectile = RB.create();
    
    //Create physics body for player ball
    auto projectBBody = PhysicsBody::createCircle(projectile->getContentSize().width/2,PhysicsMaterial(0,1,0));
    
    //Generate player ball
    if(RAND == RED){
        RedBall *RB = new RedBall;
        projectile = RB->create();
        projectBBody->setCollisionBitmask(PLAYER_RED);
        curColor = RED;
    }
    else if(RAND == ORANGE){
        OrangeBall *OB = new OrangeBall;
        projectile = OB->create();
        projectBBody->setCollisionBitmask(PLAYER_ORANGE);
        curColor = ORANGE;
    }
    else if(RAND == GREEN){
        GreenBall *GB = new GreenBall;
        projectile = GB->create();
        projectBBody->setCollisionBitmask(PLAYER_GREEN);
        curColor = GREEN;
    }
    else if(RAND == PINK){
        PinkBall *PB = new PinkBall;
        projectile = PB->create();
        projectBBody->setCollisionBitmask(PLAYER_PINK);
        curColor = PINK;
    }
    else if(RAND == PURPLE){
        PurpleBall *PuB = new PurpleBall;
        projectile = PuB->create();
        projectBBody->setCollisionBitmask(PLAYER_PURPLE);
        curColor = PURPLE;
    }
    else if(RAND == DARK_BLUE){
        DarkBlueBall *DB = new DarkBlueBall;
        projectile = DB->create();
        projectBBody->setCollisionBitmask(PLAYER_DARK_BLUE);
        curColor = DARK_BLUE;
    }
    else if(RAND == LIGHT_BLUE){
        LightBlueBall *LB = new LightBlueBall;
        projectile = LB->create();
        projectBBody->setCollisionBitmask(PLAYER_LIGHT_BLUE);
        curColor = LIGHT_BLUE;
    }
    else if(RAND == YELLOW){
        YellowBall *YB = new YellowBall;
        projectile = YB->create();
        projectBBody->setCollisionBitmask(PLAYER_YELLOW);
        curColor = YELLOW;
        
    }
    
    //clear vector before push back current ball
    curBall.clear();
    curBall.push_back(projectile);
    
    //allow object to colide with other object
    projectBBody->setContactTestBitmask(true);
    
    //set position
    projectile->setPosition(_player->getPosition());
    
    //set physics body
    projectile->setPhysicsBody(projectBBody);
    
    //add ball to screen
    this->addChild(projectile,0);
    
    offset.normalize();
    auto shootAmount = offset * 1000;
    
    auto realDest = shootAmount + projectile->getPosition();
    
    //Shoot action
    auto actionMove = MoveTo::create(2.0f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove,actionRemove, nullptr));
    return true;
}


//function detect collision
bool GraphicsScene::onContactBegin(PhysicsContact &contact){
    
    //get physics body of 2 objects that are collided
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    
    //check if balls on screen colide with the game over line
    for(int i = RED ; i <= PLAYER_YELLOW ; i ++){
        if(( i == a->getCollisionBitmask() && -1 == b->getCollisionBitmask() ) ||
           ( -1 == a->getCollisionBitmask() && i == b->getCollisionBitmask() )){
            CCLOG("GAME OVER");
            auto scene = GameOverScene::createScene();
            Director::getInstance()->pushScene(scene);
        }
            }
    
    //Check collision of each color and remove the ball and gain scores
    if ( ( YELLOW == a->getCollisionBitmask() && PLAYER_YELLOW == b->getCollisionBitmask() ) ||
        ( PLAYER_YELLOW == a->getCollisionBitmask() && YELLOW == b->getCollisionBitmask() ) ||
        ( PLAYER_YELLOW == a->getCollisionBitmask() && PLAYER_YELLOW == b->getCollisionBitmask() ) ||
        ( PLAYER_YELLOW == a->getCollisionBitmask() && PLAYER_YELLOW == b->getCollisionBitmask() ))
    {
        //check first collision
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) && colors[i] == YELLOW){
                    colors[i] = COLIDED;
                }
            }
        }
        
        //remove player ball
        curBall[0]->removeFromParent();
        
        //check for others collision
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == YELLOW){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox()) ){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }
        
        //remove colided balls 
        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        //gain scores
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    
    else if ( ( LIGHT_BLUE == a->getCollisionBitmask() && PLAYER_LIGHT_BLUE == b->getCollisionBitmask() ) ||
             ( PLAYER_LIGHT_BLUE == a->getCollisionBitmask() && LIGHT_BLUE == b->getCollisionBitmask() ) ||
             ( PLAYER_LIGHT_BLUE == a->getCollisionBitmask() && PLAYER_LIGHT_BLUE == b->getCollisionBitmask() ) ||
             ( PLAYER_LIGHT_BLUE == a->getCollisionBitmask() && PLAYER_LIGHT_BLUE == b->getCollisionBitmask() ))
    {
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) && colors[i] == LIGHT_BLUE){
                    colors[i] = COLIDED;
                }
            }
        }
        
        curBall[0]->removeFromParent();
        
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == LIGHT_BLUE){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox()) ){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }
        
        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    
    else if ( ( DARK_BLUE == a->getCollisionBitmask() && PLAYER_DARK_BLUE == b->getCollisionBitmask() ) ||
             ( PLAYER_DARK_BLUE == a->getCollisionBitmask() && DARK_BLUE == b->getCollisionBitmask() ) ||
             ( PLAYER_DARK_BLUE == a->getCollisionBitmask() && PLAYER_DARK_BLUE == b->getCollisionBitmask() ) ||
             ( PLAYER_DARK_BLUE == a->getCollisionBitmask() && PLAYER_DARK_BLUE == b->getCollisionBitmask() ))
    {
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) && colors[i] == DARK_BLUE){
                    colors[i] = COLIDED;
                }
            }
        }
        
        curBall[0]->removeFromParent();
        
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == DARK_BLUE){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox()) ){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }
        
        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    else if ( ( PURPLE == a->getCollisionBitmask() && PLAYER_PURPLE == b->getCollisionBitmask() ) ||
             ( PLAYER_PURPLE == a->getCollisionBitmask() && PURPLE == b->getCollisionBitmask() ) ||
             ( PLAYER_PURPLE == a->getCollisionBitmask() && PLAYER_PURPLE == b->getCollisionBitmask() ) ||
             ( PLAYER_PURPLE == a->getCollisionBitmask() && PLAYER_PURPLE == b->getCollisionBitmask() ))
    {
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) && colors[i] == PURPLE){
                    colors[i] = COLIDED;
                }
            }
        }
        
        curBall[0]->removeFromParent();
        
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == PURPLE){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox())){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }
        
        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);

        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    else if ( ( PINK == a->getCollisionBitmask() && PLAYER_PINK == b->getCollisionBitmask() ) ||
             ( PLAYER_PINK == a->getCollisionBitmask() && PINK== b->getCollisionBitmask() ) ||
             ( PLAYER_PINK == a->getCollisionBitmask() && PLAYER_PINK == b->getCollisionBitmask() ) ||
             ( PLAYER_PINK == a->getCollisionBitmask() && PLAYER_PINK == b->getCollisionBitmask() ))
    {
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) && colors[i] == PINK){
                    colors[i] = COLIDED;
                }
            }
        }
        
        curBall[0]->removeFromParent();
        
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == PINK){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox()) ){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }
        
        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    else if ( ( GREEN == a->getCollisionBitmask() && PLAYER_GREEN == b->getCollisionBitmask() ) ||
             ( PLAYER_GREEN == a->getCollisionBitmask() && GREEN == b->getCollisionBitmask() ) ||
             ( PLAYER_GREEN == a->getCollisionBitmask() && PLAYER_GREEN == b->getCollisionBitmask() ) ||
             ( PLAYER_GREEN == a->getCollisionBitmask() && PLAYER_GREEN == b->getCollisionBitmask() ))
    {
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) && colors[i] == GREEN){
                    colors[i] = COLIDED;
                }
            }
        }
        
        curBall[0]->removeFromParent();
        
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == GREEN){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox()) ){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }
        
        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    else if ( ( ORANGE == a->getCollisionBitmask() && PLAYER_ORANGE == b->getCollisionBitmask() ) ||
             ( PLAYER_ORANGE == a->getCollisionBitmask() && ORANGE == b->getCollisionBitmask() ) ||
             ( PLAYER_ORANGE == a->getCollisionBitmask() && PLAYER_ORANGE == b->getCollisionBitmask() ) ||
             ( PLAYER_ORANGE == a->getCollisionBitmask() && PLAYER_ORANGE == b->getCollisionBitmask() ))
    {
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) && colors[i] == ORANGE){
                    colors[i] = COLIDED;
                }
            }
        }
        
        curBall[0]->removeFromParent();
        
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == ORANGE){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox()) ){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }
        
        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    
    
    //check red collision
    else if ( ( RED == a->getCollisionBitmask() && PLAYER_RED == b->getCollisionBitmask() ) ||
             ( PLAYER_RED == a->getCollisionBitmask() && RED == b->getCollisionBitmask() ) ||
             ( PLAYER_RED == a->getCollisionBitmask() && PLAYER_RED == b->getCollisionBitmask() ) ||
             ( PLAYER_RED == a->getCollisionBitmask() && PLAYER_RED == b->getCollisionBitmask() ))
    {
        for(int i = 0 ; i < sprites.size() ; i++){
            if(colors[i] != DELETED && colors[i] == RED){
                if(curBall[0]->getBoundingBox().intersectsRect(sprites[i]->getBoundingBox()) ){
                    colors[i] = COLIDED;
                    
                }
            }
        }
        
        //remove player's ball
        curBall[0]->removeFromParent();
        
        int count = 0 ;
        while(count != -1){
            count = 0;
            for(int i = 0 ; i < sprites.size() ; i ++){
                for(int j = 0 ; j < sprites.size() ; j ++){
                    if(colors[i] == COLIDED && colors[j] == RED){
                        if(sprites[i]->getBoundingBox().intersectsRect(sprites[j]->getBoundingBox()) ){
                            colors[j] = COLIDED;
                            count++;
                        }
                    }
                }
            }
            if(count == 0){
                count = -1;
            }
        }

        int noOfBall = 0;
        for(int i = 0 ; i < colors.size() ; i ++){
            if(colors[i] == COLIDED){
                sprites[i]->removeFromParent();
                colors[i] = DELETED;
                noOfBall++;
            }
        }
        
        for(int i = 0 ; i < noOfBall ; i++)
            Game.AddScore(SCORE);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_EFFECT_FILEPATH);
    }
    
    //if balls are not the same color
    else{
        bool push = false;
        //PlayerBall
        for(int i = PLAYER_RED ; i <= PLAYER_YELLOW ; i++ ){
            //Ball on screen
            for(int j = RED ; j <= PLAYER_YELLOW ; j ++){
                if ( ( i == a->getCollisionBitmask() && j == b->getCollisionBitmask() ) ||
                    ( j == a->getCollisionBitmask() && i == b->getCollisionBitmask() )){
                    auto nodeA = contact.getShapeA()->getBody()->getNode();
                    nodeA->pause();
                    
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SHOOT_EFFECT_FILEPATH);
                    
                    sprites.push_back(curBall[0]);
                    colors.push_back(curColor);
                    
                    push = true;
                    break;
                    
                }
            }
            if(push == true)
                break;
        }
    }
    
    //update scores on screen
     __String *tempScore = __String::createWithFormat("%i" , Game.GetScore());
    scoreLable->setString(tempScore->getCString());
    
    int remainingBalls = 0;
    for(int i = 0 ; i < sprites.size() ; i ++){
        if(colors[i] != -2)
            remainingBalls++;
    }
    
    if(remainingBalls == 0){
        auto scene = GameWin::createScene();
        Director::getInstance()->pushScene(scene);
    }
    
    return true;
}

//Generate ball on screen
void GraphicsScene::GenerateBalls(int Row, int Col){
    int xpos = 40 , ypos = 310;
    
    srand(time(NULL));
    sprites.clear();
    colors.clear();
    
    //Use to generate balls
    for(int i = 0 ; i < Row ; i ++){
        if(i%2 == 0){
            xpos = 70;
            Col = 11;
        }
        else{
            xpos = 40;
            Col = 12;
        }
        for(int j = 0 ; j < Col ; j ++){
            
            int Rand = rand()%8;
            
            //Check win
//            int Rand = 0;
            
            if(Rand == 0){
                RedBall* RedB = new RedBall;
                auto rb = RedB->create();
                rb->setPosition(xpos,ypos);
                this->addChild(rb,0);
                sprites.push_back(rb);
                colors.push_back(RED);
            }
            else if(Rand == 1){
                OrangeBall* OrangeB = new OrangeBall;
                auto ob = OrangeB->create();
                ob->setPosition(xpos,ypos);
                this->addChild(ob,0);
                sprites.push_back(ob);
                colors.push_back(ORANGE);
            }
            else if(Rand == 2){
                GreenBall* GreenB = new GreenBall;
                auto gb = GreenB->create();
                gb->setPosition(xpos,ypos);
                this->addChild(gb,0);
                sprites.push_back(gb);
                colors.push_back(GREEN);
            }
            else if(Rand == 3){
                PinkBall* PinkB = new PinkBall;
                auto pb = PinkB->create();
                pb->setPosition(xpos,ypos);
                this->addChild(pb,0);
                sprites.push_back(pb);
                colors.push_back(PINK);
            }
            else if(Rand == 4){
                PurpleBall* PurpleB = new PurpleBall;
                auto pub = PurpleB->create();
                pub->setPosition(xpos,ypos);
                this->addChild(pub,0);
                sprites.push_back(pub);
                colors.push_back(PURPLE);
            }
            else if(Rand == 5){
                DarkBlueBall* DarkB = new DarkBlueBall;
                auto db = DarkB->create();
                db->setPosition(xpos,ypos);
                this->addChild(db,0);
                sprites.push_back(db);
                colors.push_back(DARK_BLUE);
            }
            else if(Rand == 6){
                LightBlueBall* LightB = new LightBlueBall;
                auto lb = LightB->create();
                lb->setPosition(xpos,ypos);
                this->addChild(lb,0);
                sprites.push_back(lb);
                colors.push_back(LIGHT_BLUE);
            }
            else if(Rand == 7){
                YellowBall* YellowB = new YellowBall;
                auto yb = YellowB->create();
                yb->setPosition(xpos,ypos);
                this->addChild(yb,0);
                sprites.push_back(yb);
                colors.push_back(YELLOW);
            }
            
            xpos+=50;
        }
        ypos+=45;
    }
    

}

//function to create game over line on screen
void GraphicsScene::Redline(){
    
    _line = Sprite::create(RED_LINE_FILEPATH);
    _line->setAnchorPoint(Vec2(0,0));
    _line->setPosition(30,0);
    auto _linebody = PhysicsBody::createBox(_line->getContentSize(),PhysicsMaterial(0,1,0));
    _line->setPhysicsBody(_linebody);
    _linebody->setContactTestBitmask(true);
    _linebody->setCollisionBitmask(-1);
    _linebody->setDynamic(false);
    this->addChild(_line);
}

//function to create player on screen
void GraphicsScene::Player(){
    _player = Sprite::create(PLAYER_FILEPATH);
    _player->setAnchorPoint(Vec2(0, 0));
    _player->setPosition(250, 50);
    this->addChild(_player);
}

//function to create sprtie of player ball for the fisrt loop
void GraphicsScene::DrawPlayerBallFirstLoop(){
    RAND = rand()%8;
    if(RAND == RED){
        RedBall RB;
        auto RedB = RB.create();
        RedB->setAnchorPoint(Vec2(0, 0));
        RedB->setPosition(_player->getPosition());
        RedB->setTag(93);
        this->addChild(RedB, 0);
    }
    else if(RAND == ORANGE){
        OrangeBall OB;
        auto OrangeB = OB.create();
        OrangeB->setAnchorPoint(Vec2(0, 0));
        OrangeB->setPosition(_player->getPosition());
        OrangeB->setTag(94);
        this->addChild(OrangeB, 0);
    }
    else if(RAND == GREEN){
        GreenBall GB;
        auto GreenB = GB.create();
        GreenB->setAnchorPoint(Vec2(0, 0));
        GreenB->setPosition(_player->getPosition());
        GreenB->setTag(95);
        this->addChild(GreenB, 0);
    }
    else if(RAND == PINK){
        PinkBall PB;
        auto PinkB = PB.create();
        PinkB->setAnchorPoint(Vec2(0, 0));
        PinkB->setPosition(_player->getPosition());
        PinkB->setTag(96);
        this->addChild(PinkB, 0);
    }
    else if(RAND == PURPLE){
        PurpleBall PuB;
        auto PurpleB = PuB.create();
        PurpleB->setAnchorPoint(Vec2(0, 0));
        PurpleB->setPosition(_player->getPosition());
        PurpleB->setTag(97);
        this->addChild(PurpleB, 0);
    }
    else if(RAND == DARK_BLUE){
        DarkBlueBall DB;
        auto DarkB = DB.create();
        DarkB->setAnchorPoint(Vec2(0, 0));
        DarkB->setPosition(_player->getPosition());
        DarkB->setTag(98);
        this->addChild(DarkB, 0);
    }
    else if(RAND == LIGHT_BLUE){
        LightBlueBall LB;
        auto LightB = LB.create();
        LightB->setAnchorPoint(Vec2(0, 0));
        LightB->setPosition(_player->getPosition());
        LightB->setTag(99);
        this->addChild(LightB, 0);
    }
    else if(RAND == YELLOW){
        YellowBall YB;
        auto YellowB = YB.create();
        YellowB->setAnchorPoint(Vec2(0, 0));
        YellowB->setPosition(_player->getPosition());
        YellowB->setTag(100);
        this->addChild(YellowB, 0);
    }
}

//function to create sprite of player ball after the first loop and remove the previos sprite on screen
void GraphicsScene::DrawPlayerBallAfterFirstLoop(){
    RAND = rand()%8;
    if(RAND == RED){
        RedBall RB;
        auto RedB = RB.create();
        Sprite *PclonedRed = Sprite::createWithTexture(RedB->getTexture());
        PclonedRed->setScale(RedB->getScaleX(), RedB->getScaleY());
        PclonedRed->setRotation(RedB->getRotation());
        PclonedRed->setAnchorPoint(Vec2(0, 0));
        PclonedRed->setPosition(_player->getPosition());
        PclonedRed->setTag(0);
        this->addChild(PclonedRed, 0);
    }
    else if(RAND == ORANGE){
        OrangeBall OB;
        auto OrangeB = OB.create();
        Sprite *PclonedOrange = Sprite::createWithTexture(OrangeB->getTexture());
        PclonedOrange->setScale(OrangeB->getScaleX(), OrangeB->getScaleY());
        PclonedOrange->setRotation(OrangeB->getRotation());
        PclonedOrange->setAnchorPoint(Vec2(0, 0));
        PclonedOrange->setPosition(_player->getPosition());
        PclonedOrange->setTag(1);
        this->addChild(PclonedOrange, 0);
    }
    else if(RAND == GREEN){
        GreenBall GB;
        auto GreenB = GB.create();
        Sprite *PclonedGreen = Sprite::createWithTexture(GreenB->getTexture());
        PclonedGreen->setScale(GreenB->getScaleX(), GreenB->getScaleY());
        PclonedGreen->setRotation(GreenB->getRotation());
        PclonedGreen->setAnchorPoint(Vec2(0, 0));
        PclonedGreen->setPosition(_player->getPosition());
        PclonedGreen->setTag(2);
        this->addChild(PclonedGreen, 0);
    }
    else if(RAND == PINK){
        PinkBall PB;
        auto PinkB = PB.create();
        Sprite *PclonedPink = Sprite::createWithTexture(PinkB->getTexture());
        PclonedPink->setScale(PinkB->getScaleX(), PinkB->getScaleY());
        PclonedPink->setRotation(PinkB->getRotation());
        PclonedPink->setAnchorPoint(Vec2(0, 0));
        PclonedPink->setPosition(_player->getPosition());
        PclonedPink->setTag(3);
        this->addChild(PclonedPink, 0);
    }
    else if(RAND == PURPLE){
        PurpleBall PuB;
        auto PurpleB = PuB.create();
        Sprite *PclonedPurple = Sprite::createWithTexture(PurpleB->getTexture());
        PclonedPurple->setScale(PurpleB->getScaleX(), PurpleB->getScaleY());
        PclonedPurple->setRotation(PurpleB->getRotation());
        PclonedPurple->setAnchorPoint(Vec2(0, 0));
        PclonedPurple->setPosition(_player->getPosition());
        PclonedPurple->setTag(4);
        this->addChild(PclonedPurple, 0);
    }
    else if(RAND == DARK_BLUE){
        DarkBlueBall DB;
        auto DarkB = DB.create();
        Sprite *PclonedDB = Sprite::createWithTexture(DarkB->getTexture());
        PclonedDB->setScale(DarkB->getScaleX(), DarkB->getScaleY());
        PclonedDB->setRotation(DarkB->getRotation());
        PclonedDB->setAnchorPoint(Vec2(0, 0));
        PclonedDB->setPosition(_player->getPosition());
        PclonedDB->setTag(5);
        this->addChild(PclonedDB, 0);
    }
    else if(RAND == LIGHT_BLUE){
        LightBlueBall LB;
        auto LightB = LB.create();
        Sprite *PclonedLB = Sprite::createWithTexture(LightB->getTexture());
        PclonedLB->setScale(LightB->getScaleX(), LightB->getScaleY());
        PclonedLB->setRotation(LightB->getRotation());
        PclonedLB->setAnchorPoint(Vec2(0, 0));
        PclonedLB->setPosition(_player->getPosition());
        PclonedLB->setTag(5);
        this->addChild(PclonedLB, 0);
    }
    else if(RAND == YELLOW){
        YellowBall YB;
        auto YellowB = YB.create();
        Sprite *PclonedYellow = Sprite::createWithTexture(YellowB->getTexture());
        PclonedYellow->setScale(YellowB->getScaleX(), YellowB->getScaleY());
        PclonedYellow->setRotation(YellowB->getRotation());
        PclonedYellow->setAnchorPoint(Vec2(0, 0));
        PclonedYellow->setPosition(_player->getPosition());
        PclonedYellow->setTag(7);
        this->addChild(PclonedYellow, 0);
        
    }
}

//function to draw text on screen
void GraphicsScene::DrawText(Size visibleSize){
    //Create text to display score
    __String *tempScore = __String::createWithFormat("%i" , Game.GetScore());
    scoreLable = Label::createWithTTF(tempScore->getCString(),TEXT_FILEPATH, visibleSize.height*0.1);
    
    //Set text color to white
    scoreLable->setColor(Color3B::WHITE);
    
    //Set position of text
    scoreLable->setPosition(500,80);
    
    //Add text on screen
    this->addChild(scoreLable,10000);
}
