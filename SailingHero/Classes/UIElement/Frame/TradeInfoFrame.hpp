//
//  TradeInfoFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/9/18.
//

#ifndef TradeInfoFrame_hpp
#define TradeInfoFrame_hpp

#include "cocos2d.h"
#include "CityData.hpp"
#include "SHBaseFrame.hpp"

USING_NS_CC;

class TradeInfoFrame : public SHBaseFrame
{
private:
  CityData* p_cityData;
  int p_categoryDataId;
  double p_scale;
  map<int, Label *> p_categoryPriceLabs;
  Label* p_labCityName;
  Label* p_labCategory;
  Label* p_labCategoryType;
  Label* createLabelWithScale(Vec2 position, Vec2 anchor, string text);
protected:
  virtual Node* getSprite(double scale);
public:
  TradeInfoFrame(double scale);
  void setCityData(CityData *cityData);
  void updateGoodsCategory(int categoryId = 1);
};


#endif /* TradeInfoFrame_hpp */
