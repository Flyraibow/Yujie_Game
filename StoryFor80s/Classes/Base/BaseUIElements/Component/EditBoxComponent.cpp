//
//  EditBoxComponent.cpp
//
//  Created by Yujie Liu on 9/26/18.
//

#include "EditBoxComponent.hpp"
#include "JsonUtil.hpp"
#include <unordered_map>
#include "DataManager.hpp"

EditBoxComponent::EditBoxComponent(nlohmann::json componentJson) : BaseComponent(componentJson)
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
  p_tempString = SHUtil::getStringFromJson(componentJson, "setTemp");
}

Node* EditBoxComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  auto editBox = ui::EditBox::create(getComponentSize(parent), p_iconPath);
  auto defaultText = DataManager::getShareInstance()->decipherString(p_text);
  editBox->setPlaceHolder(defaultText.c_str());
  editBox->setInputMode(p_mode);
  editBox->setNormalizedPosition(p_normalizePosition);
  editBox->setMaxLength(p_length);
  if (p_tempString.length() > 0) {
    DataManager::getShareInstance()->setTempString(p_tempString, defaultText);
    editBox->setDelegate(this);
  }
  
  addNodeToParent(dict, editBox, parent);
  
  return editBox;
}

void EditBoxComponent::editBoxTextChanged(ui::EditBox* editBox, const std::string& text)
{
  DataManager::getShareInstance()->setTempString(p_tempString, editBox->getText());
}

void EditBoxComponent::editBoxReturn(ui::EditBox* editBox)
{
  DataManager::getShareInstance()->setTempString(p_tempString, editBox->getText());
}
