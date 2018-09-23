//
//  SHButtonComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/23/18.
//

#ifndef SHButtonComponent_hpp
#define SHButtonComponent_hpp

#include "SHComponent.hpp"

class SHButtonComponent : public SHComponent
{
private:
  float p_textSize;
  std::string p_text;
  std::string p_eventId;
protected:
public:
  SHButtonComponent(nlohmann::json componentJson);
  cocos2d::Node *generateComponent();
};


#endif /* SHButtonComponent_hpp */
