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

bool SHColorNode::init()
{
    if (LayerColor::init()) {
        this->commonInit();
        return true;
    }
    return false;
}

bool SHColorNode::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
    if(LayerColor::initWithColor(color, w, h)) {
        this->commonInit();
        return true;
    }
    return false;
}

bool SHColorNode::initWithColor(const Color4B& color)
{
    if ( LayerColor::initWithColor(color)) {
        this->commonInit();
        return true;
    }
    return false;
}

void SHColorNode::commonInit()
{
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    this->setTouchEnabled(true);
}

bool SHColorNode::onTouchBegan(Touch *touch, Event *unused_event) {
    printf("touch swallowed by SHColorNode \n");
    return true;
}


SHColorNode* SHColorNode::createInvisibleNode() {
    auto node = SHColorNode::create(Color4B(100, 0, 0, 100));
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    node->setPosition(origin);
    
    return node;
}
