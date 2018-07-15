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

Button* SystemButton::defaultButtonWithText(std::string text)
{
  auto image = "res/button_up.png";
  auto button = Button::create(image);
  button->setScale9Enabled(true);
  button->setTitleAlignment(TextHAlignment::CENTER);
  button->setTitleText(text);
  auto lbl_size = button->getTitleRenderer()->getContentSize();
  button->setContentSize(
                         Size(
                              lbl_size.width + 20,
                              lbl_size.height + 10
                              )
                         );
  return button;
}


Button* SystemButton::defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback)
{
  auto button = SystemButton::defaultButtonWithText(text);
  button->addClickEventListener(callback);
  return button;
}


SHColorNode* SystemButton::getButtonGroupNode(const Vector<Button *> &buttons, bool withCloseButton, bool italic, const Color4B& color)
{
  auto buttonGroup = buttons;
  if (withCloseButton) {
    auto button = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_close"),
                                                      [&] (cocos2d::Ref *pSender) {
                                                        auto btn = dynamic_cast<Button*>(pSender);
                                                        btn->getParent()->removeFromParentAndCleanup(true);
                                                      });
    buttonGroup.pushBack(button);
  }
  auto node = SHColorNode::create(color);
  if (!buttonGroup.empty()) {
    static auto miniDistance = 0.09;
    static auto h_dist = - 0.02;
    const auto size = buttonGroup.size();
    auto distance = size > 1 ? MIN(miniDistance, 1.0 / (size - 1)) : 0;
    for (int i = 0; i < size; ++i) {
      auto button = buttonGroup.at(i);
      button->setAnchorPoint(Vec2(0.5, 0.5));
      button->setPositionType(Widget::PositionType::PERCENT);
      auto diff = ((size - 1) / 2.0 - i);
      double offset_y = diff * distance;
      double offset_x = italic ? diff * h_dist : 0;
      button->setPositionPercent(Vec2(0.5 + offset_x, offset_y + 0.5));
      node->addChild(button);
    }
  }
  return node;
}

SHColorNode* SystemButton::getButtonGroupNode(const Vector<Button *> &buttons, bool withCloseButton, bool italic)
{
  return SystemButton::getButtonGroupNode(buttons, withCloseButton, italic, Color4B());
}

SHColorNode* SystemButton::getButtonGroupNode(const Vector<Button *> &buttons, bool withCloseButton)
{
  return SystemButton::getButtonGroupNode(buttons, withCloseButton, true);
}

SHColorNode* SystemButton::getButtonGroupNode(const Vector<Button *> &buttons)
{
  return SystemButton::getButtonGroupNode(buttons, false);
}

