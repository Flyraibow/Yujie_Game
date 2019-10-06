//
//  BackgroundContainer.hpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#ifndef BackgroundContainer_hpp
#define BackgroundContainer_hpp

#include "cocos2d.h"
#include <vector>

using namespace std;

USING_NS_CC;

class EventData;

class BackgroundContainer : public Sprite
{
private:
  bool p_moving;
  float p_positionX;
  float p_duration;
  
  vector<EventData *> p_contents;
public:
  CREATE_FUNC(BackgroundContainer);
  virtual void update(float delta);
  
  void initTitle();
  void addEvent(EventData* eventData);
  void setMoving(bool flag);
};

#endif /* BackgroundContainer_hpp */
