//
//  PanelContent.cpp
//
//  Created by Yujie Liu on 9/26/18.
//

#include "PanelContent.hpp"

using namespace nlohmann;

PanelContent::PanelContent(const std::string &jsonFileName) : JSONContent("res/base/panel/" + jsonFileName + ".json")
{
  p_component = BaseComponent::getComponentFromJson(p_jsonContent);
}

BaseComponent* PanelContent::getComponent() const
{
  return p_component;
}
