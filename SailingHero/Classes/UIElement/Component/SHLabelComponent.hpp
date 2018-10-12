//
//  SHLabelComponent.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/22/18.
//

#ifndef SHLabelComponent_hpp
#define SHLabelComponent_hpp

#include "SHComponent.hpp"

class SHLabelComponent : public SHComponent
{
private:
  float p_textSize;
  std::string p_text;
  cocos2d::Vec2 p_normalizedDimension;
protected:
public:
  SHLabelComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};


#endif /* SHLabelComponent_hpp */
