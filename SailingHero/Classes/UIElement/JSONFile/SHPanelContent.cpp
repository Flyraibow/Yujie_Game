//
//  SHPanelContent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SHPanelContent.hpp"

using namespace nlohmann;

SHPanelContent::SHPanelContent(const std::string &jsonFileName) : SHJSONContent("res/base/panel/" + jsonFileName + ".json")
{
  p_component = SHComponent::getComponentFromJson(p_jsonContent);
}

SHComponent* SHPanelContent::getComponent() const
{
  return p_component;
}
