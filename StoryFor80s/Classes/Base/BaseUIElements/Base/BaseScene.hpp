//
//  BaseScene.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "cocos2d.h"
#include "SceneContent.hpp"
#include "PanelContent.hpp"
#include "BasePanel.hpp"

#include <unordered_map>
#include <stack>

USING_NS_CC;

#define SCREEN_COVER_LAYER_HEIGHT 100
#define SCREEN_FOREGROUND_LAYER_HEIGHT 101
#define COVER_DEBUG

class DialogFrame;

class BaseScene : public cocos2d::Scene
{
private:
  Node* s_background;
  Node* s_foreground;
  Size s_screenSize;
  bool s_isFullScreen;
  std::string p_backgroundMusic;
protected:
  /** Set a screen cover to make screen the same ratio of ratioSize
   *
   * @param ratioSize  The desired screen ratio, e.g. (4, 3), (16, 9);
   */
  void setScreenCover(Size ratioSize);
  void setFullScreenCover();
  void setBackgroundImage(const std::string &imgPath);
  void setForegroundImage(const std::string &imgPath);
  void setBackgroundMusic(const std::string &path);
  Node* s_window;
  
  ComponentDict p_componentDict;
  std::stack<BasePanel *> p_panelStack;
  
  void initSceneWithJson(const std::string &jsonFileName);
  
public:
  static BaseScene* createScene(const string &jsonFile);
  CREATE_FUNC(BaseScene);
  virtual bool init();
  virtual void refreBaseScene();
  void refreshMusic();
  Size getScreenSize() const;
  Node* getBackground();
  
  void addPanelWithParameters(BasePanel *panel);
  void popPanel();
  void addDialogFrame(DialogFrame* dialog);
  BasePanel* topPanel () const;
  
  template <typename T, typename std::enable_if<std::is_base_of<Node, T>::value>::type* = nullptr>
  T* getComponentById(const std::string &componentId) {
    CCASSERT(p_componentDict.count(componentId), ("Coudn't find component id : " + componentId).c_str());
    return static_cast<T*>(p_componentDict.at(componentId));
  }
};

#endif /* BaseScene_hpp */