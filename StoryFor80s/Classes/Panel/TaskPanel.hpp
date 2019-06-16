//
//  TaskPanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/15/19.
//

#ifndef TaskPanel_hpp
#define TaskPanel_hpp

#include "BasePanel.hpp"

class SpriteComponent;
class TaskData;

class TaskPanel : public BasePanel
{
private:
  ComponentDict p_spriteComponents;
  vector<BaseComponent *> p_components;
  SpriteComponent* generateTaskComponent(TaskData *taskData);
  void selectTask(Touch* touch, Event* event);
public:
  static BasePanel* createPanel();
  TaskPanel();
  void initialize();
  void referesh();
};

#endif /* TaskPanel_hpp */
