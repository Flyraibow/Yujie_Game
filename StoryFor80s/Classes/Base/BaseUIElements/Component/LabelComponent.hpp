//
//  LabelComponent.hpp
//
//  Created by Yujie Liu on 9/22/18.
//

#ifndef LabelComponent_hpp
#define LabelComponent_hpp

#include "BaseComponent.hpp"

class LabelComponent : public BaseComponent
{
private:
  float p_textSize;
  std::string p_text;
  cocos2d::Vec2 p_normalizedDimension;
protected:
public:
  LabelComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};


#endif /* LabelComponent_hpp */
