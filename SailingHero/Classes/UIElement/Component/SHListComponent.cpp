//
//  SHListComponent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 10/15/18.
//

#include "SHListComponent.hpp"
#include "JsonUtil.hpp"
#include "DataManager.hpp"
#include "SHPanelContent.hpp"

USING_NS_CC;

SHListComponent::SHListComponent(nlohmann::json componentJson) : SHComponent(componentJson)
{
  p_panelName = SHUtil::getStringFromJson(componentJson, "file_name");
  auto dataListKey = SHUtil::getStringFromJson(componentJson, "data_list");
  p_dataList = DataManager::getShareInstance()->decipherDataList(dataListKey);
  p_cacheKey = SHUtil::getStringFromJson(componentJson, "cache_name", "cache");
  if (p_panelName.length() > 0) {
    auto panelContent = new SHPanelContent(p_panelName);
    for (int i = 0; i < p_dataList.size(); ++i) {
      auto component = panelContent->getComponent();
      component->copyAttributesFromJson(componentJson);
      p_componentList.push_back(component);
    }
    delete panelContent;
  }
}

Node* SHListComponent::addComponentToParent(ComponentDict &dict, cocos2d::Node *parent)
{
  for (int i = 0; i < p_dataList.size(); ++i) {
    DataManager::getShareInstance()->setTempData(p_cacheKey, p_dataList.at(i));
    auto component = p_componentList.at(i);
    component->addComponentToParent(dict, parent);
  }
  return nullptr;
}

void SHListComponent::refresh()
{
  for (int i = 0; i < p_dataList.size(); ++i) {
    DataManager::getShareInstance()->setTempData(p_cacheKey, p_dataList.at(i));
    auto component = p_componentList.at(i);
    component->refresh();
  }
}
