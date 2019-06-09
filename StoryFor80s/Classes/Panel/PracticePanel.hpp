//
//  PracticePanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/5/19.
//

#ifndef PracticePanel_hpp
#define PracticePanel_hpp

#include "BasePanel.hpp"

class SelectableScheduleData;
class SpriteComponent;

class PracticePanel : public BasePanel
{
private:
  string p_selectedType;
  string p_selectedSubType;
  ComponentDict p_selectableSpriteComponents;
  vector<BaseComponent *> p_selectableComponents;
  SpriteComponent* generateSelecatableSpriteComponent(SelectableScheduleData *selectableData);
  unordered_map<string, string> p_lastSubTypeFilter;
  void selectSchedule(Touch* touch, Event* event);
  void unSelectSchedule(Touch* touch, Event* event);
  void clickFilterBar(Touch* touch, Event* event);
  void selectScheduleType(const string &type, const string &subtype = "");
  
public:
  static BasePanel* createPanel();
  PracticePanel();
  void initialize();
};

#endif /* PracticePanel_hpp */
