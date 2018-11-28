//
//  SHListComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 10/15/18.
//

#ifndef SHListComponent_hpp
#define SHListComponent_hpp

#include "SHComponent.hpp"
#include "BaseData.h"

class SHListComponent : public SHComponent
{
private:
  std::string p_panelName;
  vector<SHComponent*> p_componentList;
  vector<BaseData *> p_dataList;
protected:
public:
  SHListComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  virtual void refresh();
};

#endif /* SHListComponent_hpp */
