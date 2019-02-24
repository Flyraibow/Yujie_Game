//
//  WaitEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef WaitEventContent_hpp
#define WaitEventContent_hpp

#include "StoryEventContent.hpp"

class WaitEventContent : public StoryEventContent
{
private:
  float p_duration;
public:
  WaitEventContent(const nlohmann::json &jsonContent);
  void runEvent(BaseScene *baseScene, StoryEventCallback callback) const;
};

#endif /* WaitEventContent_hpp */
