//
//  ColorNodeComponent.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef ColorNodeComponent_hpp
#define ColorNodeComponent_hpp

#include "BaseComponent.hpp"
#include <vector>

using namespace std;

class ColorNodeComponent : public BaseComponent
{
private:
  cocos2d::Color4B p_color;
  int p_buttonComponentOptions;
  vector<BaseComponent *> p_buttonComponentList;
  void setButtonComponentsFromJson(const nlohmann::json &componentJson);
protected:
public:
  ColorNodeComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
};

#endif /* ColorNodeComponent_hpp */
