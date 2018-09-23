//
//  SHBaseSceneContent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/17/18.
//

#ifndef SHBaseSceneContent_hpp
#define SHBaseSceneContent_hpp

#include "cocos2d.h"
#include "json.hpp"
#include "SHComponent.hpp"
#include <vector>

USING_NS_CC;

class SHBaseSceneContent
{
private:
  nlohmann::json p_jsonContent;
public:
  static SHBaseSceneContent* loadContentFromPath(std::string jsonFilePath);
  
  std::string getBackgroundImage();
  std::string getBackgroundMusic();
  std::string getInitialEvent();
  bool isFullScreenCover();
  Size getScreenCoverRatio();
  std::vector<SHComponent *> getComponentList();
  
};

#endif /* BaseScene_hpp */
