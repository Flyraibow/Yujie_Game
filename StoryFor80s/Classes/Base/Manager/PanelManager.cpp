//
//  PanelManager.cpp
//
//  Created by Yujie Liu on 9/27/18.
//

#include "PanelManager.hpp"

PanelManager* PanelManager::s_sharedManager = nullptr;
std::unordered_map<std::string, getPanel> PanelManager::s_panelFuncMap = {};

PanelManager* PanelManager::getShareInstance()
{
  if (s_sharedManager == nullptr) {
    s_sharedManager = new PanelManager();
  }
  return s_sharedManager;
}

bool PanelManager::isRegistered(const std::string &panelName)
{
  return s_panelFuncMap.count(panelName);
}

BasePanel* PanelManager::getPanelById(const std::string &panelName) const
{
  if (isRegistered(panelName)) {
    return s_panelFuncMap.at(panelName)();
  }
  return new BasePanel(panelName);
}
