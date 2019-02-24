//
//  ColorNodeComponent.cpp
//
//  Created by Yujie Liu on 9/26/18.
//

#include "ColorNodeComponent.hpp"
#include "BaseColorNode.hpp"
#include "JsonUtil.hpp"
#include "BaseButtonGroup.hpp"

USING_NS_CC;

void ColorNodeComponent::setButtonComponentsFromJson(const nlohmann::json &componentJson)
{
  vector<BaseComponent *> result;
  p_buttonComponentOptions = 0;
  if (componentJson.count("group_button")) {
    auto groupButtonJson = componentJson.at("group_button");
    if (groupButtonJson.count("components")) {
      auto componentJsonList = groupButtonJson.at("components");
      for (int i = 0; i < componentJsonList.size(); ++i) {
        nlohmann::json componentJson = componentJsonList.at(i);
        result.push_back(BaseComponent::getComponentFromJson(componentJson));
      }
      if (groupButtonJson.count("options")) {
        auto optionsJson = groupButtonJson.at("options");
        p_buttonComponentOptions = Utils::getBoolFromJson(optionsJson, "close", false) ? (GroupButtonOptionWithCloseButton | p_buttonComponentOptions) : p_buttonComponentOptions;
        p_buttonComponentOptions = Utils::getBoolFromJson(optionsJson, "italic", false) ? (GroupButtonOptionItalic | p_buttonComponentOptions) : p_buttonComponentOptions;
        p_buttonComponentOptions = Utils::getBoolFromJson(optionsJson, "align", true) ? (GroupButtonOptionAlignAll | p_buttonComponentOptions) : p_buttonComponentOptions;
      }
    }
  }
  p_buttonComponentList = result;
}

ColorNodeComponent::ColorNodeComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_color = Utils::getColorFromJson(componentJson, "backgroundColor");;
  ColorNodeComponent::setButtonComponentsFromJson(componentJson);
}

Node* ColorNodeComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  auto parentSize = parent->getContentSize();
  BaseColorNode *background = nullptr;
  if (p_buttonComponentList.size() > 0) {
    vector<BaseButton *> buttons;
    for (auto buttonComponent : p_buttonComponentList) {
      auto node = buttonComponent->addComponentToParent(dict);
      if (node != nullptr) {
        auto button = dynamic_cast<BaseButton *>(node);
        buttons.push_back(button);
      }
    }
    background = BaseButtonGroup::create(buttons, p_buttonComponentOptions, p_color);
  } else {
    background = BaseColorNode::create(p_color, parentSize.width, parentSize.height);
  }

  addNodeToParent(dict, background, parent);

  return background;
}
