//
//  SHLabelComponent.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/22/18.
//

#ifndef SHLabelComponent_hpp
#define SHLabelComponent_hpp

#include "SHComponent.hpp"

class SHLabelComponent : public SHComponent
{
private:
  float p_textSize;
  std::string p_text;
protected:
public:
  SHLabelComponent(nlohmann::json componentJson);
  cocos2d::Node *generateComponent();
};


#endif /* SHLabelComponent_hpp */
