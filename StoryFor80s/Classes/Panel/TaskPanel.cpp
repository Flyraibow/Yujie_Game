//
//  TaskPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/15/19.
//

#include "TaskPanel.hpp"
#include "SpriteComponent.hpp"
#include "TaskData.hpp"
#include "ui/UIScrollView.h"
#include "ConditionManager.hpp"
#include "BaseSpriteListener.hpp"
#include "TaskLogicFunction.hpp"

BasePanel* TaskPanel::createPanel()
{
  return new TaskPanel();
}

TaskPanel::TaskPanel() : BasePanel("taskPanel")
{
}

void TaskPanel::initialize()
{
  referesh();
}

void TaskPanel::referesh()
{
  for (int i = (int)p_components.size() - 1; i >= 0; --i) {
    delete p_components[i];
  }
  p_components.clear();
  p_spriteComponents.clear();
  
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  int index = 0;
  auto allTaskMaps = *TaskData::getSharedDictionary();
  auto height = scrollView->getContentSize().height;
  for (auto taskPair : allTaskMaps) {
    if (!taskPair.second->getIsOnGoing()) {
      continue;
    }
    auto component = generateTaskComponent(taskPair.second);
    auto sprite = component->getNode();
    auto listener = BaseSpriteListener::createWithNode(sprite, false);
    listener->setTouchClicked(CC_CALLBACK_2(TaskPanel::selectTask, this), nullptr);
    int row = index / 3;
    int col = index % 3;
    sprite->setPosition(col * 310, height - row * 220);
    scrollView->addChild(sprite);
    component->refresh();
    index++;
    p_components.push_back(component);
  }
}

SpriteComponent* TaskPanel::generateTaskComponent(TaskData *taskData)
{
  auto component = dynamic_cast<SpriteComponent *>(BaseComponent::getComponentFromJsonFile("taskSprite"));
  component->setId(taskData->getId());
  component->addComponentToParent(p_spriteComponents);
  component->setAssociateData(taskData);
  auto taskStatusLabelComponent = component->getChildComponentById("task_result_lab");
  auto label = dynamic_cast<Label *>(taskStatusLabelComponent->getNode());
  
  string status = game::getTaskStatusString(taskData);
  label->setString(status);
  
  return component;
}

void TaskPanel::selectTask(Touch* touch, Event* event)
{
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  if (!BaseSpriteListener::isTouchInsideNode(touch, scrollView)) {
    CCLOG("touch is out side the view, it doesn't count");
    return;
  }
  auto sprite = event->getCurrentTarget();
  auto task = TaskData::getTaskDataById(sprite->getName());
  game::finishTask(task);
}
