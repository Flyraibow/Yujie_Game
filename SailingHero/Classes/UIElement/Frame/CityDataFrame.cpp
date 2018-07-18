//
//  CityDataFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/16/18.
//

#include "CityDataFrame.hpp"
#include "LocalizationHelper.hpp"

static const int MAX_GOODS_NUM = 5;

CityDataFrame::CityDataFrame()
{
  p_sprite = Sprite::create("res/base/frame/cityDataFrame.png");
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  p_scale = visibleSize.height / p_sprite->getContentSize().height;
  p_sprite->setScale(p_scale);
  p_sprite->setAnchorPoint(Vec2(1, 0));
  p_sprite->setNormalizedPosition(Vec2(1, 0));
  
  p_labCityName = createLabelWithScale(Vec2(0.08, 0.933));
  p_labCityType = createLabelWithScale(Vec2(0.08, 0.866));
  p_labCulture = createLabelWithScale(Vec2(0.4, 0.866));
  p_labCommerce = createLabelWithScale(Vec2(0.08, 0.802),Vec2(), LocalizationHelper::getLocalization("tag_commerce"));
  p_labMilitary = createLabelWithScale(Vec2(0.08, 0.75),Vec2(), LocalizationHelper::getLocalization("tag_military"));
  p_labCommerceValue = createLabelWithScale(Vec2(0.86, 0.802), Vec2(1, 0));
  p_labMilitaryValue = createLabelWithScale(Vec2(0.86, 0.75), Vec2(1, 0));
  p_labCityStatus = createLabelWithScale(Vec2(0.5, 0.701), Vec2(0.5, 0));
  p_labGoodsTag = createLabelWithScale(Vec2(0.12, 0.35),Vec2(), LocalizationHelper::getLocalization("tag_goods"));
  
  for (int i = 0; i < MAX_GOODS_NUM; ++i) {
    auto label = createLabelWithScale(Vec2(0.08, 0.302 - i * 0.0498),Vec2(), LocalizationHelper::getLocalization("tag_goods"));
    p_labGoodsList.push_back(label);
  }
}

Label* CityDataFrame::createLabelWithScale(Vec2 position, Vec2 anchor, string text)
{
  auto label = Label::createWithSystemFont(text, "Helvetica", 8);
  label->setScale(1 / p_scale);
  label->setAnchorPoint(anchor);
  label->setNormalizedPosition(position);
  p_sprite->addChild(label);
  return label;
}

void CityDataFrame::setCityData(CityData *cityData)
{
  p_cityData = cityData;
  refresh();
}

void CityDataFrame::refresh()
{
  p_labCityName->setString(p_cityData->getCityName());
  p_labCityType->setString(p_cityData->getCityTypeData()->getCityTypeName());
  p_labCulture->setString(p_cityData->getCultureData()->getCultureName());
  p_labMilitaryValue->setString(to_string(p_cityData->getMilltary()));
  p_labCommerceValue->setString(to_string(p_cityData->getCommerce()));
  p_labCityStatus->setString(p_cityData->getCityStatusData()->getCityStatusName());
  auto goodsList = p_cityData->getCityGoodsDataVector();
  int index = 0;
  for (int i = 0; i < goodsList.size(); ++i) {
    auto cityGoods = goodsList[i];
    if (!cityGoods->getIsHidden()) {
      p_labGoodsList[index++]->setString(cityGoods->getGoodsData()->getGoodsName());
    }
  }
  for (int i = index; i < MAX_GOODS_NUM; ++i) {
    p_labGoodsList[index++]->setString("");
  }
}


Sprite* CityDataFrame::getSprite() const
{
  return p_sprite;
}
