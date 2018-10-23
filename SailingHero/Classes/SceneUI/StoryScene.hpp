//
//  StoryScene.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/13/18.
//

#ifndef StoryScene_hpp
#define StoryScene_hpp

#include "SHScene.hpp"

class StoryEventData;

class StoryScene : public SHScene
{
private:
  unordered_map<StoryEventData *, float> p_storyEventDeltas;
  unordered_map<string, Node*> p_pictures;
  unordered_map<string, map<string, string>> p_originalValue;
  
  void addPictures(StoryEventData *storyEventData);
  void movePictures(StoryEventData *storyEventData);
  void setPicture(const string &pictureName, const map<string, string> &originalParameters, const map<string, string> &destinyParameters, float totalDuration = 0, float leftTime = 0);
public:
  static StoryScene* createScene();
  
  virtual bool init();
  
  void startStoryEvent(StoryEventData *storyData);
  virtual void update(float delta);
  
  // implement the "static create()" method manually
  CREATE_FUNC(StoryScene);
};

#endif /* StoryScene_hpp */
