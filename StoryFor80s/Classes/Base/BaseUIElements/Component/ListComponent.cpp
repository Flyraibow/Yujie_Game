//
//  ListComponent.cpp
//
//  Created by Yujie Liu on 10/15/18.
//

#include "ListComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "PanelContent.hpp"
#include "ConditionManager.hpp"

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
  p_condition = Utils::getStringFromJson(componentJson, "condition");
  if (componentJson.count("data")) {
    
    p_dataListStr = Utils::getStringFromJson(componentJson, "data");
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
  p_dict = dict;
  p_parent = parent;
  
  refresh();

  return nullptr;
}

void ListComponent::refresh()
{
  // if p_componentList is not empty, we need probably remove current view first
  if (p_componentList.size() > 0) {
    for (auto component : p_componentList) {
      component->remove(p_dict);
    }
  }
  p_componentList.clear();
  auto dataList = DataManager::getShareInstance()->decipherDataList(p_dataListStr);
  auto count = p_count == 0 ? dataList.size() : p_count;
  if (count > 0 && !p_panelContent.empty()) {
    auto index = 0;
    for (int i = 0; i < count; ++i) {
      if (i < dataList.size()) {
        auto associateData = dataList.at(i);
        if (p_condition.length() == 0 || Manager::checkConditionByString(p_condition, associateData)) {
          auto component = BaseComponent::getComponentFromJson(p_panelContent);
          component->setIndex(index++);
          component->setAssociateData(associateData);
          component->addComponentToParent(p_dict, p_parent);
          p_componentList.push_back(component);
        }
      }
    }
  }
}
