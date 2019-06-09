//
//  BaseSpriteListener.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "BaseSpriteListener.hpp"

bool BaseSpriteListener::isTouchInsideNode(Touch *touch, Node *node)
{
  
  auto worldPoint = touch->getLocation();//node->getParent()->convertToWorldSpace(touch->getLocation());
  auto size = node->getContentSize();
  auto worldRectOrigin = node->convertToWorldSpace(Vec2());
  auto worldRectMax = node->convertToWorldSpace(Vec2(size.width, size.height));
  auto rect = Rect(
                   MIN(worldRectOrigin.x, worldRectMax.x),
                   MIN(worldRectOrigin.y, worldRectMax.y),
                   abs(worldRectOrigin.x - worldRectMax.x),
                   abs(worldRectOrigin.y - worldRectMax.y)
  );
  return rect.containsPoint(worldPoint);
}

BaseSpriteListener* BaseSpriteListener::createWithNode(Node *node, bool swallowTouches)
{
  auto listener = BaseSpriteListener::create();
  listener->s_node = node;
  listener->setSwallowTouches(swallowTouches);
  listener->setTouchBegin(nullptr);
//  node->getEventDispatcher()->removeAllEventListeners();
  node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
  return listener;
}


void BaseSpriteListener::setTouchBegin(ccTouchBeganCallback touchBegin)
{
  auto node = s_node;
  this->onTouchBegan = [node, touchBegin](Touch* touch, Event* event) {
    if (isTouchInsideNode(touch, node)) {
      if (touchBegin == nullptr) {
        return true;
      }
      return touchBegin(touch, event);
    }
    return false;
  };
}

void BaseSpriteListener::setTouchOver(ccTouchCallback touchOver, ccTouchCallback touchOverOut)
{
  auto node = s_node;
  this->onTouchMoved = [node, touchOver, touchOverOut](Touch* touch, Event* event){
    if (isTouchInsideNode(touch, node)) {
      if (touchOver != nullptr) {
        touchOver(touch, event);
      }
    } else {
      if (touchOverOut != nullptr) {
        touchOverOut(touch, event);
      }
    }
  };
}

void BaseSpriteListener::setTouchEnd(ccTouchCallback touchEnd, ccTouchCallback touchCanceled)
{
  auto node = s_node;
  this->onTouchEnded = [node, touchEnd, touchCanceled](Touch* touch, Event* event){
    if (isTouchInsideNode(touch, node)) {
      if (touchEnd != nullptr) {
        touchEnd(touch, event);
      }
    } else {
      if (touchCanceled != nullptr) {
        touchCanceled(touch, event);
      }
    }
  };
}

void BaseSpriteListener::setTouchClicked(ccTouchCallback touchEnd, ccTouchCallback touchCanceled)
{
  auto node = s_node;
  this->onTouchEnded = [node, touchEnd, touchCanceled](Touch* touch, Event* event) {
    if (isTouchInsideNode(touch, node) && touch->getLocation().getDistance(touch->getStartLocation()) <= 2) {
      if (touchEnd != nullptr) {
        touchEnd(touch, event);
      }
    } else {
      if (touchCanceled != nullptr) {
        touchCanceled(touch, event);
      }
    }
  };
}
