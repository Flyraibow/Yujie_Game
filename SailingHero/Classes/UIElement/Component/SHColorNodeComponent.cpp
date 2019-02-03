//
//  SHColorNodeComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SHColorNodeComponent.hpp"
#include "SHColorNode.hpp"
#include "JsonUtil.hpp"
#include "SystemButton.hpp"

USING_NS_CC;

void SHColorNodeComponent::setButtonComponentsFromJson(const nlohmann::json &componentJson)
{
  vector<SHComponent *> result;
  p_buttonComponentOptions = 0;
  if (componentJson.count("group_button")) {
    auto groupButtonJson = componentJson.at("group_button");
    if (groupButtonJson.count("components")) {
      auto componentJsonList = groupButtonJson.at("components");
      for (int i = 0; i < componentJsonList.size(); ++i) {
        nlohmann::json componentJson = componentJsonList.at(i);
        result.push_back(SHComponent::getComponentFromJson(componentJson));
      }
      if (groupButtonJson.count("options")) {
        auto optionsJson = groupButtonJson.at("options");
        p_buttonComponentOptions = SHUtil::getBoolFromJson(optionsJson, "close", false) ? (GroupButtonOptionWithCloseButton | p_buttonComponentOptions) : p_buttonComponentOptions;
        p_buttonComponentOptions = SHUtil::getBoolFromJson(optionsJson, "italic", false) ? (GroupButtonOptionItalic | p_buttonComponentOptions) : p_buttonComponentOptions;
        p_buttonComponentOptions = SHUtil::getBoolFromJson(optionsJson, "align", true) ? (GroupButtonOptionAlignAll | p_buttonComponentOptions) : p_buttonComponentOptions;
      }
    }
  }
  p_buttonComponentList = result;
}

SHColorNodeComponent::SHColorNodeComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  p_color = SHUtil::getColorFromJson(componentJson, "backgroundColor");;
  SHColorNodeComponent::setButtonComponentsFromJson(componentJson);
}

Node* SHColorNodeComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  auto parentSize = parent->getContentSize();
  SHColorNode *background = nullptr;
  if (p_buttonComponentList.size() > 0) {
    vector<SHButton *> buttons;
    for (auto buttonComponent : p_buttonComponentList) {
      auto node = buttonComponent->addComponentToParent(dict);
      if (node != nullptr) {
        auto button = dynamic_cast<SHButton *>(node);
        buttons.push_back(button);
      }
    }
    background = SystemButton::getButtonGroupNode(buttons, p_buttonComponentOptions, p_color);
  } else {
    background = SHColorNode::create(p_color, parentSize.width, parentSize.height);
  }

  addNodeToParent(dict, background, parent);

  return background;
}
