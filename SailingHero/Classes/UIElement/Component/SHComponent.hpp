//
//  SHComponent.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/22/18.
//

#ifndef SHComponent_hpp
#define SHComponent_hpp

#include "cocos2d.h"
#include "json.hpp"

#include <vector>

using namespace std;

class SHComponent
{
private:
protected:
  std::string p_type;
  std::string p_id;
  cocos2d::Vec2 p_normalizePosition;
  cocos2d::Vec2 p_anchorPoint;
public:
  SHComponent(const nlohmann::json &componentJson);
  virtual cocos2d::Node *generateComponent() = 0;
  std::string getId() const;
  
  /**
   * It will create real component by type
   */
  static SHComponent* getComponentFromJson(const nlohmann::json &componentJson);
  static vector<SHComponent *> getComponentsFromJson(const nlohmann::json &componentJsonList);
};

#endif /* SHComponent_hpp */
