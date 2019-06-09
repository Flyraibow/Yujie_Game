//
//  BaseSpriteListener.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#ifndef BaseSpriteListener_hpp
#define BaseSpriteListener_hpp

#include "cocos2d.h"

USING_NS_CC;

class BaseSpriteListener : public cocos2d::EventListenerTouchOneByOne
{
private:
  Node* s_node;
public:
  CREATE_FUNC(BaseSpriteListener);
  static BaseSpriteListener* createWithNode(Node *node, bool swallowTouches = true);
  void setTouchBegin(ccTouchBeganCallback touchBegin);
  void setTouchOver(ccTouchCallback touchOver, ccTouchCallback touchOverOut);
  void setTouchEnd(ccTouchCallback touchEnd, ccTouchCallback touchCanceled);
  // won't trigger if mouth moved too much
  void setTouchClicked(ccTouchCallback touchEnd, ccTouchCallback touchCanceled);
  
  static bool isTouchInsideNode(Touch *touch, Node *node);
};

#endif /* BaseSpriteListener_hpp */
