//
//  LabelComponent.cpp
//
//  Created by Yujie Liu on 9/22/18.
//

#include "LabelComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"

USING_NS_CC;

LabelComponent::LabelComponent(nlohmann::json componentJson) : BaseComponent(componentJson)
{
  p_textSize = SHUtil::getFloatFromJson(componentJson, "text_size");
  p_text = SHUtil::getStringFromJson(componentJson, "text");
  p_normalizedDimension = SHUtil::getVec2FromJson(componentJson, "normalized_dimensions");
}

Node* LabelComponent::addComponentToParent(ComponentDict &dict, Node *parent)
{
  auto text = p_text.size() > 0 ? DataManager::getShareInstance()->decipherString(p_text) : "";
  auto label = Label::createWithSystemFont(text, "Helvetica", p_textSize);
  
  if (parent) {
    if (!p_normalizedDimension.isZero()) {
      label->setDimensions(parent->getContentSize().width * p_normalizedDimension.x,
                           parent->getContentSize().height * p_normalizedDimension.y);
    }
  }
  addNodeToParent(dict, label, parent);
  return label;
}

void LabelComponent::refresh()
{
  BaseComponent::refresh();
  auto text = p_text.size() > 0 ? DataManager::getShareInstance()->decipherString(p_text) : "";
  auto label = dynamic_cast<Label *>(p_node);
  label->setString(text);
}
