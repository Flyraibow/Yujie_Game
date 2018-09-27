//
//  SHPanelContent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef SHPanelContent_hpp
#define SHPanelContent_hpp

#include "SHJSONContent.hpp"
#include "SHComponent.hpp"

USING_NS_CC;

class SHPanelContent : public SHJSONContent
{
private:
  SHComponent *p_component;
public:
  SHPanelContent(const std::string &jsonFileName);
  SHComponent* getComponent() const;
};

#endif /* SHBasePanel_hpp */
