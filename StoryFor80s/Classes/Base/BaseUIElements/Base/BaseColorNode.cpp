//
//  BaseColorNode.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#include "BaseColorNode.hpp"


BaseColorNode * BaseColorNode::create(const Color4B& color, GLfloat width, GLfloat height)
{
  BaseColorNode * layer = new (std::nothrow) BaseColorNode();
  if( layer && layer->initWithColor(color,width,height))
  {
    layer->autorelease();
    return layer;
  }
  CC_SAFE_DELETE(layer);
  return nullptr;
}

BaseColorNode * BaseColorNode::create(const Color4B& color)
{
  BaseColorNode * layer = new (std::nothrow) BaseColorNode();
  if(layer && layer->initWithColor(color))
  {
    layer->autorelease();
    return layer;
  }
  CC_SAFE_DELETE(layer);
  return nullptr;
}

bool BaseColorNode::init()
{
  if (LayerColor::init()) {
    p_color = Color4B();
    this->commonInit();
    return true;
  }
  return false;
}

bool BaseColorNode::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
  if(LayerColor::initWithColor(color, w, h)) {
    p_color = color;
    this->commonInit();
    return true;
  }
  return false;
}

bool BaseColorNode::initWithColor(const Color4B& color)
{
  if ( LayerColor::initWithColor(color)) {
    p_color = color;
    this->commonInit();
    return true;
  }
  return false;
}

void BaseColorNode::commonInit()
{
  auto listener = EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);
  listener->onTouchBegan = [this](Touch *touch, Event *unused_event) {
    Director *pDirector = Director::getInstance();
    Point touchPoint = pDirector->convertToGL(touch->getLocationInView());
    auto flag = this->getBoundingBox().containsPoint(touchPoint);
    if (flag) {
      CCLOG("Touch is swallowed by current view SHColorNode : %s", this->getName().c_str());
    }
    return flag;
  };
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
