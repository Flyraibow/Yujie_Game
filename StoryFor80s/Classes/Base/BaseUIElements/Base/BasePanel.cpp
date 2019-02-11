//
//  BasePanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#include "BasePanel.hpp"

BasePanel::BasePanel(const std::string &panelName)
{
  p_node = nullptr;
  p_panelName = panelName;
  auto panelContent = new PanelContent(panelName);
  p_component = panelContent->getComponent();
  delete panelContent;
}

BasePanel::~BasePanel()
{
  delete p_component;
}

std::string BasePanel::getPanelName() const
{
  return p_panelName;
}

Node* BasePanel::addToParent(Node *parent)
{
  CCASSERT(p_node == nullptr, "Need remove it before regenerate it");
  p_node = p_component->addComponentToParent(p_componentDict, parent);
  return p_node;
}

void BasePanel::removeFromParent()
{
  p_node->removeFromParent();
  p_node = nullptr;
}
