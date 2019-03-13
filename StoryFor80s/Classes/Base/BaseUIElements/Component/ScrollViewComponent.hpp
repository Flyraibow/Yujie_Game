//
//  ScrollViewComponent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/11/19.
//

#ifndef ScrollViewComponent_hpp
#define ScrollViewComponent_hpp

#include "BaseComponent.hpp"

class ScrollViewComponent : public BaseComponent
{
private:
  std::string p_backgroundImagePath;
  Color4B p_color;
  std::string p_direction;
  nlohmann::json p_innerContainerSize;
  Size getInnerContainerSize(Node *parent) const;
protected:
public:
  ScrollViewComponent(const nlohmann::json &componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* ScrollViewComponent_hpp */
