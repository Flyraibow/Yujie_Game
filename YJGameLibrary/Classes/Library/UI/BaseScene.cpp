//
//  BaseScene.cpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#include "BaseScene.hpp"
#include "JSONContent.hpp"
#include "SceneJsonStruct.h"
#include "audio/include/SimpleAudioEngine.h"
#include "ComponentGenerator.hpp"

cocos2d::Scene* BaseScene::createScene(std::string jsonSceneFile)
{
  auto scene = BaseScene::create();
  auto jsonContent = new JSONContent(jsonSceneFile);
  scene->initWithJson(jsonContent->getContent());
  return scene;
}

bool BaseScene::initWithJson(const nlohmann::json& json)
{
  auto sceneStruct = new SceneJsonStruct(json);
  setBackgroundMusic(sceneStruct->backgroundMusic);
  //
  for (auto nodeStruct : sceneStruct->componentStructs) {
    createNodeFromJsonStruct(nodeStruct, this);
  }
  delete sceneStruct;
  return true;
}

void BaseScene::setBackgroundMusic(const std::string &path)
{
  if (path.length() == 0) {
    return;
  }
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->stopBackgroundMusic();
  audio->playBackgroundMusic(path.c_str(), true);
}
