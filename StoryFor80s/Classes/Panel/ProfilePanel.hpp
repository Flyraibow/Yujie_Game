//
//  ProfilePanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/13/19.
//

#ifndef ProfilePanel_hpp
#define ProfilePanel_hpp

#include "BasePanel.hpp"

class SpriteComponent;
class ProficiencyData;
class AchievementsData;
class ItemData;

class ProfilePanel : public BasePanel
{
private:
  ComponentDict p_spriteComponents;
  vector<BaseComponent *> p_components;
  unordered_map<string, string> p_lastTypeFilter;
  SpriteComponent* generateProficientComponent(ProficiencyData *proficiencyData);
  SpriteComponent* generateItemComponent(ItemData *itemData);
  SpriteComponent* generateAchievementComponent(AchievementsData *achivementData);
  string p_selectedType;
  // return true if it changed, return no it remains previous type
  bool tryChangeSelections(const string &newType);
  void tryChangeFilterTypes(const string &filterType);
  void selectProficiency(cocos2d::Ref *pSender);
  void selectAchievements(cocos2d::Ref *pSender);
  void selectItems(cocos2d::Ref *pSender);
  void clearComponents();
  void refreshProficiency();
  void refreshAchievements();
  void refreshItems();
  void clickFilterBar(Touch* touch, Event* event);
public:
  static BasePanel* createPanel();
  ProfilePanel();
  void initialize();
};

#endif /* ProfilePanel_hpp */
