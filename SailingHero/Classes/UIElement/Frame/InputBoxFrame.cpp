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
  auto background = SHColorNode::create(Color4B(Color3B::BLACK, 100));
  auto sprite = Sprite::create("res/base/frame/infoBox.png");
  sprite->setPositionNormalized(Vec2(0.5, 0.7));
  auto f = Director::getInstance()->getContentScaleFactor();
  auto contentSize = sprite->getContentSize();
  
  auto hintLabel = Label::createWithSystemFont(message, "Helvetica", 18);
  hintLabel->setDimensions((contentSize.width - 20) * f, 0);
  hintLabel->setPositionNormalized(Vec2(0.5, 0.83));
  hintLabel->setScale(1 / f);
  sprite->addChild(hintLabel);
  sprite->setScale(f);
  background->addChild(sprite);
  
  auto editBox = ui::EditBox::create(Size(contentSize.width, 18), "res/base/frame/inputFrame.jpg");
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