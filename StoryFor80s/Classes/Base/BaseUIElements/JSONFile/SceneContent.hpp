//
//  SceneContent.hpp
//
//  Created by Yujie Liu on 9/17/18.
//

#ifndef SceneContent_hpp
#define SceneContent_hpp

#include "JSONContent.hpp"
#include "BaseComponent.hpp"

USING_NS_CC;

class SceneContent : public JSONContent
{
public:
  SceneContent(const std::string &jsonFileName);
  std::string getBackgroundImage() const;
  std::string getBackgroundMusic() const;
  std::string getInitialEvent() const;
  std::string getAddOnEvent() const;
  bool isFullScreenCover() const;
  Size getScreenCoverRatio() const;
  
  std::vector<BaseComponent *> getComponentList() const;
};

#endif /* BaseScene_hpp */
