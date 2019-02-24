//
//  StoryEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef StoryEventContent_hpp
#define StoryEventContent_hpp

#include <stdio.h>
#include "json.hpp"

using namespace std;

class BaseScene;
typedef std::function<void()> StoryEventCallback;

class StoryEventContent
{
protected:
  string p_type;
  string p_comment;
public:
  StoryEventContent(const nlohmann::json &componentJson);
  virtual ~StoryEventContent() {};
  
  string getType() const;
  string getComment() const;
  static StoryEventContent* getStoryEventFromJson(const nlohmann::json &jsonContent);
  static vector<StoryEventContent *> getStoryEventsFromJson(const nlohmann::json &jsonContent);
  
  virtual void runEvent(BaseScene *baseScene, StoryEventCallback callback) const {
    callback();
  };
};

#endif /* StoryEventContent_hpp */
