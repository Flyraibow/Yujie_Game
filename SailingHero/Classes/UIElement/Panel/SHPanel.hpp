//
//  SHPanel.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/27/18.
//

#ifndef SHPanel_hpp
#define SHPanel_hpp

#include "cocos2d.h"
#include "SHPanelContent.hpp"
#include <unordered_map>

USING_NS_CC;

class SHPanel
{
protected:
  std::string p_panelName;
  SHComponent* p_component;
  ComponentDict p_componentDict;
  Node* p_node;
  
public:
  SHPanel(const std::string &panelName);
  ~SHPanel();
  std::string getPanelName() const;
  virtual void initialize() {};
  virtual void referesh() {};
  virtual void process() {};
  Node* addToParent(Node *parent);
  void removeFromParent();
  
  template <typename T, typename std::enable_if<std::is_base_of<Node, T>::value>::type* = nullptr>
  T* getComponentById(const std::string &componentId) {
    CCASSERT(p_componentDict.count(componentId), ("Coudn't find component id : " + componentId).c_str());
    auto component = p_componentDict.at(componentId);
    return static_cast<T*>(component->getNode());
  }
};

#endif /* SHPanel_hpp */