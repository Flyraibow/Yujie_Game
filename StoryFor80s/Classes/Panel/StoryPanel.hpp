//
//  StoryPanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/2/19.
//

#ifndef StoryPanel_hpp
#define StoryPanel_hpp

#include "BasePanel.hpp"
#include <vector>

class PlotData;
class ExamListData;
class BaseButton;

using namespace std;

class StoryPanel : public BasePanel
{
private:
  vector<PlotData *> p_plots;
  vector<ExamListData *> p_examLists;
  vector<BaseButton *> p_tempButtons;
  int p_currentPlotIndex = 0;
  int p_currentExamIndex = 0;
  void nextPlot();
  void startPlot(PlotData* plot);
  void completePlotText(PlotData* plot);
  void clearTempButtons();
  
  void initializeExam();
  void nextExam();
  void startExam(ExamListData* examList);
  void completeExamText(ExamListData* examList);

public:
  static BasePanel* createPanel();
  StoryPanel();
  void initialize();
};

#endif /* StoryPanel_hpp */
