//
//  InteractionPanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/23/19.
//

#ifndef InteractionPanel_hpp
#define InteractionPanel_hpp

#include "BasePanel.hpp"
#include "StoryEventContent.hpp"
#include "DialogEventContent.hpp"
#include <vector>

using namespace std;

class InteractionPanel : public BasePanel
{
private:
public:
  static BasePanel* createPanel();
  InteractionPanel();
};


#endif /* InteractionPanel_hpp */
