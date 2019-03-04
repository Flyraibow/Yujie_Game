//
//  PanelEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef PanelEventContent_hpp
#define PanelEventContent_hpp

#include "StoryEventContent.hpp"
#include <vector>

class PanelEventContent : public StoryEventContent
{
private:
  string p_name;
public:
  PanelEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};

#endif /* PanelEventContent_hpp */
