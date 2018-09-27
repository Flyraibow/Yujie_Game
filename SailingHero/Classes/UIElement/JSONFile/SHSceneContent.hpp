//
//  SHSceneContent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/17/18.
//

#ifndef SHSceneContent_hpp
#define SHSceneContent_hpp

#include "SHJSONContent.hpp"

USING_NS_CC;

class SHSceneContent : public SHJSONContent
{
public:
  SHSceneContent(const std::string &jsonFileName);
  std::string getBackgroundImage() const;
  std::string getBackgroundMusic() const;
  std::string getInitialEvent() const;
  bool isFullScreenCover() const;
  Size getScreenCoverRatio() const;
  
};

#endif /* BaseScene_hpp */
