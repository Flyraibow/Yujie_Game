//
//  SystemButton.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SystemButton.hpp"
#include <algorithm>
#include "LocalizationHelper.hpp"

USING_NS_CC;
using namespace ui;


void SHButton::pushClickEventListener(const Widget::ccWidgetClickCallback &callback)
{
  _callbackList.push_back(callback);
  this->addClickEventListener([this](cocos2d::Ref* pSender) {
    for (auto callback : _callbackList) {
      callback(pSender);
    }
  });
}

SHButton* SHButton::create(const std::string &normalImage,
                       const std::string& selectedImage,
                       const std::string& disableImage,
                       TextureResType texType)
{
  SHButton *btn = new (std::nothrow) SHButton;
  if (btn && btn->init(normalImage,selectedImage,disableImage,texType))
  {
    btn->autorelease();
    return btn;
  }
  CC_SAFE_DELETE(btn);
  return nullptr;
}

SHButton* SystemButton::defaultButtonWithText(std::string text)
{
  auto image = "res/button_up.png";
  auto button = SHButton::create(image);
  auto f = Director::getInstance()->getWinSize().width / 800;
  button->setScale9Enabled(true);
  button->setTitleFontSize(18 * f);
  button->setTitleAlignment(TextHAlignment::CENTER);
  button->setTitleText(text);
  auto lbl_size = button->getTitleRenderer()->getContentSize();
  button->setContentSize(
                         Size(
                              lbl_size.width + 35,
                              lbl_size.height + 16
                              )
                         );
  return button;
}


SHButton* SystemButton::defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback)
{
  auto button = SystemButton::defaultButtonWithText(text);
  button->pushClickEventListener(callback);
  return button;
}

SHColorNode* SystemButton::getButtonGroupNode(const vector<SHButton *> &buttons)
{
  return SystemButton::getButtonGroupNode(buttons, GroupButtonOptionItalic | GroupButtonOptionAlignAll);
}

SHColorNode* SystemButton::getButtonGroupNode(const vector<SHButton *> &buttons, int option)
{
  return SystemButton::getButtonGroupNode(buttons, option, Color4B());
}

SHColorNode* SystemButton::getButtonGroupNode(const vector<SHButton *> &buttons, int option, const Color4B& color)
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
    auto button = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_close"),
                                                      closeGroupCallback);
    buttonGroup.push_back(button);
  }
  bool alignAll = GroupButtonOptionAlignAll & option;
  float maxWidth = 0;
  auto node = SHColorNode::create(color);
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

#include "ButtonData.hpp"
#include "EventManager.hpp"

SHColorNode* SystemButton::getButtonGroupFromEvent(vector<string> parameters)
{
  vector<SHButton *> buttons;
  for (int i = 0; i < parameters.size(); ++i) {
    auto buttonData = ButtonData::getButtonDataById(parameters[i]);
    if (buttonData != nullptr) {
      // also need check button data condition;
      auto button = SystemButton::defaultButtonWithText(buttonData->getLabel(), [&, buttonData] (cocos2d::Ref *pSender) {
        EventManager::getShareInstance()->runEvent(buttonData->getTriggerEventId());
      });
      buttons.push_back(button);
    }
  }
  return SystemButton::getButtonGroupNode(buttons);
}
