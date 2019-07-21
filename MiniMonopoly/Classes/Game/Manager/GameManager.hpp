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

class GameManager
{
private:
  LevelData* p_levelData;
  
public:
  GameManager(const string &levelId);
};

#endif /* GameManager_hpp */
