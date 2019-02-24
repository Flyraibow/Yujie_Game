//
//  PanelComponent.cpp
//
//  Created by Yujie Liu on 10/14/18.
//

#include "PanelComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "PanelContent.hpp"

USING_NS_CC;

PanelComponent::PanelComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_panelName = Utils::getStringFromJson(componentJson, "file_name");
  if (p_panelName.length() > 0) {
    auto panelContent = new PanelContent(p_panelName);
    p_component = panelContent->getComponent();
    p_component->copyAttributesFromJson(componentJson);
    delete panelContent;
  } else {
    p_component = nullptr;
  }
}

Node* PanelComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  if (p_component != nullptr) {
    return p_component->addComponentToParent(dict, parent);
  }
  return nullptr;
}

void PanelComponent::refresh()
{
  if (p_component != nullptr) {
    return p_component->refresh();
  }
}
