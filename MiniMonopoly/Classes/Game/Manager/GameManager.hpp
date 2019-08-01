//
//  GameManager.hpp
//  MiniMonopoly
//  游戏管理，负责管理每一局的游戏
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include "LevelData.hpp"

class GameScene;

class GameManager
{
private:
  static GameManager* p_sharedInstance;
  LevelData* p_levelData;
  int p_gameSpeed;
  bool p_paused;
  void clear();
public:
  static GameManager* getSharedInstance();
  GameManager();
  ~GameManager();
  
  GameManager* setLevelId(const string& levelId);
  
  LevelData* getLevelData() const {return p_levelData;};
  void setGameSpeed(int speed) {p_gameSpeed = speed;};
  int getGameSpeed() const {return p_gameSpeed;};
  
  void setPaused(bool isPaused) {p_paused = isPaused;};
  bool isPaused() const {return p_paused;};
  void restartLevel();
};

#endif /* GameManager_hpp */
