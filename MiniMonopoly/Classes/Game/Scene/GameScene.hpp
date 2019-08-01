//
//  GameScene.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

USING_NS_CC;
class TeamData;

class GameManager;

class GameScene : public cocos2d::Scene
{
private:
  GameManager* p_gameManager;
  Sprite* p_map;
  Label* p_myGuildMoney;
  Label* p_speedLab;
  MenuItemLabel* p_speedMenuItem;
  
  void showCitiesOnMap();
  void updateTeamsOnMap();
  
  void clickSystem(cocos2d::Ref* pSender);
  void clickSpeed(cocos2d::Ref* pSender);
public:
  ~GameScene();
  static GameScene* createScene(const std::string &levelId);
  
  bool initWithLevelId(const std::string &levelId);
  
  void popScene(cocos2d::Ref* pSender);
  
  void addTeamOnMap(TeamData* teamData);
  void updateMyGuildMoney();
  
  static GameScene* getGameScene();
  
  CREATE_FUNC(GameScene);
};

#endif /* GameScene_hpp */
