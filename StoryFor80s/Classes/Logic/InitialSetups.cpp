//
//  InitialSetups.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/17/19.
//

#include "InitialSetups.hpp"
#include "SpecialFunctions.hpp"
#include "StoryManager.hpp"
#include "PanelManager.hpp"
#include "DialogPanel.hpp"

void story::setupForThisGame()
{
  StoryManager::registerSpecialEventFunction("passDay", &story::passDay);
  PanelManager::registerPanel<DialogPanel>("dialogPanel");
  PanelManager::isRegistered("dialogPanel");
}
