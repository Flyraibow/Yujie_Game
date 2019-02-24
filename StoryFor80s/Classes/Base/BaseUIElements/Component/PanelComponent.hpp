//
//  PanelComponent.hpp
//
//  Created by Yujie Liu on 10/14/18.
//

#ifndef PanelComponent_hpp
#define PanelComponent_hpp

#include "BaseComponent.hpp"

class PanelComponent : public BaseComponent
{
private:
  std::string p_panelName;
  BaseComponent *p_component;
protected:
public:
  PanelComponent(const nlohmann::json &componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* PanelComponent_hpp */
