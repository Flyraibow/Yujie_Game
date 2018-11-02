//
//  DialogFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/21/18.
//

#include "DialogFrame.hpp"
#include "SHSpriteListener.hpp"
#include "DialogData.hpp"
#include "SHGameDataHelper.hpp"
#include "DataManager.hpp"

DialogFrame::DialogFrame(const vector<string>& dialogIds, ccDialogCallback dialogCallback, Color4B color, Size windowSize)
{
  p_sprite = LayerColor::create(color);
  p_sprite->setAnchorPoint(Vec2());
  p_sprite->setContentSize(windowSize);
  auto listener = SHSpriteListener::createWithNode(p_sprite);

  p_dialogIds = dialogIds;
  p_callback = dialogCallback;
  listener->setTouchEnd(CC_CALLBACK_2(DialogFrame::clickDialogPanel, this), nullptr);
  
  p_dialogFrame = Sprite::create("res/base/dialog/dialogFrame.png");
  
  p_dialogPhotoFrame.addToParent(p_dialogFrame);
  auto sprite = p_dialogPhotoFrame.getSprite();
  
  double width = sprite->getContentSize().width + p_dialogFrame->getContentSize().width;
  p_scale = windowSize.width / width;
  p_dialogFrame->setScale(p_scale);
  p_dialogFrame->setAnchorPoint(Vec2(0.5, 0));
  p_dialogFrame->setNormalizedPosition(Vec2(0.5, 0));
  
  auto f = Director::getInstance()->getContentScaleFactor();
  
  p_sprite->addChild(p_dialogFrame);
  p_dialogContent = Label::createWithSystemFont("", "Helvetica", 14);
  p_dialogContent->setTextColor(Color4B::BLACK);
  p_dialogContent->setScale(1 / f);
  p_dialogContent->setAnchorPoint(Vec2(0, 1));
  p_dialogContent->setNormalizedPosition(Vec2(0.1, 0.85));
  p_dialogContent->setDimensions(p_dialogFrame->getContentSize().width * f * 0.8, 0);
  p_dialogFrame->addChild(p_dialogContent);
  
  p_dialogName = Label::createWithSystemFont("", "Helvetica", 12);
  p_dialogName->setTextColor(Color4B::BLACK);
  p_dialogName->setScale(1 / f);
  p_dialogName->setAnchorPoint(Vec2(0, 1));
  p_dialogName->setNormalizedPosition(Vec2(0.15, 0.85));
  p_dialogName->setVisible(false);
  p_dialogFrame->addChild(p_dialogName);
  
  sprite->setAnchorPoint(Vec2(1, 0));
  sprite->setNormalizedPosition(Vec2());
  
  p_index = 0;
  clickDialogPanel(nullptr, nullptr);
  
}


Node* DialogFrame::getSprite() const
{
  return p_sprite;
}

void DialogFrame::clickDialogPanel(Touch* touch, Event* event)
{
  if (p_index >= p_dialogIds.size()) {
    p_sprite->removeFromParent();
    p_callback();
    return;
  }
  auto dialog = DialogData::getDialogDataById(p_dialogIds[p_index++]);
  if (dialog != nullptr) {
    auto hero = dialog->getHeroIdData();
    bool showName = hero != nullptr;
    if (showName != p_dialogName->isVisible()) {
      p_dialogName->setVisible(showName);
    }
    if (showName) {
      p_dialogName->setString(getHeroDialogName(hero, dialog->getShowFullNames()));
      p_dialogContent->setNormalizedPosition(Vec2(0.1, showName ? 0.65 : 0.85));
    }
    bool showImage = (hero != nullptr && dialog->getShowImage());
    auto photoSprite = p_dialogPhotoFrame.getSprite();
    if (showImage != photoSprite->isVisible()) {
      photoSprite->setVisible(showImage);
    }
    if (showImage) {
      p_dialogFrame->setAnchorPoint(Vec2());
      p_dialogFrame->setPosition(Vec2(photoSprite->getContentSize().width * p_scale, 0));
      p_dialogPhotoFrame.setHeroData(hero);
    } else {
      p_dialogFrame->setAnchorPoint(Vec2(0.5, 0));
      p_dialogFrame->setNormalizedPosition(Vec2(0.5, 0));
    }
    auto content = DataManager::getShareInstance()->getLocalizedDialogString(dialog->getDialogId());
    p_dialogContent->setString(content);
  } else {
    p_dialogContent->setString(p_dialogIds[p_index -1] + " is not defined");
  }
}

DialogFrame* DialogFrame::createWithDialogId(const string& dialogId, ccDialogCallback dialogCallback,Color4B color, Size windowSize)
{
  return DialogFrame::createWithDialogIds({dialogId}, dialogCallback, color, windowSize);
}

DialogFrame* DialogFrame::createWithDialogIds(const vector<string>& dialogIdList, ccDialogCallback dialogCallback,Color4B color, Size windowSize)
{
  CCASSERT(dialogIdList.size() > 0, "Shouldn't create dialog without dialogIDs");
  auto dialogFrame = new DialogFrame(dialogIdList, dialogCallback, color, windowSize);
  return dialogFrame;
}
