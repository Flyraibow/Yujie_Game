//
//  DialogFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/21/18.
//

#ifndef DialogFrame_hpp
#define DialogFrame_hpp

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class DialogFrame
{
private:
  Node* p_sprite;
  Sprite* p_dialogFrame;
  Label* p_dialogContent;
  double p_scale;
public:
  DialogFrame(const string& text);
  Node* getSprite() const;
  void setText(const string& text);
  
  static DialogFrame* createWithContent(const string& text);
};

#endif /* DialogFrame_hpp */
