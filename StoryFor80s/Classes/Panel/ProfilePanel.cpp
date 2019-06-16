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
#include "ScrollViewComponent.hpp"
#include "GameLogicFunction.hpp"
#include "LocalizationHelper.hpp"
#include "BaseDropDownMenu.hpp"
#include "SceneManager.hpp"

static const string kProficiencyBtn = "btn_proficiency";
static const string kAchievementsBtn = "btn_achievements";
static const string kItemBtn = "btn_items";

BasePanel* ProfilePanel::createPanel()
{
  return new ProfilePanel();
}

ProfilePanel::ProfilePanel() : BasePanel("profilePanel")
{
}

void ProfilePanel::initialize()
{
  auto btnProficiency = getComponentById<BaseButton>(kProficiencyBtn);
  auto btnAchievements = getComponentById<BaseButton>(kAchievementsBtn);
  auto btnItems = getComponentById<BaseButton>(kItemBtn);
  
  btnProficiency->setClickEventListener(CC_CALLBACK_1(ProfilePanel::selectProficiency, this));
  btnAchievements->setClickEventListener(CC_CALLBACK_1(ProfilePanel::selectAchievements, this));
  btnItems->setClickEventListener(CC_CALLBACK_1(ProfilePanel::selectItems, this));
  selectProficiency(nullptr);
  
  auto filterSprite = getComponentById<Sprite>("filter");
  auto listener = BaseSpriteListener::createWithNode(filterSprite, false);
  listener->setTouchEnd(CC_CALLBACK_2(ProfilePanel::clickFilterBar, this), nullptr);
}

void ProfilePanel::clickFilterBar(Touch* touch, Event* event)
{
  vector<string> results;
  vector<string> labels;
  labels.push_back(LocalizationHelper::getLocalization("empty"));
  results.push_back("");
  if (p_selectedType == kProficiencyBtn) {
    auto proficiencyCategoryTypes = game::getAllProficiencyCategories();
    for (auto proficiencyCategoryType : proficiencyCategoryTypes) {
      results.push_back(proficiencyCategoryType->getProficiencyCategoryId());
      labels.push_back(proficiencyCategoryType->getName());
    }
  } else if (p_selectedType == kAchievementsBtn) {
    auto achievementCategoryTypes = game::getAllAchievementCategories();
    for (auto achievementCategoryType : achievementCategoryTypes) {
      results.push_back(achievementCategoryType->getCategoryId());
      labels.push_back(achievementCategoryType->getName());
    }
  }
  
  auto dropDown = BaseDropDownMenu::create([this, results](int index){
    if (index >= 0) {
      CCLOG("select sub type : %s", results.at(index).c_str());
      tryChangeFilterTypes(results.at(index));
    } else {
      CCLOG("canceled");
    }
  });
  dropDown->setSelections(labels);
  dropDown->setMaxHeight(200);
  dropDown->setDropDownMenuItem(Size(200, 22), Color4B(100, 100, 100, 100), Color4B(200, 100, 100, 100));
  dropDown->render();
  auto baseScene = SceneManager::getShareInstance()->currentScene();
  baseScene->addChild(dropDown, SCREEN_DIALOG_LAYER);
}

void ProfilePanel::tryChangeFilterTypes(const string &filterType)
{
  auto previousFilterType = p_lastTypeFilter.count(p_selectedType) ? p_lastTypeFilter.at(p_selectedType) : "";
  if (previousFilterType == filterType) {
    return;
  }
  p_lastTypeFilter[p_selectedType] = filterType;
  if (p_selectedType == kProficiencyBtn) {
    refreshProficiency();
  } else if (p_selectedType == kAchievementsBtn) {
    refreshAchievements();
  } else if (p_selectedType == kItemBtn) {
    refreshItems();
  }
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
  
  p_selectedType = newType;
  return true;
}

void ProfilePanel::clearComponents()
{
  for (int i = (int)p_components.size() - 1; i >= 0; --i) {
    delete p_components[i];
  }
  p_components.clear();
  p_spriteComponents.clear();
  
}

void ProfilePanel::selectProficiency(cocos2d::Ref *pSender)
{
  if (!tryChangeSelections(kProficiencyBtn)) {
    return;
  }
  refreshProficiency();
}

void ProfilePanel::selectAchievements(cocos2d::Ref *pSender)
{
  if (!tryChangeSelections(kAchievementsBtn)) {
    return;
  }
  refreshAchievements();
}

void ProfilePanel::selectItems(cocos2d::Ref *pSender)
{
  if (!tryChangeSelections(kItemBtn)) {
    return;
  }
  refreshItems();
}

void ProfilePanel::refreshProficiency()
{
  clearComponents();
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  int index = 0;
  auto categoryId = p_lastTypeFilter.count(p_selectedType) ? p_lastTypeFilter.at(p_selectedType) : "";
  auto filterLab = getComponentById<Label>("filter_lib");
  if (categoryId.length() > 0) {
    filterLab->setString(ProficiencyCategoryData::getProficiencyCategoryDataById(categoryId)->getName());
  } else {
    filterLab->setString(LocalizationHelper::getLocalization("lab_filter"));
  }
  
  auto allMyProficiencies = game::getMyProficiencies(categoryId);
  int rows = allMyProficiencies.size() / 3;
  float height = 35 * rows;
  if (height < scrollView->getContentSize().height) {
    height = scrollView->getContentSize().height;
  }
  for (auto proficiency : allMyProficiencies) {
    auto component = generateProficientComponent(proficiency);
    auto sprite = component->getNode();
    int row = index / 3;
    int col = index % 3;
    sprite->setPosition(col * 265, height - row * 35);
    scrollView->addChild(sprite);
    component->refresh();
    index++;
    p_components.push_back(component);
  }
  scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, height));
}

void ProfilePanel::refreshAchievements()
{
  clearComponents();
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  int index = 0;
  auto categoryId = p_lastTypeFilter.count(p_selectedType) ? p_lastTypeFilter.at(p_selectedType) : "";
  auto filterLab = getComponentById<Label>("filter_lib");
  if (categoryId.length() > 0) {
    filterLab->setString(AchievementCategoryData::getAchievementCategoryDataById(categoryId)->getName());
  } else {
    filterLab->setString(LocalizationHelper::getLocalization("lab_filter"));
  }
  
  auto allMyAchievements = game::getMyAchievements(categoryId);
  int rows = allMyAchievements.size() / 3;
  float height = 35 * rows;
  if (height < scrollView->getContentSize().height) {
    height = scrollView->getContentSize().height;
  }
  for (auto achievement : allMyAchievements) {
    auto component = generateAchievementComponent(achievement);
    auto sprite = component->getNode();
    int row = index / 3;
    int col = index % 3;
    sprite->setPosition(col * 265, height - row * 35);
    scrollView->addChild(sprite);
    component->refresh();
    index++;
    p_components.push_back(component);
  }
  scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, height));
}

void ProfilePanel::refreshItems()
{
  clearComponents();
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  int index = 0;
  getComponentById<Label>("filter_lib")->setString(LocalizationHelper::getLocalization("lab_filter"));
  
  auto allMyItems = game::getMyItems();
  int rows = allMyItems.size() / 3;
  float height = 180 * rows;
  if (height < scrollView->getContentSize().height) {
    height = scrollView->getContentSize().height;
  }
  for (auto item : allMyItems) {
    auto component = generateItemComponent(item);
    auto sprite = component->getNode();
    int row = index / 3;
    int col = index % 3;
    sprite->setPosition(col * 180, height - row * 180);
    scrollView->addChild(sprite);
    component->refresh();
    index++;
    p_components.push_back(component);
  }
  scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, height));
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

SpriteComponent* ProfilePanel::generateAchievementComponent(AchievementsData *achivementData)
{
  auto component = dynamic_cast<SpriteComponent *>(BaseComponent::getComponentFromJsonFile("achievementSprite"));
  component->setId(achivementData->getId());
  component->addComponentToParent(p_spriteComponents);
  component->setAssociateData(achivementData);
  return component;
}
