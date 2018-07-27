//
//  CityBuildingFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/26/18.
//

#ifndef CityBuildingFrame_hpp
#define CityBuildingFrame_hpp

#include "cocos2d.h"
#include "CityBuildingData.hpp"

USING_NS_CC;
using namespace std;

class CityBuildingFrame
{
private:
  Node* p_sprite;
  CityBuildingData* p_cityBuildingData;
public:
  CityBuildingFrame(int cityBuildingDataId);
  CityBuildingFrame(CityBuildingData* cityBuildingData);
  Node* getSprite() const;
};


#endif /* CityBuildingFrame_hpp */
