//
//  ListComponent.cpp
//
//  Created by Yujie Liu on 10/15/18.
//

#include "ListComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "PanelContent.hpp"

USING_NS_CC;

ListComponent::ListComponent(const nlohmann::json &componentJson) : BaseComponent(componentJson)
{
//  p_panelName = Utils::getStringFromJson(componentJson, "file_name");
//  auto dataListKey = Utils::getStringFromJson(componentJson, "data_list");
//  p_dataList = DataManager::getShareInstance()->decipherDataList(dataListKey);
//  if (p_panelName.length() > 0) {
//    for (int i = 0; i < p_dataList.size(); ++i) {
//      auto panelContent = new PanelContent(p_panelName);
//      auto component = panelContent->getComponent();
//      component->copyAttributesFromJson(componentJson);
//      component->setAssociateData(p_dataList.at(i));
//      p_componentList.push_back(component);
//      delete panelContent;
//    }
//  }
  p_count = Utils::getIntFromJson(componentJson, "number");
  if (componentJson.count("content")) {
    p_panelContent = componentJson.at("content");
  }
  if (componentJson.count("data")) {
    p_dataList = DataManager::getShareInstance()->decipherDataList(Utils::getStringFromJson(componentJson, "data"));
    if (p_count == 0) {
      p_count = p_dataList.size();
    }
  }
//  if (p_count > 0 && !p_panelContent.empty()) {
//    for (int i = 0; i < p_count; ++i) {
//      auto component = BaseComponent::getComponentFromJson(p_panelContent);
//      p_componentList.push_back(component);
//    }
//  }
}

Node* ListComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  if (p_count > 0 && !p_panelContent.empty()) {
    for (int i = 0; i < p_count; ++i) {
      auto component = BaseComponent::getComponentFromJson(p_panelContent);
      component->setIndex(i);
      if (i < p_dataList.size()) {
        component->setAssociateData(p_dataList.at(i));
      }
      component->addComponentToParent(dict, parent);
    }
  }
//  for (int i = 0; i < p_dataList.size(); ++i) {
//    auto component = p_componentList.at(i);
//    component->addComponentToParent(dict, parent);
//  }
  return nullptr;
}

void ListComponent::refresh()
{
//  for (int i = 0; i < p_dataList.size(); ++i) {
//    auto component = p_componentList.at(i);
//    component->refresh();
//  }
}
