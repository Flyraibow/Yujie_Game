//
//  PanelManager.hpp
//
//  Created by Yujie Liu on 9/27/18.
//

#ifndef PanelManager_hpp
#define PanelManager_hpp

#include <unordered_map>
#include "BasePanel.hpp"

typedef BasePanel* (*getPanel)();

class PanelManager
{
private:
  static PanelManager* s_sharedManager;
  static std::unordered_map<std::string, getPanel> s_panelFuncMap;
  
public:
  static PanelManager* getShareInstance();
  template <typename T, typename std::enable_if<std::is_base_of<BasePanel, T>::value>::type* = nullptr>
  static void registerPanel(const std::string &panelName) {
    s_panelFuncMap[panelName] = T::createPanel;
  }

  static bool isRegistered(const std::string &panelName);
  
  BasePanel* getPanelById(const std::string &panelName) const;
};


#endif /* PanelManager_hpp */
