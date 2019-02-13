//
//  PanelManager.cpp
//
//  Created by Yujie Liu on 9/27/18.
//

#include "PanelManager.hpp"

PanelManager* PanelManager::p_sharedManager = nullptr;

PanelManager* PanelManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new PanelManager();
  }
  return p_sharedManager;
}

template <typename T, typename std::enable_if<std::is_base_of<BasePanel, T>::value>::type*>
void PanelManager::registerPanel(const std::string &panelName)
{
  p_sharedManager->p_panelFuncMap[panelName] = T::createPanel;
}


bool PanelManager::isRegistered(const std::string &panelName) const
{
  return p_panelFuncMap.count(panelName);
}

BasePanel* PanelManager::getPanelById(const std::string &panelName) const
{
  if (isRegistered(panelName)) {
    return p_panelFuncMap.at(panelName)();
  }
  return new BasePanel(panelName);
}
