//
//  SHEditBoxComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SHEditBoxComponent.hpp"
#include "JsonUtil.hpp"
#include <unordered_map>

SHEditBoxComponent::SHEditBoxComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  p_iconPath = SHUtil::getStringFromJson(componentJson, "path");
  auto mode = SHUtil::getStringFromJson(componentJson, "input_mode");
  static const std::unordered_map<std::string, ui::EditBox::InputMode> INPUT_MODE_MAP = {
    {"ANY", ui::EditBox::InputMode::ANY},
    {"EMAIL_ADDRESS", ui::EditBox::InputMode::EMAIL_ADDRESS},
    {"NUMERIC", ui::EditBox::InputMode::NUMERIC},
    {"PHONE_NUMBER", ui::EditBox::InputMode::PHONE_NUMBER},
    {"URL", ui::EditBox::InputMode::URL},
    {"DECIMAL", ui::EditBox::InputMode::DECIMAL},
    {"SINGLE_LINE", ui::EditBox::InputMode::SINGLE_LINE}
  };
  if (INPUT_MODE_MAP.count(mode)) {
    p_mode = INPUT_MODE_MAP.at(mode);
  } else {
    p_mode = ui::EditBox::InputMode::ANY;
  }
  p_length = SHUtil::getIntFromJson(componentJson, "max_length");
  p_text = SHUtil::getStringFromJson(componentJson, "text");
}

Node* SHEditBoxComponent::addComponentToParent(unordered_map<string, Node *> &dict, cocos2d::Node *parent) const
{
  auto editBox = ui::EditBox::create(getComponentSize(parent), p_iconPath);
  editBox->setPlaceHolder(p_text.c_str());
  editBox->setInputMode(p_mode);
  editBox->setNormalizedPosition(p_normalizePosition);
  editBox->setMaxLength(p_length);
  
  addNodeToParent(dict, editBox, parent);
  
  return editBox;
}
