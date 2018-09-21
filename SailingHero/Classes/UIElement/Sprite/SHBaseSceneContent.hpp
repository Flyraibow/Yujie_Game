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
};

#endif /* BaseScene_hpp */
