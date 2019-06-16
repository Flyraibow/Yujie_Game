//
//  TaskLogicFunction.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/15/19.
//

#ifndef TaskLogicFunction_hpp
#define TaskLogicFunction_hpp

#include <stdio.h>

using namespace std;

enum TaskStatus
{
  TaskStatus_NONE,
  TaskStatus_ONGOING,
  TaskStatus_SUCCESS,
  TaskStatus_FAIL
};

class TaskData;

namespace game {
  string getTaskStatusString(const TaskData* task);
  void updateAllTasks();
  void updateTask(TaskData* task);
  bool canStartTask(const TaskData* task);
  void startTask(TaskData* task);
  TaskStatus getTaskStatus(const TaskData* task);
  void finishTask(TaskData* task);
}

#endif /* TaskLogicFunction_hpp */
