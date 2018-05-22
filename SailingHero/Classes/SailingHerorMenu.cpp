//
//  SailingHerorMenu.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SailingHerorMenu.hpp"

#include "SimpleAudioEngine.h"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"

#include "SHColorNode.hpp"

USING_NS_CC;
using namespace ui;

Scene* SailingHeroMenu::createScene()
{
    return SailingHeroMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SailingHeroMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SailingHeroMenu::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
//        float x = - closeItem->getContentSize().width/2;
//        float y = closeItem->getContentSize().height/2;
        closeItem->setAnchorPoint(Vec2(1, 0));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
    this->addChild(menu, 1);

    auto str = LocalizationHelper::getLocalization("start_game");
    auto button = SystemButton::defaultButtonWithText(str);
    button->setPositionType(Widget::PositionType::PERCENT);
    button->setPositionPercent(Vec2(0.5, 0.5));
    button->addClickEventListener(CC_CALLBACK_1(SailingHeroMenu::buttonClickCallback, this));
    this->addChild(button);

    auto node = SHColorNode::create(Color4B(255, 255, 0, 100));
    node->setTouchesEnabled(true);
    node->setContentSize(visibleSize);
    node->setPosition(origin);
    this->addChild(node);
    
    
//    auto s_touchListener = EventListenerTouchOneByOne::create();
//    s_touchListener->onTouchBegan = CC_CALLBACK_2(SHColorNode::onTouchBegan, node);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(s_touchListener, node);
    
    return true;
}

void SailingHeroMenu::buttonClickCallback(Ref* pSender)
{
    printf("click button ");
}

void SailingHeroMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
