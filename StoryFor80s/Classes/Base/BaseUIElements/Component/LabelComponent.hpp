//
//  LabelComponent.hpp
//
//  Created by Yujie Liu on 9/22/18.
//

#ifndef LabelComponent_hpp
#define LabelComponent_hpp

#include "BaseComponent.hpp"
#include <vector>

class LabelComponent : public BaseComponent
{
private:
  float p_textSize;
  std::string p_text;
  std::vector<std::string> p_textParameters;
  int p_speed;
  cocos2d::Vec2 p_normalizedDimension;
  std::string decipherString() const;
protected:
public:
  LabelComponent(const nlohmann::json &componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
  void setText(const string &text) {p_text = text;};
  Label* getLabel() {return dynamic_cast<Label *>(p_node);};
};


#endif /* LabelComponent_hpp */
