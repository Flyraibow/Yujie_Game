//
//  ConditionEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef ConditionEventContent_hpp
#define ConditionEventContent_hpp

#include "StoryEventContent.hpp"

class StoryJsonData;

class ConditionEventContent : public StoryEventContent
{
private:
  string p_conditionStr;
  string p_yesEventId;
  string p_noEventId;
  StoryJsonData *p_yesEventData;
  StoryJsonData *p_noEventData;
public:
  ~ConditionEventContent();
  ConditionEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};

#endif /* ConditionEventContent_hpp */
