//
//  BasePanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#ifndef BasePanel_hpp
#define BasePanel_hpp

#include "cocos2d.h"
#include "PanelContent.hpp"
#include <unordered_map>

USING_NS_CC;

class BasePanel
{
protected:
  std::string p_panelName;
  BaseComponent* p_component;
  ComponentDict p_componentDict;
  Node* p_node;
  
public:
  BasePanel(const std::string &panelName);
  ~BasePanel();
  std::string getPanelName() const;
  virtual void initialize() {};
  virtual void referesh();
  virtual void process() {};
  Node* addToParent(Node *parent);
  void removeFromParent();
  
  template <typename T, typename std::enable_if<std::is_base_of<Node, T>::value>::type* = nullptr>
  T* getComponentById(const std::string &componentId) {
    CCASSERT(p_componentDict.count(componentId), ("Coudn't find component id : " + componentId).c_str());
    auto component = p_componentDict.at(componentId);
    return static_cast<T*>(component->getNode());
  }
  void refreshComponentById(const string &componentId);
};

#endif /* BasePanel_hpp */
