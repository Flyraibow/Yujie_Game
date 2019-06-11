//
//  BaseButton.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#include "BaseButton.hpp"

USING_NS_CC;
using namespace ui;


void BaseButton::pushClickEventListener(const Widget::ccWidgetClickCallback &callback)
{
  _callbackList.push_back(callback);
  this->addClickEventListener([this](cocos2d::Ref* pSender) {
    for (auto callback : _callbackList) {
      callback(pSender);
    }
  });
}

void BaseButton::setClickEventListener(const Widget::ccWidgetClickCallback &callback)
{
  _callbackList.clear();
  pushClickEventListener(callback);
}

BaseButton* BaseButton::create(const std::string &normalImage,
                           const std::string& selectedImage,
                           const std::string& disableImage,
                           TextureResType texType)
{
  BaseButton *btn = new (std::nothrow) BaseButton;
  if (btn && btn->init(normalImage,selectedImage,disableImage,texType))
  {
    btn->autorelease();
    return btn;
  }
  CC_SAFE_DELETE(btn);
  return nullptr;
}

BaseButton* BaseButton::defaultButtonWithText(std::string text)
{
  auto image = "res/button_up.png";
  auto button = BaseButton::create(image);
  auto f = Director::getInstance()->getWinSize().width / 800;
  button->setScale9Enabled(true);
  button->setTitleFontSize(18 * f);
  button->setTitleAlignment(TextHAlignment::CENTER);
  button->setText(text);
  return button;
}


BaseButton* BaseButton::defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback)
{
  auto button = BaseButton::defaultButtonWithText(text);
  button->pushClickEventListener(callback);
  return button;
}


void BaseButton::setText(const std::string& text)
{
  this->setTitleText(text);
  auto lbl_size = this->getTitleRenderer()->getContentSize();
  this->setContentSize(
                         Size(
                              lbl_size.width + 35,
                              lbl_size.height + 16
                              )
                         );
}
