//
//  DateFrame.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#ifndef DateFrame_hpp
#define DateFrame_hpp

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class DateFrame
{
private:
  Node* p_sprite;
  Label* p_labDate;
public:
  DateFrame();
  void refresh();
  Node* getSprite() const;
};


#endif /* DateFrame_hpp */
