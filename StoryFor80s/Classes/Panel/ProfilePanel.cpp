//
//  ProfilePanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/13/19.
//

#include "ProfilePanel.hpp"
#include "BaseButton.hpp"
#include "ui/UIScrollView.h"
#include "ItemData.hpp"
#include "ConditionManager.hpp"
#include "BaseSpriteListener.hpp"
#include "SpriteComponent.hpp"
#include "ProficiencyData.hpp"

BasePanel* ProfilePanel::createPanel()
{
  return new ProfilePanel();
}

ProfilePanel::ProfilePanel() : BasePanel("profilePanel")
{
}

void ProfilePanel::initialize()
{
  auto btnProficiency = getComponentById<BaseButton>("btn_proficiency");
  auto btnAchievements = getComponentById<BaseButton>("btn_achievements");
  auto btnItems = getComponentById<BaseButton>("btn_items");
  
  btnProficiency->setClickEventListener(CC_CALLBACK_1(ProfilePanel::selectProficiency, this));
  btnAchievements->setClickEventListener(CC_CALLBACK_1(ProfilePanel::selectAchievements, this));
  btnItems->setClickEventListener(CC_CALLBACK_1(ProfilePanel::selectItems, this));
  selectProficiency(nullptr);
}

bool ProfilePanel::tryChangeSelections(const string &newType)
{
  auto btnPrevious = getComponentById<BaseButton>(p_selectedType);
  if (p_selectedType == newType) {
    if (btnPrevious != nullptr) {
      btnPrevious->setHighlighted(true);
    }
    return false;
  }
  if (btnPrevious != nullptr) {
    btnPrevious->setHighlighted(false);
  }
  auto btnNew = getComponentById<BaseButton>(newType);
  btnNew->setHighlighted(true);
  // clear current
  
  for (int i = (int)p_components.size() - 1; i >= 0; --i) {
    delete p_components[i];
  }
  p_components.clear();
  p_spriteComponents.clear();
  
  p_selectedType = newType;
  return true;
}

void ProfilePanel::selectProficiency(cocos2d::Ref *pSender)
{
  if (!tryChangeSelections("btn_proficiency")) {
    return;
  }
  
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  int index = 0;
  auto allProficiencyMaps = *ProficiencyData::getSharedDictionary();
  auto height = scrollView->getContentSize().height;
  for (auto proficiencyPair : allProficiencyMaps) {
    if (proficiencyPair.second->getValue() == 0) {
      continue;
    }
    auto component = generateProficientComponent(proficiencyPair.second);
    auto sprite = component->getNode();
    int row = index / 3;
    int col = index % 3;
    sprite->setPosition(col * 265, height - row * 35);
    scrollView->addChild(sprite);
    component->refresh();
    index++;
    p_components.push_back(component);
  }
}

void ProfilePanel::selectAchievements(cocos2d::Ref *pSender)
{
  if (!tryChangeSelections("btn_achievements")) {
    return;
  }
}

void ProfilePanel::selectItems(cocos2d::Ref *pSender)
{
  if (!tryChangeSelections("btn_items")) {
    return;
  }
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  int index = 0;
  auto allItemMaps = *ItemData::getSharedDictionary();
  auto height = scrollView->getContentSize().height;
  for (auto itemPair : allItemMaps) {
    if (!itemPair.second->getHaveIt()) {
      continue;
    }
    auto component = generateItemComponent(itemPair.second);
    auto sprite = component->getNode();
    int row = index / 3;
    int col = index % 3;
    sprite->setPosition(col * 180, height - row * 180);
    scrollView->addChild(sprite);
    component->refresh();
    index++;
    p_components.push_back(component);
  }
}

SpriteComponent* ProfilePanel::generateItemComponent(ItemData *itemData)
{
  auto component = dynamic_cast<SpriteComponent *>(BaseComponent::getComponentFromJsonFile("shopItemSprite"));
  component->setId(itemData->getId());
  component->addComponentToParent(p_spriteComponents);
  component->setAssociateData(itemData);
  return component;
}

SpriteComponent* ProfilePanel::generateProficientComponent(ProficiencyData *proficiencyData)
{
  auto component = dynamic_cast<SpriteComponent *>(BaseComponent::getComponentFromJsonFile("proficiencySprite"));
  component->setId(proficiencyData->getId());
  component->addComponentToParent(p_spriteComponents);
  component->setAssociateData(proficiencyData);
  return component;
}
