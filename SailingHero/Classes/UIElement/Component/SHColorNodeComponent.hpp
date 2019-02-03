//
//  SHColorNodeComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef SHColorNodeComponent_hpp
#define SHColorNodeComponent_hpp

#include "SHComponent.hpp"
#include <vector>

using namespace std;

class SHColorNodeComponent : public SHComponent
{
private:
  cocos2d::Color4B p_color;
  int p_buttonComponentOptions;
  vector<SHComponent *> p_buttonComponentList;
  void setButtonComponentsFromJson(const nlohmann::json &componentJson);
protected:
public:
  SHColorNodeComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
};

#endif /* SHColorNodeComponent_hpp */
