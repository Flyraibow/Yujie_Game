//
//  ScrollViewComponent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/11/19.
//

#include "ScrollViewComponent.hpp"
#include "ui/UIScrollView.h"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "BaseSpriteListener.hpp"
#include "StoryManager.hpp"
#include "BaseButton.hpp"

USING_NS_CC;

ScrollViewComponent::ScrollViewComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_backgroundImagePath = Utils::getStringFromJson(componentJson, "path");
  p_color = Utils::getColorFromJson(componentJson, "color");
  if (componentJson.count("innerContainerSize")) {
    p_innerContainerSize = componentJson.at("innerContainerSize");
  }
}

Size ScrollViewComponent::getInnerContainerSize(Node *parent) const
{
  float width = 0, height = 0;
  if (!p_innerContainerSize.empty() && p_innerContainerSize.is_object()) {
    if (p_innerContainerSize.count("width")) {
      width = p_innerContainerSize.at("width").get<double>();
    } else if (p_innerContainerSize.count("normalized_width")) {
      width = parent->getContentSize().width * p_innerContainerSize.at("normalized_width").get<float>();
    }
    if (p_innerContainerSize.count("height")) {
      height = p_innerContainerSize.at("height").get<double>();
    } else if (p_innerContainerSize.count("normalized_height")) {
      height = parent->getContentSize().height * p_innerContainerSize.at("normalized_height").get<float>();
    }
  }
  return Size(width, height);
}

Node* ScrollViewComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  ui::ScrollView *scrollView = ui::ScrollView::create();
  if (p_backgroundImagePath.length() > 0) {
    scrollView->setBackGroundImage(p_backgroundImagePath);
  } else {
    scrollView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B(p_color));
  }
  auto size = getComponentSize(parent);
  scrollView->setContentSize(size);
  scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
  
  
  scrollView->setContentSize(size);
  if (p_direction == "both") {
    scrollView->setDirection(ui::ScrollView::Direction::BOTH);
  } else if (p_direction == "horizontal") {
    scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
  } else {
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
  }

  scrollView->setInnerContainerSize(getInnerContainerSize(scrollView));

  addNodeToParent(dict, scrollView, parent);
  
  return scrollView;
}

void ScrollViewComponent::refresh()
{
  BaseComponent::refresh();
}
