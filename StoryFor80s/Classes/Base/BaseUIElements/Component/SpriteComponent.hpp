//
//  SpriteComponent.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "BaseComponent.hpp"

class SpriteComponent : public BaseComponent
{
private:
  std::string p_iconPath;
  Color4B p_color;
protected:
public:
  SpriteComponent(const nlohmann::json &componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* SpriteComponent_hpp */
