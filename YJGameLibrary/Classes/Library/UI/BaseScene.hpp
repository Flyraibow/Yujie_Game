//
//  BaseScene.hpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "cocos2d.h"
#include "json.hpp"
#include <vector>

USING_NS_CC;

using namespace std;

class BaseScene : public Scene
{
protected:
  vector<Node *> p_components;
public:
  static Scene* createScene(string jsonSceneFile);
  bool initWithJson(const nlohmann::json& json);
  CREATE_FUNC(BaseScene);
  void setBackgroundMusic(const string &path);
};

#endif /* BaseScene_hpp */
