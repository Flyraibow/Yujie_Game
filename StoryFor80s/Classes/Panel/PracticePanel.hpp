//
//  PracticePanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/5/19.
//

#ifndef PracticePanel_hpp
#define PracticePanel_hpp

#include "BasePanel.hpp"

class PracticePanel : public BasePanel
{
private:
public:
  static BasePanel* createPanel();
  PracticePanel();
  void initialize();
};

#endif /* PracticePanel_hpp */
