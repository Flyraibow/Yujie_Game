//
//  InteractionPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/23/19.
//

#include "InteractionPanel.hpp"

BasePanel* InteractionPanel::createPanel()
{
  return new InteractionPanel();
}

InteractionPanel::InteractionPanel() : BasePanel("interactionPanel")
{
}
