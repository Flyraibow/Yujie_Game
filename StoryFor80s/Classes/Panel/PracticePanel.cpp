//
//  PracticePanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/5/19.
//

#include "PracticePanel.hpp"

BasePanel* PracticePanel::createPanel()
{
  return new PracticePanel();
}

PracticePanel::PracticePanel() : BasePanel("practicePanel")
{
}

void PracticePanel::initialize()
{
}
