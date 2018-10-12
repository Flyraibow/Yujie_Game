//
//  SHSpriteComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef SHSpriteComponent_hpp
#define SHSpriteComponent_hpp

#include "SHComponent.hpp"

class SHSpriteComponent : public SHComponent
{
private:
  std::string p_iconPath;
protected:
public:
  SHSpriteComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* SHSpriteComponent_hpp */
