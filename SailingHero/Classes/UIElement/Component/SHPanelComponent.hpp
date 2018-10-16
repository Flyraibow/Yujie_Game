//
//  SHPanelComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 10/14/18.
//

#ifndef SHPanelComponent_hpp
#define SHPanelComponent_hpp

#include "SHComponent.hpp"

class SHPanelComponent : public SHComponent
{
private:
  std::string p_panelName;
  SHComponent *p_component;
protected:
public:
  SHPanelComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* SHPanelComponent_hpp */
