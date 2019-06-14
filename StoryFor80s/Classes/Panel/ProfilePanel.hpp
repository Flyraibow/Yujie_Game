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
class ItemData;

class ProfilePanel : public BasePanel
{
private:
  ComponentDict p_spriteComponents;
  vector<BaseComponent *> p_components;
  SpriteComponent* generateProficientComponent(ProficiencyData *proficiencyData);
  SpriteComponent* generateItemComponent(ItemData *itemData);
  string p_selectedType;
  // return true if it changed, return no it remains previous type
  bool tryChangeSelections(const string &newType);
  void selectProficiency(cocos2d::Ref *pSender);
  void selectAchievements(cocos2d::Ref *pSender);
  void selectItems(cocos2d::Ref *pSender);
public:
  static BasePanel* createPanel();
  ProfilePanel();
  void initialize();
};

#endif /* ProfilePanel_hpp */
