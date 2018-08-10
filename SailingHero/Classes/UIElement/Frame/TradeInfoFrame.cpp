//
//  TradeInfoFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/9/18.
//

#include "TradeInfoFrame.hpp"
#include "GoodsCategoryData.hpp"
#include "GoodsPricePercentData.hpp"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"

TradeInfoFrame::TradeInfoFrame(double scale)
{
  p_sprite = Sprite::create("res/base/frame/tradeInfoFrame.png");
  p_scale = scale;
  createLabelWithScale(Vec2(0.096, 0.877), Vec2(0.5, 0.5), LocalizationHelper::getLocalization("tag_category"));
  createLabelWithScale(Vec2(0.216, 0.877), Vec2(0.5, 0.5), LocalizationHelper::getLocalization("tag_price"));
  auto sprite = p_sprite;
  auto closeButton = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_close"), [sprite](cocos2d::Ref* pSender){
    sprite->setVisible(false);
  });
  closeButton->setScale(1 / p_scale);
  closeButton->setNormalizedPosition(Vec2(0.9086, 0.0651));
  p_sprite->addChild(closeButton);
}

Label* TradeInfoFrame::createLabelWithScale(Vec2 position, Vec2 anchor, string text)
{
  auto label = Label::createWithSystemFont(text, "Helvetica", 14);
  label->setScale(1 / p_scale);
  label->setAnchorPoint(anchor);
  label->setNormalizedPosition(position);
  p_sprite->addChild(label);
  return label;
}

void TradeInfoFrame::setCityData(CityData *cityData)
{
  p_cityData = cityData;
  auto categories = GoodsCategoryData::getSharedDictionary();
  int i = 0;
  for (auto iter = categories->begin(); iter != categories->end(); iter++) {
    auto category = iter->second;
    auto categoryId = category->getCategoryId();
    auto price = GoodsPricePercentData::getGoodsPricePercent(cityData->getCityId(), categoryId);
    string priceTag = to_string(price) + "%";
    if (p_categoryPriceLabs.count(categoryId) == 0) {
      createLabelWithScale(Vec2(0.096, 0.8125 - i * 0.04181), Vec2(0.5, 0.5), category->getCategory_name());
      auto labPrice = createLabelWithScale(Vec2(0.2596, 0.8125 - i * 0.04181), Vec2(1, 0.5), priceTag);
      p_categoryPriceLabs.insert(make_pair(categoryId, labPrice));
    } else {
      p_categoryPriceLabs.at(categoryId)->setString(priceTag);
    }
    ++i;
  }
}

Sprite* TradeInfoFrame::getSprite() const
{
  return p_sprite;
}
