//
//  SelectionEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/2/19.
//

#ifndef SelectionEventContent_hpp
#define SelectionEventContent_hpp

#include "StoryEventContent.hpp"

class StoryJsonData;

class SelectionElement
{
private:
  string p_condition;
  string p_text;
  StoryJsonData *p_subStoryData;
  bool p_autoClose;
public:
  SelectionElement(const nlohmann::json &jsonContent);
  ~SelectionElement();
  bool isCondtionFufilled() const;
  string getText() const;
  bool isAutoClose() const;
  StoryJsonData *getStoryData() const;
};

class SelectionEventContent : public StoryEventContent
{
private:
  cocos2d::Node *p_buttonGroup;
  vector<SelectionElement *> p_selectionElements;
  cocos2d::Color4B p_backgroundColor;
public:
  virtual ~SelectionEventContent();
  SelectionEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};

#endif /* SelectionEventContent_hpp */
