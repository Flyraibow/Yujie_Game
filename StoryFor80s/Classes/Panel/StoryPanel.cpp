//
//  StoryPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/2/19.
//

#include "StoryPanel.hpp"
#include "PlotData.hpp"
#include "GameData.hpp"

vector<PlotData *> findPlotsInThisMonth()
{
  auto currentDate = GameData::getSharedInstance()->getGameDateData();
  auto currentDateValue = currentDate->getYear() * 10000+currentDate->getMonth() * 100 + currentDate->getDay();
  auto nextDateValue = currentDateValue + 100;
  auto allPlots = PlotData::getSharedDictionary();
  vector<PlotData *> results;
  for(auto it = allPlots->begin(); it != allPlots->end(); ++it) {
    auto plot = it->second;
    if (plot->getExperienced() && plot->getRepeatable()) {
      continue;
    }
    // TODO: Add condition check
    auto plotDate = plot->getDateData();
    if (plotDate == nullptr) {
      results.push_back(plot);
    } else {
      auto dateValue = plotDate->getYear() * 10000+plotDate->getMonth() * 100 + plotDate->getDay();
      if (dateValue >= currentDateValue && dateValue < nextDateValue) {
        results.push_back(plot);
      }
    }
  }
  return results;
}

BasePanel* StoryPanel::createPanel()
{
  return new StoryPanel();
}

StoryPanel::StoryPanel() : BasePanel("storyPanel")
{
}

void StoryPanel::initialize()
{
  // TODO: 1. collect what will happen during this period of time
  // 2. start to deal with the scenario 1 by 1
  auto plots = findPlotsInThisMonth();
  auto labDescriptionText = getComponentById<Label>("lab_text");
  if (plots.size() > 0) {
    auto plot = plots.at(0);
    labDescriptionText->setString(plot->getText());
  }
}
