//
//  MoneyFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/28/18.
//

#ifndef MoneyFrame_hpp
#define MoneyFrame_hpp

#include "cocos2d.h"
#include "CityBuildingData.hpp"

USING_NS_CC;
using namespace std;

class MoneyFrame
{
private:
  Node* p_sprite;
  CityBuildingData* p_cityBuildingData;
public:
  MoneyFrame();
  Node* getSprite() const;
};



#endif /* MoneyFrame_hpp */
