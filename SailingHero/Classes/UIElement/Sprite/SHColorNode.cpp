//
//  SHColorNode.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/19/18.
//

#include "SHColorNode.hpp"


SHColorNode* SHColorNode::create()
{
    SHColorNode* ret = new (std::nothrow) SHColorNode();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

SHColorNode * SHColorNode::create(const Color4B& color, GLfloat width, GLfloat height)
{
    SHColorNode * layer = new (std::nothrow) SHColorNode();
    if( layer && layer->initWithColor(color,width,height))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

SHColorNode * SHColorNode::create(const Color4B& color)
{
    SHColorNode * layer = new (std::nothrow) SHColorNode();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}


void SHColorNode::setTouchesEnabled(bool enabled)
{
    printf("=================1\n");
    s_touchListener = EventListenerTouchOneByOne::create();
    s_touchListener->onTouchBegan = CC_CALLBACK_2(SHColorNode::onTouchBegan, this);
    s_touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(s_touchListener, this);
}

bool SHColorNode::onTouchBegan(Touch *touch, Event *unused_event) {
    printf("=================3\n");
    return true;
}
