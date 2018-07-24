//
//  DialogPhotoFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/23/18.
//

#ifndef DialogPhotoFrame_hpp
#define DialogPhotoFrame_hpp

#include "cocos2d.h"
#include "HeroData.hpp"

USING_NS_CC;
using namespace std;

class DialogPhotoFrame
{
private:
  Node* p_background;
  Sprite* p_photoSprite;
  HeroData* p_heroData;
public:
  DialogPhotoFrame();
  Node* getSprite() const;
  void setHeroData(HeroData* heroData);
};

#endif /* DialogPhotoFrame_hpp */
