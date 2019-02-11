//
//  ListComponent.hpp
//
//  Created by Yujie Liu on 10/15/18.
//

#ifndef ListComponent_hpp
#define ListComponent_hpp

#include "BaseComponent.hpp"
#include "BaseData.h"

class ListComponent : public BaseComponent
{
private:
  std::string p_panelName;
  vector<BaseComponent*> p_componentList;
  vector<BaseData *> p_dataList;
protected:
public:
  ListComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* ListComponent_hpp */
