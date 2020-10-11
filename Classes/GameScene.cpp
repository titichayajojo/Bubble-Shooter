//
//  Scene.cpp
//  Project
//
//  Created by JoJo on 15/4/2563 BE.
//

#include "GameScene.hpp"

//create manu scene
cocos2d::Scene* GameScene::createScene()
{
    return GameScene::create();
}

//FUNCTION CALL BACK
void GameScene::ChangeScene(cocos2d::Ref* pSender){
    
    auto scene = GraphicsScene::createScene();
    Director::getInstance()->pushScene(scene);
    
}

//Menu scene loop
bool GameScene::init()
{
    //create background
    auto bg = Sprite::create(MENU_BACKGROUND_FILEPATH);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0,0);
    this->addChild(bg,1);
    
    //create title
    auto title = Sprite::create(MENU_TITLE_FILEPATH);
    title->setAnchorPoint(Vec2(0, 0));
    title->setPosition(30,160);
    this->addChild(title,1);
    
    //create play button and click event
    auto closeItem = cocos2d::MenuItemImage::create(MENU_BUTTON_FILEPATH,CC_CALLBACK_1(GameScene::ChangeScene, this));
    
    auto menu = cocos2d::Menu::create(closeItem, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    menu->setPosition(320,150);
    this->addChild(menu, 1);
    
    //Play background music
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_MUSIC_FILEPATH);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC_FILEPATH,true);
    
    return true;
}


//create game over scene
cocos2d::Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}


//change to other scene
void GameOverScene::ChangeScene(cocos2d::Ref* pSender){
    auto scene = GraphicsScene::createScene();
    Director::getInstance()->pushScene(scene);
}

//Game over scene loop
bool GameOverScene::init()
{
    GameVariable Game;
    
    //create background
    auto bg = Sprite::create(GAMEOVER_BACKGROUND_FILEPATH);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0,0);
    this->addChild(bg,1);
    
    
    //create game over title
    auto title = Sprite::create(GAMEOVER_TITLE_FILEPATH);
    title->setAnchorPoint(Vec2(0, 0));
    title->setPosition(150,250);
    this->addChild(title,1);
    
    //create text to display score
    auto visibleSize = Director::getInstance()->getVisibleSize();
    __String *tempScore = __String::createWithFormat("%i" , Game.GetScore());
    scoreLable = Label::createWithTTF(tempScore->getCString(),TEXT_FILEPATH , visibleSize.height*0.1);
    scoreLable->setColor(Color3B::WHITE);
    scoreLable->setPosition(300,200);
    this->addChild(scoreLable,10000);
    
    auto closeItem = cocos2d::MenuItemImage::create(GAMEOVER_RETRY_BUTTON_FILEPATH,GAMEOVER_RETRY_BUTTON_FILEPATH,CC_CALLBACK_1(GameOverScene::ChangeScene, this));
    
    
    auto menu = cocos2d::Menu::create(closeItem, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    menu->setPosition(300,130);
    this->addChild(menu, 1);
    
    //set score to 0 
    Game.score = 0;
    
    return true;
}


//create win scene
cocos2d::Scene* GameWin::createScene()
{
    return GameWin::create();
}


//change to other scene
void GameWin::ChangeScene(cocos2d::Ref* pSender){
    auto scene = GraphicsScene::createScene();
    Director::getInstance()->pushScene(scene);
}

//Game win scene loop
bool GameWin::init()
{
    GameVariable Game;
    
    //create background
    auto bg = Sprite::create(GAMEOVER_BACKGROUND_FILEPATH);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0,0);
    this->addChild(bg,1);
    
    
    //create win title
    auto title = Sprite::create(WIN_TITLE);
    title->setAnchorPoint(Vec2(0, 0));
    title->setPosition(230,250);
    this->addChild(title,1);
    
    //create text to display score
    auto visibleSize = Director::getInstance()->getVisibleSize();
    __String *tempScore = __String::createWithFormat("%i" , Game.GetScore());
    scoreLable = Label::createWithTTF(tempScore->getCString(),TEXT_FILEPATH , visibleSize.height*0.1);
    scoreLable->setColor(Color3B::WHITE);
    scoreLable->setPosition(300,200);
    this->addChild(scoreLable,10000);
    
    auto closeItem = cocos2d::MenuItemImage::create(GAMEOVER_RETRY_BUTTON_FILEPATH,GAMEOVER_RETRY_BUTTON_FILEPATH,CC_CALLBACK_1(GameWin::ChangeScene, this));
    
    
    auto menu = cocos2d::Menu::create(closeItem, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    menu->setPosition(300,130);
    this->addChild(menu, 1);
    
    //set score to 0
    Game.score = 0;
    
    return true;
}
