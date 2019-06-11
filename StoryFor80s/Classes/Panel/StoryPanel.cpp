//
//  StoryPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/2/19.
//

#include "StoryPanel.hpp"
#include "PlotData.hpp"
#include "GameData.hpp"
#include "BaseLabel.hpp"
#include "BaseButton.hpp"
#include "SceneManager.hpp"
#include "ConditionManager.hpp"
#include "StoryManager.hpp"
#include "DiaryPanel.hpp"
#include "ExamListData.hpp"
#include "ExamFunctions.hpp"

struct sort_plot_by_priority
{
  inline bool operator() (const PlotData *plot1, const PlotData *plot2)
  {
    return (plot1->getPriority() < plot2->getPriority());
  }
};

struct sort_exam_by_priority
{
  inline bool operator() (const ExamListData *examList1, const ExamListData *examList2)
  {
    return (examList1->getPriority() < examList2->getPriority());
  }
};

vector<PlotData *> findPlotsInThisMonth()
{
  auto currentDate = GameData::getSharedInstance()->getGameDateData();
  auto allPlots = PlotData::getSharedDictionary();
  vector<PlotData *> results;
  for(auto it = allPlots->begin(); it != allPlots->end(); ++it) {
    auto plot = it->second;
    if (plot->getExperienced() && plot->getRepeatable()) {
      continue;
    }
    if (!Manager::checkConditionByString(plot->getCondition())) {
      continue;
    }
    auto plotYear = plot->getYear();
    if (plotYear == 0) {
      results.push_back(plot);
    } else {
      if (currentDate->getYear() == plotYear && currentDate->getMonth() == plot->getMonth()) {
        results.push_back(plot);
      }
    }
  }
  sort(results.begin(), results.end(), sort_plot_by_priority());
  return results;
}

vector<ExamListData *> findExamListInThisMonth()
{
  auto currentDate = GameData::getSharedInstance()->getGameDateData();
  auto allExamLists = ExamListData::getSharedDictionary();
  vector<ExamListData *> results;
  for(auto it = allExamLists->begin(); it != allExamLists->end(); ++it) {
    auto examList = it->second;
    if (!Manager::checkConditionByString(examList->getCondition())) {
      continue;
    }
    if (examList->getSchoolId() != GameData::getSharedInstance()->getSchoolId()) {
      continue;
    }
    auto plotYear = examList->getYear();
    if (plotYear == 0) {
      results.push_back(examList);
    } else {
      if (currentDate->getYear() == plotYear && currentDate->getMonth() == examList->getMonth()) {
        results.push_back(examList);
      }
    }
  }
  sort(results.begin(), results.end(), sort_exam_by_priority());
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
  // 1. collect what will happen during this period of time
  // 2. start to deal with the scenario 1 by 1
  p_plots = findPlotsInThisMonth();
  p_currentPlotIndex = 0;
  nextPlot();
}

void StoryPanel::nextPlot()
{
  if (p_plots.size() > p_currentPlotIndex) {
    auto plot = p_plots.at(p_currentPlotIndex);
    p_currentPlotIndex++;
    startPlot(plot);
  } else {
    initializeExam();
  }
}

void StoryPanel::startPlot(PlotData *plot)
{
  auto labDescriptionText = getComponentById<BaseLabel>("lab_text");
  auto button = this->getComponentById<BaseButton>("button_next");
  button->setVisible(false);
  labDescriptionText->setString(plot->getText());
  labDescriptionText->setCallback([this, plot](){
    this->completePlotText(plot);
  });
}


void StoryPanel::completePlotText(PlotData *plot)
{
  auto button = this->getComponentById<BaseButton>("button_next");
  auto selections = plot->getSelection_text();
  if (selections.size() == 0) {
    // 简单事件
    button->setVisible(true);
    button->setClickEventListener([this](cocos2d::Ref *pSender) {
      this->nextPlot();
    });
  } else {
    // 多选事件
    auto sprite = this->getComponentById<Sprite>("story_panel");
    for (int i = 0; i < selections.size(); ++i) {
      auto select = selections.at(i);
      auto baseButton = BaseButton::defaultButtonWithText(select);
      baseButton->setAnchorPoint(Vec2(0.5, 0.5));
      baseButton->setNormalizedPosition(Vec2(0.5 + (i - selections.size() / 2.0) * 0.1,0.05));
      p_tempButtons.push_back(baseButton);
      sprite->addChild(baseButton);
      
      if (plot->getSelection_plotDataVector().size() > i && plot->getSelection_plotDataVector().at(i) != nullptr) {
        auto select_plot = plot->getSelection_plotDataVector().at(i);
        baseButton->setClickEventListener([this, select_plot](cocos2d::Ref *pSender) {
          this->clearTempButtons();
          this->startPlot(select_plot);
        });
      } else if (plot->getSelection_event().size() > i && plot->getSelection_event().at(i).length() > 0) {
        auto event = plot->getSelection_event().at(i);
        baseButton->setClickEventListener([this, event](cocos2d::Ref *pSender) {
          StoryManager::getShareInstance()->startStory(event);
        });
      } else {
        baseButton->setClickEventListener([this](cocos2d::Ref *pSender) {
          this->clearTempButtons();
          this->nextPlot();
        });
      }
    }
  }
}

void StoryPanel::clearTempButtons()
{
  for (auto button : p_tempButtons) {
    button->removeFromParent();
  }
  p_tempButtons.clear();
}


void StoryPanel::initializeExam()
{
  p_examLists = findExamListInThisMonth();
  p_currentExamIndex = 0;
  nextExam();
}

void StoryPanel::nextExam()
{
  if (p_examLists.size() > p_currentExamIndex) {
    auto examList = p_examLists.at(p_currentExamIndex);
    p_currentExamIndex++;
    startExam(examList);
  } else {
    SceneManager::getShareInstance()->popPanel();
    // 打开diarypanel
    SceneManager::getShareInstance()->addPanel("diaryPanel");
  }
}

void StoryPanel::startExam(ExamListData* examList)
{
  auto labDescriptionText = getComponentById<BaseLabel>("lab_text");
  auto button = this->getComponentById<BaseButton>("button_next");
  button->setVisible(false);
  labDescriptionText->setString(game::startExam(examList));
  labDescriptionText->setCallback([this, examList](){
    this->completeExamText(examList);
  });
}

void StoryPanel::completeExamText(ExamListData* examList)
{
  auto button = this->getComponentById<BaseButton>("button_next");
  button->setVisible(true);
  button->setClickEventListener([this](cocos2d::Ref *pSender) {
    this->nextExam();
  });
}
