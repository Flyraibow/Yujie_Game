//
//  InputBoxFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "InputBoxFrame.hpp"
#include "SHColorNode.hpp"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"

Node* InputBoxFrame::createWithHint(const std::string &message, const std::string &defaultValue, ccInputCallback inputCallback, int maxLength, ui::EditBox::InputMode mode)
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto background = SHColorNode::create(Color4B(Color3B::BLACK, 100), visibleSize.width, visibleSize.height);
  auto sprite = Sprite::create("res/base/frame/infoBox.png");
  sprite->setAnchorPoint(Vec2(0.5, 1));
  sprite->setPositionNormalized(Vec2(0.5, 1));
  auto f = Director::getInstance()->getContentScaleFactor();
  sprite->setScale(f);
  background->addChild(sprite);
  auto contentSize = sprite->getContentSize();
  
  auto hintLabel = Label::createWithSystemFont(message, "Helvetica", 18);
  hintLabel->setDimensions((contentSize.width * 0.9) * f, 0);
  hintLabel->setAnchorPoint(Vec2(0, 1));
  hintLabel->setPositionNormalized(Vec2(0.05, 0.83));
  hintLabel->setScale(1 / f);
  sprite->addChild(hintLabel);
  
  auto editBox = ui::EditBox::create(Size(contentSize.width, 24), "res/base/frame/inputFrame.jpg");
  editBox->setPlaceHolder(defaultValue.c_str());
  editBox->setInputMode(mode);
  editBox->setPosition(Vec2(contentSize.width / 2, contentSize.height / 2));
  editBox->setMaxLength(maxLength);
  editBox->setScale(1/f);
  sprite->addChild(editBox);

  auto btnConfirm = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_confirm"),[editBox, inputCallback, background](cocos2d::Ref* pSender) {
    string text = editBox->getText();
    if (text.length() > 0) {
      inputCallback(text,false, background);
    }
  });

  auto btnCancel = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_cancel"),[editBox,inputCallback, background](cocos2d::Ref* pSender) {
    inputCallback(editBox->getText(), true, background);
  });
  
  btnConfirm->setPositionNormalized(Vec2(0.3, 0.25));
  btnCancel->setPositionNormalized(Vec2(0.7, 0.25));
  btnConfirm->setScale(1/ f);
  btnCancel->setScale(1/ f);
  sprite->addChild(btnCancel);
  sprite->addChild(btnConfirm);
  
  return background;
}
