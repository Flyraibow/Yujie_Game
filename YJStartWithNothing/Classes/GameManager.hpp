//
//  GameManager.hpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include <vector>
#include <map>

class BackgroundContainer;
class FrontContainer;
class EventNode;
class EventData;
class ValueChangeData;

using namespace std;

static const double MOVE_SPEED = 200;
static const double SECS_PER_YEAR = 6;

class GameManager {
private:
  static GameManager* p_manager;
  BackgroundContainer* p_background;
  FrontContainer* p_front;
  std::vector<EventData *> p_events;
  std::map<std::string, EventData *> p_eventsMap;
  
  std::map<std::string, double> p_values;
  vector<pair<string, pair<double, double>>> p_gradualValues;
  
  bool p_moving = false;
  bool p_started = false;
  double p_timer = 0;
  
  void loadEvents();
  void _changeValues(string type, double deltaVal, bool showMsg);
public:
  static GameManager* getInstance();
  bool getMoving() const { return p_moving;};
  bool getStarted() const { return p_started;};
  double getAge() const;
  void setContainers(BackgroundContainer* back, FrontContainer* font);
  void setMoving(bool flag);
  void setStarted(bool flag);
  void addEventNode(EventNode* node);
  void update(double delta);
  
  void valueChange(ValueChangeData* valueChange);
  void removeEvent(EventData* eventData);
  
  double getTypeValue(const string &type) const;
};

#endif /* GameManager_hpp */
