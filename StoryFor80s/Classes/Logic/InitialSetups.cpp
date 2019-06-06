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
#include "BaseGlobalDataManager.hpp"
#include "DialogPanel.hpp"
#include "StoryPanel.hpp"
#include "DiaryPanel.hpp"

void story::setupForThisGame()
{
  BaseGlobalDataManager::loadData("global");
  StoryManager::registerSpecialEventFunction("passDay", &story::passDay);
  StoryManager::registerSpecialEventFunction("home", &game::homePage);
  StoryManager::registerSpecialEventFunction("save", &game::save);
  StoryManager::registerSpecialEventFunction("load", &game::load);
  PanelManager::registerPanel<DialogPanel>("dialogPanel");
  PanelManager::registerPanel<StoryPanel>("storyPanel");
  PanelManager::registerPanel<DiaryPanel>("diaryPanel");
}
