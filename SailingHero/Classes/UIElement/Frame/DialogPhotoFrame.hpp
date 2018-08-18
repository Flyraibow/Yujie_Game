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
#include "SHBaseFrame.hpp"

USING_NS_CC;
using namespace std;

class DialogPhotoFrame : public SHBaseFrame
{
private:
  Sprite* p_photoSprite;
  HeroData* p_heroData;
protected:
  virtual Node* genSprite(double scale);
public:
  DialogPhotoFrame();
  void setHeroData(HeroData* heroData);
};

#endif /* DialogPhotoFrame_hpp */
