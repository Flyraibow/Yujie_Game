//
//  SHButtonComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/23/18.
//

#ifndef SHButtonComponent_hpp
#define SHButtonComponent_hpp

#include "SHComponent.hpp"
USING_NS_CC;

class SHButtonComponent : public SHComponent
{
private:
  float p_textSize;
  std::string p_text;
  std::string p_eventId;
protected:
public:
  SHButtonComponent(nlohmann::json componentJson);
  Node *addComponentToParent(unordered_map<string, Node *> &dict, Node *parent = nullptr) const;
};


#endif /* SHButtonComponent_hpp */
