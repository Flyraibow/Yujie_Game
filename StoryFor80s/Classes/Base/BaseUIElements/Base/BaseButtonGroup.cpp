//
//  BaseButtonGroup.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#include "BaseButtonGroup.hpp"
#include "LocalizationHelper.hpp"

BaseButtonGroup * BaseButtonGroup::create(const Color4B& color)
{
  BaseButtonGroup * layer = new (std::nothrow) BaseButtonGroup();
  if(layer && layer->initWithColor(color))
  {
    layer->autorelease();
    return layer;
  }
  CC_SAFE_DELETE(layer);
  return nullptr;
}

BaseButtonGroup* BaseButtonGroup::create(const vector<BaseButton *> &buttons)
{
  return BaseButtonGroup::create(buttons, GroupButtonOptionItalic | GroupButtonOptionAlignAll);
}

BaseButtonGroup* BaseButtonGroup::create(const vector<BaseButton *> &buttons, int option)
{
  return BaseButtonGroup::create(buttons, option, Color4B());
}

BaseButtonGroup* BaseButtonGroup::create(const vector<BaseButton *> &buttons, int option, const Color4B& color)
{
  auto buttonGroup = buttons;
  bool isItalic = GroupButtonOptionItalic & option;
  
  auto closeGroupCallback = [&] (cocos2d::Ref *pSender) {
    auto btn = dynamic_cast<Button*>(pSender);
    btn->getParent()->removeFromParentAndCleanup(true);
  };
  if (GroupButtonOptionSelectClose & option) {
    for (auto button : buttons) {
      button->pushClickEventListener(closeGroupCallback);
    }
  }
  if (GroupButtonOptionWithCloseButton & option) {
    auto button = BaseButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_close"),
                                                      closeGroupCallback);
    buttonGroup.push_back(button);
  }
  bool alignAll = GroupButtonOptionAlignAll & option;
  float maxWidth = 0;
  auto node = BaseButtonGroup::create(color);
  if (!buttonGroup.empty()) {
    static auto miniDistance = 0.07;
    static auto h_dist = - 0.02;
    const auto size = buttonGroup.size();
    auto distance = size > 1 ? MIN(miniDistance, 1.0 / (size - 1)) : 0;
    for (int i = 0; i < size; ++i) {
      auto button = buttonGroup.at(i);
      button->setAnchorPoint(Vec2(0.5, 0.5));
      auto diff = ((size - 1) / 2.0 - i);
      double offset_y = diff * distance;
      double offset_x = isItalic ? diff * h_dist : 0;
      button->setNormalizedPosition(Vec2(0.5 + offset_x, offset_y + 0.5));
      node->addChild(button);
      if (maxWidth < button->getContentSize().width) {
        maxWidth = button->getContentSize().width;
      }
    }
    if (alignAll) {
      for (int i = 0; i < size; ++i) {
        auto button = buttonGroup.at(i);
        button->setContentSize(Size(maxWidth, button->getContentSize().height));
      }
    }
  }
  return node;
}
