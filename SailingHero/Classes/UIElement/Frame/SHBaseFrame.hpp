//
//  SHBaseFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/15/18.
//

#ifndef SHBaseFrame_hpp
#define SHBaseFrame_hpp

#include "cocos2d.h"
#include "SHSpriteListener.hpp"

enum class SCALE_TYPE
{
  DEFAULT = 0,
  FULL_SCENE = 1,
  FULL_HEIGHT = 2,
  FULL_WIDTH = 3,
};

USING_NS_CC;

class SHBaseFrame
{
private:
  SCALE_TYPE p_type;
  Node* p_parent;
  Node* p_cover;
protected:
  Node* p_sprite;
  virtual Node* genSprite(double scale) = 0;
public:
  SHBaseFrame(SCALE_TYPE scaleType = SCALE_TYPE::DEFAULT);
  void addToParent(Node* node, int order = 0, bool withCover = false);
  void removeFromParent();
  void setVisible(bool visible);
  
  /*
   * set location etc. don't add child.
   */
  Node* getSprite() const;
  
  /**
   * add click event, this function need call after the sprite created
   */
  void addClickEvent(SHSpriteListener::ccTouchCallback touchEndCallback);
};


#endif /* BaseFrame_hpp */
