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

Rect calculateInnerSizeForScrollView_helper(Node *node, Rect innerRect, Vec2 offset = Vec2())
{
  double minX = fmin(innerRect.getMinX(), node->getPosition().x + offset.x);
  double minY = fmin(innerRect.getMinY(), node->getPosition().y + offset.y);
  double maxX = fmax(innerRect.getMaxX(), node->getPosition().x + node->getContentSize().width + offset.x);
  double maxY = fmax(innerRect.getMaxY(), node->getPosition().y + node->getContentSize().height + offset.y);
  innerRect = Rect(minX, minY, maxX - minX, maxY - minY);
  for(int i = 0; i < node->getChildren().size(); ++i) {
    innerRect = calculateInnerSizeForScrollView_helper(node->getChildren().at(i), innerRect, Vec2(offset.x + node->getPosition().x, offset.y + node->getPosition().y));
  }
  return innerRect;
}

Size calculateInnerSizeForScrollView(ScrollView *scrollView)
{
  Rect innerSize;
  for(int i = 0; i < scrollView->getChildren().size(); ++i) {
    innerSize = calculateInnerSizeForScrollView_helper(scrollView->getChildren().at(i), innerSize);
  }
  return innerSize.size;
}

ScrollViewComponent::ScrollViewComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
  p_backgroundImagePath = Utils::getStringFromJson(componentJson, "path");
  p_direction = Utils::getStringFromJson(componentJson, "direction", "vertical");
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
    scrollView->setBackGroundColorOpacity(p_color.a);
  }
  auto size = getComponentSize(parent);
  scrollView->setContentSize(size);
  scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);

  if (p_direction == "both") {
    scrollView->setDirection(ui::ScrollView::Direction::BOTH);
  } else if (p_direction == "horizontal") {
    scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
  } else {
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
  }
  
  if (!p_innerContainerSize.empty()) {
    scrollView->setInnerContainerSize(getInnerContainerSize(scrollView));
  }

  addNodeToParent(dict, scrollView, parent);
  
  if (p_innerContainerSize.empty()) {
    auto innerSize = calculateInnerSizeForScrollView(scrollView);
    scrollView->setInnerContainerSize(innerSize);
    // swap position make it top-left coordinate
//    auto children = scrollView->getChildren();
//    for (int i = 0; i < children.size(); ++i) {
//      auto child = children.at(i);
//      child->setPosition(Vec2(child->getPosition().x, innerSize.height - child->getPosition().y - child->getContentSize().height));
//    }
  }
  
  return scrollView;
}

void ScrollViewComponent::refresh()
{
  BaseComponent::refresh();
}
