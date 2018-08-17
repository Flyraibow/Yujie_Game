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
#include "SHSpriteListener.hpp"

TradeInfoFrame::TradeInfoFrame(double scale) : SHBaseFrame::SHBaseFrame(SCALE_TYPE::DEFAULT)
{
  
}

Label* TradeInfoFrame::createLabelWithScale(Vec2 position, Vec2 anchor, string text)
{
  auto label = Label::createWithSystemFont(text, "Helvetica", 14);
  auto f = Director::getInstance()->getContentScaleFactor();
  label->setScale(1 / f);
  label->setAnchorPoint(anchor);
  label->setNormalizedPosition(position);
  p_sprite->addChild(label);
  return label;
}

void TradeInfoFrame::setCityData(CityData *cityData)
{
  p_cityData = cityData;
  if (p_sprite != nullptr) {
    auto categories = GoodsCategoryData::getSharedDictionary();
    int i = 0;
    p_labCityName->setString(LocalizationHelper::getLocalization("tag_cityPrice", cityData->getCityName()));
    for (auto iter = categories->begin(); iter != categories->end(); iter++) {
      auto category = iter->second;
      auto categoryId = category->getCategoryId();
      auto price = GoodsPricePercentData::getGoodsPricePercent(cityData->getCityId(), categoryId);
      string priceTag = to_string(price) + "%";
      if (p_categoryPriceLabs.count(categoryId) == 0) {
        createLabelWithScale(Vec2(0.096, 0.8125 - i * 0.04181), Vec2(0.5, 0.5), category->getCategoryName());
        auto labPrice = createLabelWithScale(Vec2(0.2596, 0.8125 - i * 0.04181), Vec2(1, 0.5), priceTag);
        p_categoryPriceLabs.insert(make_pair(categoryId, labPrice));
      } else {
        p_categoryPriceLabs.at(categoryId)->setString(priceTag);
      }
      ++i;
    }
  }
}


void TradeInfoFrame::updateGoodsCategory(int categoryId)
{
  p_categoryDataId = categoryId;
  if (p_sprite != nullptr) {
    auto categoryData = GoodsCategoryData::getGoodsCategoryDataById(categoryId);
    CCLOG("choose goods %s", categoryData->getCategoryName().c_str());
    p_labCategory->setString(categoryData->getCategoryName());
    p_labCategoryType->setString(categoryData->getCategoryUpdateData()->getCategoryUpdateName());
  }
}

Node* TradeInfoFrame::getSprite(double scale)
{
  if (p_sprite != nullptr) {
    return p_sprite;
  }
  p_sprite = Sprite::create("res/base/frame/tradeInfoFrame.png");
  auto f = Director::getInstance()->getContentScaleFactor();
  p_scale = scale;
  createLabelWithScale(Vec2(0.096, 0.877), Vec2(0.5, 0.5), LocalizationHelper::getLocalization("tag_category"));
  createLabelWithScale(Vec2(0.216, 0.877), Vec2(0.5, 0.5), LocalizationHelper::getLocalization("tag_price"));
  p_labCategoryType = createLabelWithScale(Vec2(0.59, 0.875), Vec2(0, 0.5), "");
  p_labCategory = createLabelWithScale(Vec2(0.5144, 0.875), Vec2(0.5, 0.5), "");
  p_labCityName = createLabelWithScale(Vec2(0.7019, 0.94), Vec2(0.5, 0.5), "");
  auto sprite = p_sprite;
  auto listener = SHSpriteListener::createWithNode(p_sprite);
  auto closeButton = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_close"), [this](cocos2d::Ref* pSender){
    this->setVisible(false);
  });
  closeButton->setScale(1 / f / scale);
  closeButton->setNormalizedPosition(Vec2(0.9086, 0.0651));
  p_sprite->addChild(closeButton);
  
  listener->setTouchBegin([sprite](Touch* touch, Event* event){
    if (!sprite->isVisible()) {
      return false;
    }
    auto point = sprite->convertToNodeSpace(touch->getLocationInView());
    auto size = sprite->getContentSize();
    auto normalizedPoint = Vec2(point.x / size.width, point.y / size.height);
    auto rect = Rect(0.0459, 0.1737, 0.2708, 0.9621);
    if (rect.containsPoint(normalizedPoint)) {
      return true;
    }
    return false;
  });
  listener->setTouchEnd([this](Touch* touch, Event* event){
    auto point = p_sprite->convertToNodeSpace(touch->getLocationInView());
    auto size = p_sprite->getContentSize();
    auto normalizedPoint = Vec2(point.x / size.width, point.y / size.height);
    auto rect = Rect(0.0459, 0.1737, 0.2708 - 0.0459, 0.9621 - 0.1737);
    if (rect.containsPoint(normalizedPoint)) {
      int categoryId = (normalizedPoint.y - rect.origin.y) / rect.size.height * 19 + 1;
      this->updateGoodsCategory(categoryId);
    }
  }, nullptr);
  
  p_sprite->setAnchorPoint(Vec2(0, 0.5));
  p_sprite->setNormalizedPosition(Vec2(0, 0.5));
  return p_sprite;
}
