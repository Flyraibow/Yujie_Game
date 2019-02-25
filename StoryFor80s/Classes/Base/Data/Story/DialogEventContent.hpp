//
//  DialogEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef DialogEventContent_hpp
#define DialogEventContent_hpp

#include "StoryEventContent.hpp"

class DialogEventContent : public StoryEventContent
{
private:
  string p_name;
  vector<string> p_dialogIds;
public:
  DialogEventContent(const nlohmann::json &jsonContent);
  void runEvent(BaseScene *baseScene, StoryEventCallback callback);
};

#endif /* DialogEventContent_hpp */
