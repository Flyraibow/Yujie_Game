//
//  MusicEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef MusicEventContent_hpp
#define MusicEventContent_hpp

#include "StoryEventContent.hpp"

enum MusicEventAction {
  MusicEventActionStop,
  MusicEventActionPlayBackgroundMusic,
  MusicEventActionPlayEffect
};

class MusicEventContent : public StoryEventContent
{
private:
  string p_path;
  MusicEventAction p_action;
public:
  MusicEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};

#endif /* MusicEventContent_hpp */
