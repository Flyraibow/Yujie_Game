//
//  SHPanel.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/27/18.
//

#include "SHPanel.hpp"


SHPanel::SHPanel(const std::string &panelName)
{
  p_node = nullptr;
  p_panelName = panelName;
  auto panelContent = new SHPanelContent(panelName);
  p_component = panelContent->getComponent();
  delete panelContent;
}

SHPanel::~SHPanel()
{
  delete p_component;
}

std::string SHPanel::getPanelName() const
{
  return p_panelName;
}

Node* SHPanel::addToParent(Node *parent)
{
  CCASSERT(p_node == nullptr, "Need remove it before regenerate it");
  p_node = p_component->addComponentToParent(p_componentDict, parent);
  return p_node;
}

void SHPanel::removeFromParent()
{
  p_node->removeFromParent();
  p_node = nullptr;
}
