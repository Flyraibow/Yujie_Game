//
//  PanelContent.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef PanelContent_hpp
#define PanelContent_hpp

#include "JSONContent.hpp"
#include "BaseComponent.hpp"

USING_NS_CC;

class PanelContent : public JSONContent
{
private:
  BaseComponent *p_component;
public:
  PanelContent(const std::string &jsonFileName);
  BaseComponent* getComponent() const;
};

#endif /* SHBasePanel_hpp */
