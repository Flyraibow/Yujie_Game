//
//  DialogEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef DialogEventContent_hpp
#define DialogEventContent_hpp

#include "StoryEventContent.hpp"

class DialogElements
{
private:
  string p_name;
  string p_content;
  vector<string> p_parameters;
public:
  DialogElements(const nlohmann::json &jsonContent);
  DialogElements(const string &name, const string &content, const vector<string> parameters);
  ~DialogElements() {};
  
  string getName() const;
  string getContent() const;
  vector<string> getParameters() const;
};

class DialogEventContent : public StoryEventContent
{
private:
  string p_name;
  vector<DialogElements *> p_dialogs;
public:
  DialogEventContent(const nlohmann::json &jsonContent);
  ~DialogEventContent();
  void runEvent(StoryEventCallback callback);
};

#endif /* DialogEventContent_hpp */
