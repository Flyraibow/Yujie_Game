//
//  StoryScene.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/13/18.
//

#ifndef StoryScene_hpp
#define StoryScene_hpp

#include "SHScene.hpp"
#include <stack>

class StoryEventData;

typedef std::function<void()> ccStoryEventCallback;

class StoryScene : public SHScene
{
private:
  unordered_map<StoryEventData *, float> p_storyEventDeltas;
  unordered_map<string, Node*> p_pictures;
  unordered_map<string, map<string, string>> p_originalValue;
  stack<StoryEventData *> p_stackStories;
  
  bool p_isTouching;
  bool p_moveFast;
  float p_touchedDuration;
  ccStoryEventCallback p_callback;
  
  void startNextStoryEvent(StoryEventData *storyData);
  void startStoryEvent(StoryEventData *storyData);
  void addDialogs(StoryEventData *storyEventData);
  void addPictures(StoryEventData *storyEventData);
  void movePictures(StoryEventData *storyEventData);
  void showSelections(StoryEventData *storyEventData);
  void setPicture(const string &pictureName, const map<string, string> &originalParameters, const map<string, string> &destinyParameters, float totalDuration = 0, float leftTime = 0);
public:
  static StoryScene* createScene();
  
  virtual bool init();
  
  void startStory(StoryEventData *storyData, ccStoryEventCallback callback = nullptr);
  
  virtual void update(float delta);
  
  // implement the "static create()" method manually
  CREATE_FUNC(StoryScene);
};

#endif /* StoryScene_hpp */
