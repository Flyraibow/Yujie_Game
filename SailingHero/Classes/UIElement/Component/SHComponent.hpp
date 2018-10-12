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
#include <unordered_map>

using namespace std;
USING_NS_CC;

class SHComponent;

typedef std::unordered_map<string, SHComponent *> ComponentDict;

class SHComponent
{
private:
protected:
  string p_type;
  string p_id;
  bool p_isAutoScale;
  Vec2 p_normalizePosition;
  Vec2 p_anchorPoint;
  nlohmann::json p_size;
  Node* p_node;
  float p_scale;
  
  vector<SHComponent *> p_componentList;
  Size getComponentSize(Node *parent) const;
public:
  SHComponent(const nlohmann::json &componentJson);
  virtual ~SHComponent() {};
  void addNodeToParent(ComponentDict &dict, Node *child, Node *parent);
  virtual Node *addComponentToParent(ComponentDict &dict, Node *parent = nullptr) = 0;
  string getId() const;
  virtual void refresh() {};
  Node* getNode() {return p_node;};
  
  /**
   * It will create real component by type
   */
  static SHComponent* getComponentFromJson(const nlohmann::json &componentJson);
  static vector<SHComponent *> getComponentsFromJson(const nlohmann::json &componentJson);
};

#endif /* SHComponent_hpp */
