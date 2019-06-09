//
//  BaseDropDownMenu.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/8/19.
//

#ifndef BaseDropDownMenu_hpp
#define BaseDropDownMenu_hpp

#include "BaseColorNode.hpp"
#include <vector>
#include "ui/UIScrollView.h"

using namespace std;
USING_NS_CC;

// -1 means canceled
typedef std::function<void(int index)> BaseDropDownMenuCallback;

class BaseDropDownMenu : public BaseColorNode {
private:
  // background color
  static BaseDropDownMenu * create(const Color4B& color);
  int p_selectedIndex;
  vector<string> p_selections;
  ui::ScrollView* p_scrollView;
  Color4B p_spriteColor;
  Color4B p_selectedColor;
  Size p_spriteSize;
  const Label* p_exampleLabel;
  float p_maxHeight;
  void selectItem(Touch* touch, Event* event);
  void cancel(Touch* touch, Event* event);
  BaseDropDownMenuCallback p_callback;
public:
  CREATE_FUNC(BaseDropDownMenu);
  void setSelections(const vector<string> &selections);
  void setSelectedIndex(int index);
  void setMaxHeight(float maxHeight) {p_maxHeight = maxHeight;};
  void setDropDownMenuItem(const Size &spriteSize, const Color4B& spriteColor, const Color4B& selectedColor);
  void setDropDownLabel(const Label* exampleLabel);
  void render();
  
  static BaseDropDownMenu * create(BaseDropDownMenuCallback callback);
};

#endif /* BaseDropDownMenu_hpp */
