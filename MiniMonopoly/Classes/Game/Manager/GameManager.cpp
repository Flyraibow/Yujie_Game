//
//  GameManager.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "GameManager.hpp"
#include "LevelData.hpp"


GameManager* GameManager::p_sharedInstance = nullptr;

GameManager* GameManager::getSharedInstance()
{
  if (!p_sharedInstance) {
    p_sharedInstance = new GameManager();
  }
  return p_sharedInstance;
}

GameManager::GameManager()
{
  p_levelData = nullptr;
}

void GameManager::clear()
{
  if (p_levelData != nullptr) {
    delete p_levelData;
    p_levelData = nullptr;
  }
}

GameManager* GameManager::setLevelId(const string &levelId)
{
  clear();
  p_levelData = new LevelData(levelId);
  p_gameSpeed = 1;
  return this;
}

GameManager::~GameManager()
{
  clear();
}


void GameManager::restartLevel()
{
  
}
