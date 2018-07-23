//
//  SHSpriteListener.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#ifndef SHSpriteListener_hpp
#define SHSpriteListener_hpp

#include "cocos2d.h"

USING_NS_CC;

class SHSpriteListener : public cocos2d::EventListenerTouchOneByOne
{
private:
  Node* s_node;
public:
  CREATE_FUNC(SHSpriteListener);
  static SHSpriteListener* createWithNode(Node *node, bool swallowTouches = true);
  void setTouchBegin(ccTouchBeganCallback touchBegin);
  void setTouchOver(ccTouchCallback touchOver, ccTouchCallback touchOverOut);
  void setTouchEnd(ccTouchCallback touchEnd, ccTouchCallback touchCanceled);
};

#endif /* SHSpriteListener_hpp */
