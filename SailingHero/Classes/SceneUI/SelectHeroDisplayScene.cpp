//
//  SelectHeroDisplayScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SelectHeroDisplayScene.hpp"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "HeroSelectingFrame.hpp"
#include "SHGameDataHelper.hpp"
#include "InputBoxFrame.hpp"

USING_NS_CC;
using namespace ui;

Scene* SelectHeroDisplayScene::createScene(HeroSelectData *selectHeroData)
{
  auto scene = SelectHeroDisplayScene::create();
  scene->setSelectHeroData(selectHeroData);
  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SelectHeroDisplayScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init() )
  {
    return false;
  }
  
  this->setBackgroundImage("res/default_background.png");
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();

  auto btnCancel = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_cancel"), [](cocos2d::Ref* pSender) {
    Director::getInstance()->popScene();
  });
  btnCancel->setAnchorPoint(Vec2(1,0));
  btnCancel->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y + 12));
  this->addChild(btnCancel);
  
  p_labHeroName = Label::createWithSystemFont("", "Helvetica", 12);
  p_labHeroName->setAnchorPoint(Vec2());
  p_labHeroName->setPosition(Vec2(origin.x + visibleSize.width / 2 - 20, origin.y + 215));
  this->addChild(p_labHeroName);
  
  p_labGuildName = Label::createWithSystemFont("", "Helvetica", 12);
  p_labGuildName->setAnchorPoint(Vec2());
  p_labGuildName->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 190));
  this->addChild(p_labGuildName);
  
  P_labBirth = Label::createWithSystemFont("", "Helvetica", 12);
  P_labBirth->setAnchorPoint(Vec2());
  P_labBirth->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 175));
  this->addChild(P_labBirth);
  
  p_labZodiac = Label::createWithSystemFont("", "Helvetica", 12);
  p_labZodiac->setAnchorPoint(Vec2());
  p_labZodiac->setPosition(Vec2(origin.x + visibleSize.width / 2 + 90, origin.y + 175));
  this->addChild(p_labZodiac);
  
  p_zodiacIcon = nullptr;
  
  auto btnChangeHeroName = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("change_hero_name"), CC_CALLBACK_1(SelectHeroDisplayScene::clickChangeHeroName, this));
  auto btnChangeGuildName = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("change_guild_name"), CC_CALLBACK_1(SelectHeroDisplayScene::clickChangeGuildName, this));
  auto btnChangeHeroBirth = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("change_hero_birth"), CC_CALLBACK_1(SelectHeroDisplayScene::clickChangeHeroBirth, this));

  btnChangeHeroName->setAnchorPoint(Vec2(0,0));
  btnChangeGuildName->setAnchorPoint(Vec2(0,0));
  btnChangeHeroBirth->setAnchorPoint(Vec2(0,0));
  
  btnChangeHeroName->setPosition(Vec2(origin.x + visibleSize.width  / 2 + 20, origin.y + 90));
  btnChangeGuildName->setPosition(Vec2(origin.x + visibleSize.width  / 2 + 20, origin.y + 65));
  btnChangeHeroBirth->setPosition(Vec2(origin.x + visibleSize.width   / 2 + 20, origin.y + 40));
  this->addChild(btnChangeHeroName);
  this->addChild(btnChangeGuildName);
  this->addChild(btnChangeHeroBirth);
  
  
  auto btnConfirm = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_confirm"), [](cocos2d::Ref* pSender) {
  });
  btnConfirm->setAnchorPoint(Vec2(1,0));
  btnConfirm->setPosition(Vec2(origin.x + visibleSize.width - 100, origin.y + 12));
  
  this->addChild(btnConfirm);
  return true;
}

void SelectHeroDisplayScene::setSelectHeroData(HeroSelectData *selectHeroData)
{
  p_selectHeroData = selectHeroData;
  auto peoplePanel = HeroSelectingFrame::createBigPhotoWithSelectHeroId(selectHeroData->getSelectHeroId());
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  peoplePanel->setPosition(Vec2(origin.x + visibleSize.width / 2  - 120, origin.y + visibleSize.height / 2));
  this->addChild(peoplePanel);
  
  auto descriptionLabel = Label::createWithSystemFont(selectHeroData->getHeroDescription(), "Helvetica", 12);
  descriptionLabel->setAnchorPoint(Vec2(0, 1));
  descriptionLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 20, origin.y + 165));
  descriptionLabel->setDimensions(200, 0);
  this->addChild(descriptionLabel);
  
  this->refreshScene();
}


void SelectHeroDisplayScene::refreshScene()
{
  auto heroData = p_selectHeroData->getGuildData()->getLeaderData();
  auto zodiac = getZodiacFromHero(heroData);
  p_labHeroName->setString(getHeroFullName(heroData));
  p_labGuildName->setString(p_selectHeroData->getGuildData()->getGuildName());
  p_labZodiac->setString(zodiac->getZodiacName());
  P_labBirth->setString(getHeroBirthName(heroData));
  if (p_zodiacIcon != nullptr) {
    p_zodiacIcon->removeFromParent();
  }
  p_zodiacIcon = zodiac->getIcon(false);
  p_zodiacIcon->setAnchorPoint(Vec2());
  p_zodiacIcon->setPosition(Vec2(p_labZodiac->getPosition().x + 50, p_labZodiac->getPosition().y));
  this->addChild(p_zodiacIcon);
}


void SelectHeroDisplayScene::clickChangeHeroName(cocos2d::Ref *pSender)
{
  auto heroData = p_selectHeroData->getGuildData()->getLeaderData();
  auto inputLastNameSprite = InputBoxFrame::createWithHint(LocalizationHelper::getLocalization("input_last_name"), heroData->getHeroLastName(), [this](const string &lastName, bool canceled, Node* node){
    node->removeFromParent();
    if (!canceled) {
      auto heroData = p_selectHeroData->getGuildData()->getLeaderData();
      auto inputFirstNameSprite = InputBoxFrame::createWithHint(LocalizationHelper::getLocalization("input_first_name"), heroData->getHeroFirstName(), [lastName, heroData, this](const string &firstName, bool canceled, Node* node){
        node->removeFromParent();
        if (!canceled) {
          heroData->setHeroLastName(lastName);
          heroData->setHeroFirstName(firstName);
          this->refreshScene();
        }
      });
      this->addChild(inputFirstNameSprite);
    }
  });
  this->addChild(inputLastNameSprite);
}

void SelectHeroDisplayScene::clickChangeGuildName(cocos2d::Ref *pSender)
{
  auto guildName = p_selectHeroData->getGuildData()->getGuildName();
  auto inputLastNameSprite = InputBoxFrame::createWithHint(LocalizationHelper::getLocalization("input_guild_name"), guildName, [this](const string &guildName, bool canceled, Node* node){
    node->removeFromParent();
    if (!canceled) {
      this->p_selectHeroData->getGuildData()->setGuildName(guildName);
      this->refreshScene();
    }
  });
  this->addChild(inputLastNameSprite);
}

void SelectHeroDisplayScene::clickChangeHeroBirth(cocos2d::Ref *pSender)
{
  auto month = p_selectHeroData->getGuildData()->getLeaderData()->getBirthMonth();
  auto inputLastNameSprite = InputBoxFrame::createWithHint(LocalizationHelper::getLocalization("input_birth_month"), to_string(month), [this](const string &monthStr, bool canceled, Node* node){
    node->removeFromParent();
    if (!canceled) {
      auto day = p_selectHeroData->getGuildData()->getLeaderData()->getBirthDay();
      auto inputFirstNameSprite = InputBoxFrame::createWithHint(LocalizationHelper::getLocalization("input_birth_day"), to_string(day), [monthStr, this](const string &dayStr, bool canceled, Node* node){
        node->removeFromParent();
        if (!canceled) {
          auto heroData = p_selectHeroData->getGuildData()->getLeaderData();
          int month = atoi(monthStr.c_str());
          int day = atoi(dayStr.c_str());
          if (isBirthValid(month, day)) {
            heroData->setBirthMonth(month);
            heroData->setBirthDay(day);
            this->refreshScene();
          } else {
            // TODO: Add a dialog, invalid birth
            CCLOG("Invalid birth month %d , day %d ", month, day);
            this->clickChangeHeroBirth(nullptr);
          }
        }
      }, 2, ui::EditBox::InputMode::NUMERIC);
      this->addChild(inputFirstNameSprite);
    }
  }, 2, ui::EditBox::InputMode::NUMERIC);
  this->addChild(inputLastNameSprite);
}
