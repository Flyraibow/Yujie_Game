//
//  SHButtonComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/23/18.
//

#ifndef SHButtonComponent_hpp
#define SHButtonComponent_hpp

#include "SHComponent.hpp"
#include <unordered_map>
USING_NS_CC;
using namespace std;

class SHButtonComponent : public SHComponent
{
private:
  float p_textSize;
  std::string p_text;
  std::string p_eventId;
  std::string p_imagePath;
  unordered_map<string, string> p_setTempStrDict;
protected:
public:
  SHButtonComponent(nlohmann::json componentJson);
  Node *addComponentToParent(ComponentDict &dict, Node *parent = nullptr);
  virtual void refresh();
};


#endif /* SHButtonComponent_hpp */
