//
//  PhotoEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef PhotoEventContent_hpp
#define PhotoEventContent_hpp

#include "StoryEventContent.hpp"
#include "cocos2d.h"

enum PhotoEventAction {
  PhotoEventActionAdd,
  PhotoEventActionRemove,
  PhotoEventActionMove
};

enum PhotoScaleMode {
  PhotoScaleNone,
  PhotoScaleAspectFit,
  PhotoScaleAspectFill,
  PhotoScaleScaleFill
};

class PhotoEventContent : public StoryEventContent, public cocos2d::Ref
{
private:
  string p_path;
  string p_name;
  PhotoEventAction p_action;
  float p_duration;
  cocos2d::Vec2 p_normalizePosition;
  cocos2d::Vec2 p_anchorPoint;
  PhotoScaleMode p_scaleMode;
  int p_opacity;
  int p_order;
  void photoMoveTick(float delta);
  float p_currentDuration;
  cocos2d::Vec2 p_originNormalizePosition;
  cocos2d::Vec2 p_originAnchorPoint;
  double p_originScaleX;
  double p_originScaleY;
  int p_originOpacity;
  string getMoveKey() const;
public:
  PhotoEventContent(const nlohmann::json &jsonContent);
  void runEvent(BaseScene *baseScene, StoryEventCallback callback);
};


#endif /* PhotoEventContent_hpp */
