//
//  PanelManager.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/27/18.
//

#ifndef PanelManager_hpp
#define PanelManager_hpp

#include <unordered_map>
#include "SHPanel.hpp"

typedef SHPanel* (*getPanel)();

class PanelManager
{
private:
  static PanelManager* p_sharedManager;
  std::unordered_map<std::string, getPanel> p_panelFuncMap;
  
  template <typename T, typename std::enable_if<std::is_base_of<SHPanel, T>::value>::type* = nullptr>
  void registerPanel(const std::string &panelName);
  bool isRegistered(const std::string &panelName) const;
public:
  static PanelManager* getShareInstance();
  SHPanel* getPanelById(const std::string &panelName) const;
};


#endif /* PanelManager_hpp */
