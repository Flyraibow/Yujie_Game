//
//  AreaMapFrame.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#ifndef AreaMapFrame_hpp
#define AreaMapFrame_hpp

#include "cocos2d.h"
#include "AreaData.hpp"
#include "SHBaseFrame.hpp"

USING_NS_CC;
using namespace std;

class CityData;

typedef function<void(CityData *)> ccCityDataSelectCallback;

class AreaMapFrame : public SHBaseFrame
{
private:
  Node* p_areaSprite;
  void refresh();
  AreaData* p_areaData;
  Vector<MenuItem*> p_cityList;
  ccCityDataSelectCallback p_cityDataSelectCallback;
protected:
  virtual Node* genSprite(double scale);
public:
  AreaMapFrame();
  void setAreaData(AreaData* areaData);
  void setCityDataSelectCallback(ccCityDataSelectCallback cityDataSelectCallback);
};


#endif /* AreaMapFrame_hpp */
