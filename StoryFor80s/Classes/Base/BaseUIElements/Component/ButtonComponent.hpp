//
//  ButtonComponent.hpp
//
//  Created by Yujie Liu on 9/23/18.
//

#ifndef ButtonComponent_hpp
#define ButtonComponent_hpp

#include "BaseComponent.hpp"
#include <unordered_map>

USING_NS_CC;
using namespace std;

class StoryJsonData;

class ButtonComponent : public BaseComponent
{
private:
  float p_textSize;
  std::string p_text;
  std::string p_storyId;
  StoryJsonData *p_storyData;
  std::string p_imagePath;
  std::string p_disableCondition;
  unordered_map<string, string> p_setTempStrDict;
protected:
public:
  ButtonComponent(const nlohmann::json &componentJson);
  virtual ~ButtonComponent();
  Node *addComponentToParent(ComponentDict &dict, Node *parent = nullptr);
  virtual void refresh();
};


#endif /* ButtonComponent_hpp */
