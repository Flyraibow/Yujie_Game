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

using namespace std;

class StoryPanel : public BasePanel
{
private:
public:
  static BasePanel* createPanel();
  StoryPanel();
  void initialize();
};

#endif /* StoryPanel_hpp */
