//
//  LevelManager.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/27/19.
//

#include "LevelManager.hpp"
#include "JSONContent.hpp"

using namespace std;

vector<SimpleLevelData *> getAllLevelInfo()
{
  vector<SimpleLevelData *> levels;
  auto fileUtils = cocos2d::FileUtils::getInstance();
  vector<string> files = fileUtils->listFiles(LEVEL_FILE_FOLDER);
  for (auto file : files) {
    if (fileUtils->getFileExtension(file) == ".json") {
      auto j = JSONContent::loadJsonFromPath(file);
      auto levelData = new SimpleLevelData(j);
      levels.push_back(levelData);
    }
  }
  return levels;
}
