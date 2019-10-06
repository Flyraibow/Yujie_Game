//
//  EventData.hpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/5/19.
//

#ifndef EventData_hpp
#define EventData_hpp

#include <stdio.h>
#include "json.hpp"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class EventData;

class ValueChangeData
{
private:
  string p_type;
  bool p_isInstant;
  double p_value;
  double p_length;
public:
  ValueChangeData(const nlohmann::json &valueJson);
  string getType() const {return p_type;};
  bool isInstant() const {return p_isInstant;};
  double getValue() const {return p_value;};
  double getLength() const {return p_length;};
};

class OptionData
{
private:
  string p_text;
  vector<ValueChangeData *> p_values;
  Label* p_weakLab;
  bool p_isSelected;
  EventData* p_parentEvent;
public:
  OptionData(const nlohmann::json &eventJson);
  ~OptionData();
  void setParentEvent(EventData* event) {p_parentEvent = event;};
  string getText() const {return p_text;};
  void setLabel(Label* lab) {p_weakLab = lab;};
  bool isNotSelected() const {return !p_isSelected;};
  
  bool clickOption(Touch* touch, Event* event);
};

class ConditionData
{
private:
  string p_type;
  string p_compareMethod;
  double p_value;
public:
  ConditionData(const nlohmann::json &conditionJson);
  ~ConditionData();
  bool pass() const;
};

class EventData
{
private:
  string p_eventName;
  double p_age;
  double p_distantAge;
  string p_text;
  double p_height;
  int p_status; // 0: not started, 1: ongoing, 2: completed
  bool p_force;
  Node* p_node = nullptr;
  vector<OptionData *> p_options;
  vector<ValueChangeData *> p_values;
  vector<ConditionData *> p_conditions;
  
public:
  EventData(const nlohmann::json &eventJson);
  EventData(Node* node) {
    p_force = false;
    p_node = node;
  };
  ~EventData();
  string getName() const {return p_eventName;};
  bool isNotStarted() const {return p_status == 0;};
  double getAge() const {return p_age;};
  double getHeight() const {return p_height;};
  double getForce() const {return p_force;};
  double getDistantAge() const {return p_distantAge;};
  void setStarted() {p_status = 1;};
  bool isNotSelected() const;
  void forceSelect();
  bool passCondition() const;
  Node* getNode();
};

#endif /* EventData_hpp */
