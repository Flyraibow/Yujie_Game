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
  ComponentDict p_selectableSpriteComponents;
  vector<BaseComponent *> p_selectableComponents;
  SpriteComponent* generateSelecatableSpriteComponent(SelectableScheduleData *selectableData);
  void selectSchedule(Touch* touch, Event* event);
  void unSelectSchedule(Touch* touch, Event* event);
  
public:
  static BasePanel* createPanel();
  PracticePanel();
  void initialize();
  void selectScheduleType(const string &type);
};

#endif /* PracticePanel_hpp */
