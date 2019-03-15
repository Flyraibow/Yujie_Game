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
//  std::string p_panelName;
  nlohmann::json p_panelContent;
  int p_count;
  vector<BaseComponent*> p_componentList;
  vector<BaseData *> p_dataList;
protected:
public:
  ListComponent(const nlohmann::json &componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* ListComponent_hpp */
