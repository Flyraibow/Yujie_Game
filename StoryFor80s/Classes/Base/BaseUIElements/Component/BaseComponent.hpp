//
//  BaseComponent.hpp
//
//  Created by Yujie Liu on 9/22/18.
//

#ifndef BaseComponent_hpp
#define BaseComponent_hpp

#include "cocos2d.h"
#include "json.hpp"

#include <vector>
#include <unordered_map>

using namespace std;
USING_NS_CC;

class BaseComponent;
class BaseData;

typedef std::unordered_map<string, BaseComponent *> ComponentDict;

class BaseComponent
{
private:
protected:
  string p_type;
  string p_id;
  bool p_isAutoScale;
  bool p_isParentScale;
  Vec2 p_normalizePosition;
  Vec2 p_normalizePositionOffset;
  Vec2 p_position;
  Vec2 p_positionOffset;
  Vec2 p_anchorPoint;
  nlohmann::json p_size;
  Node* p_node;
  float p_scale;
  bool p_isFullScreen;
  BaseData *p_associateData;
  string p_shouldHideCondition;
  int p_index;
  
  vector<BaseComponent *> p_componentList;
  Size getComponentSize(Node *parent) const;
  string decipherValue(const string &value) const;
  Vec2 getVec2FromStringVec2(const vector<string> &list) const;
public:
  BaseComponent(const nlohmann::json &componentJson);
  virtual ~BaseComponent() {};
  void addNodeToParent(ComponentDict &dict, Node *child, Node *parent);
  virtual Node *addComponentToParent(ComponentDict &dict, Node *parent = nullptr) = 0;
  string getId() const;
  virtual void refresh();
  Node* getNode() {return p_node;};
  void setIndex(int index);
  
  /**
   * It will create real component by type
   */
  static BaseComponent* getComponentFromJson(const nlohmann::json &componentJson);
  static vector<BaseComponent *> getComponentsFromJson(const nlohmann::json &componentJson);

  virtual void copyAttributesFromJson(const nlohmann::json &componentJson);
  void setAssociateData(BaseData *baseData) { p_associateData = baseData; };
};

#endif /* BaseComponent_hpp */
