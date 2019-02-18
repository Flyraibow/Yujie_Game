//
//  InitialSetups.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/17/19.
//

#include "InitialSetups.hpp"
#include "SpecialFunctions.hpp"
#include "EventManager.hpp"

void story::setupForThisGame()
{
  EventManager::getShareInstance()->registerSpecialEventFunction("passDay", &story::passDay);
}
