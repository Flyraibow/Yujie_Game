//
//  SHPanelComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 10/14/18.
//

#include "SHPanelComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "SHPanelContent.hpp"

USING_NS_CC;

SHPanelComponent::SHPanelComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  p_panelName = SHUtil::getStringFromJson(componentJson, "file_name");
  if (p_panelName.length() > 0) {
    auto panelContent = new SHPanelContent(p_panelName);
    p_component = panelContent->getComponent();
    p_component->copyAttributesFromJson(componentJson);
    delete panelContent;
  } else {
    p_component = nullptr;
  }
}

Node* SHPanelComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  if (p_component != nullptr) {
    return p_component->addComponentToParent(dict, parent);
  }
  return nullptr;
}

void SHPanelComponent::refresh()
{
  if (p_component != nullptr) {
    return p_component->refresh();
  }
}
