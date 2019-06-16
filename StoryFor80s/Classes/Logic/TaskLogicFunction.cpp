//
//  TaskLogicFunction.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/15/19.
//

#include "TaskLogicFunction.hpp"
#include "TaskData.hpp"
#include "ConditionManager.hpp"
#include "GameData.hpp"
#include "StoryManager.hpp"

void game::updateAllTasks()
{
  auto allTaskMap = *TaskData::getSharedDictionary();
  for (auto taskPair : allTaskMap) {
    updateTask(taskPair.second);
  }
}

void game::updateTask(TaskData* task)
{
  if (!task->getIsOnGoing() || task->getFailed()) {
    return;
  }
  // 如果有失败条件
  if (task->getFailCondition().length() > 0) {
    if (Manager::checkConditionByString(task->getFailCondition())) {
      task->setFailed(true);
    }
  }
  // 如果有禁止 安排
  auto forbidenSchdule = task->getForbiddenScheduleData();
  if (forbidenSchdule != nullptr) {
    auto lastMonthScheduleIds = GameData::getSharedInstance()->getLastMonthScheduleIdVector();
    for (auto scheduleId : lastMonthScheduleIds) {
      if (scheduleId == forbidenSchdule->getId()) {
        task->setFailed(true);
        break;
      }
    }
  }
  if (task->getLimitedMonth() > 0) {
    // calculate left month
    int year = GameData::getSharedInstance()->getGameDateData()->getYear();
    int month = GameData::getSharedInstance()->getGameDateData()->getMonth();
    int startYear = task->getStartedYear();
    int startMonth = task->getStartedMonth();
    int passedMonth = year * 12 + month - startYear * 12 - startMonth;
    int leftMonth = task->getLimitedMonth() - passedMonth;
    if (leftMonth < 0) {
      leftMonth = 0;
      if (task->getSuccessCondition().length() > 0) {
        // 有成功条件的，时间一到就算失败。
        task->setFailed(true);
      }
    }
    task->setLeftMonth(leftMonth);
  }
}

bool game::canStartTask(const TaskData* task)
{
  if (task->getIsOnGoing()) {
    // skip it
    return false;
  }
  if (task->getFailCondition().length() > 0 && Manager::checkConditionByString(task->getFailCondition())) {
    // skip it if it's already fail
    return false;
  }
  return true;
}

void game::startTask(TaskData* task)
{
  if (task->getLimitedMonth() > 0) {
    // calculate left month
    int year = GameData::getSharedInstance()->getGameDateData()->getYear();
    int month = GameData::getSharedInstance()->getGameDateData()->getMonth();
    task->setStartedYear(year);
    task->setStartedMonth(month);
    task->setLeftMonth(task->getLimitedMonth());
  }
  task->setFailed(false);
  task->setIsOnGoing(true);
}

TaskStatus game::getTaskStatus(const TaskData* task)
{
  if (task->getIsOnGoing()) {
    if (task->getFailed()) {
      return TaskStatus_FAIL;
    }
    if (task->getSuccessCondition().length() > 0) {
      if (Manager::checkConditionByString(task->getSuccessCondition())) {
        return TaskStatus_SUCCESS;
      }
    } else if (task->getLeftMonth() == 0) {
      return TaskStatus_SUCCESS;
    }
    return TaskStatus_ONGOING;
  }
  return TaskStatus_NONE;
}

void game::finishTask(TaskData* task)
{
  TaskStatus status = getTaskStatus(task);
  if (status == TaskStatus_SUCCESS) {
    task->setIsOnGoing(false);
    StoryManager::getShareInstance()->startStory(task->getSuccessEvent());
  } else if (status == TaskStatus_FAIL) {
    task->setIsOnGoing(false);
    StoryManager::getShareInstance()->startStory(task->getFailedEvent());
  }
}

string game::getTaskStatusString(const TaskData* task)
{
  TaskStatus status = getTaskStatus(task);
  switch (status) {
    case TaskStatus_SUCCESS:
      return "任务成功";
    case TaskStatus_FAIL:
      return "任务失败";
    case TaskStatus_ONGOING:
      return "任务执行中";
    case TaskStatus_NONE:
      return "未领取";
  }
}
