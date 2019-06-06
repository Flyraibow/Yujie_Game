//
//  DiaryPanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/2/19.
//

#ifndef DiaryPanel_hpp
#define DiaryPanel_hpp

#include "BasePanel.hpp"

class DiaryPanel : public BasePanel
{
private:
public:
  static BasePanel* createPanel();
  DiaryPanel();
  void initialize();
};

#endif /* DiaryPanel_hpp */
