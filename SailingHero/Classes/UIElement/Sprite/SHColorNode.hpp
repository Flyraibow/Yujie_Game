//
//  SHColorNode.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/19/18.
//

#ifndef SHColorNode_hpp
#define SHColorNode_hpp

#include "cocos2d.h"

USING_NS_CC;

/** @class SHColorNode
 * @brief SHColorNode is a subclass of LayerColor that can swallow all touches
 
 */
class SHColorNode : public LayerColor
{
private:
  void commonInit();
  Color4B p_color;
public:
  CREATE_FUNC(SHColorNode);
  /** Creates a Layer with color, width and height in Points.
   *
   * @param color The color of layer.
   * @param width The width of layer.
   * @param height The height of layer.
   * @return An autoreleased LayerColor object.
   */
  static SHColorNode * create(const Color4B& color, GLfloat width, GLfloat height);
  /** Creates a Layer with color. Width and height are the window size.
   *
   * @param color The color of layer.
   * @return An autoreleased LayerColor object.
   */
  static SHColorNode * create(const Color4B& color);
  
  bool init() override;
  bool initWithColor(const Color4B& color);
  bool initWithColor(const Color4B& color, GLfloat w, GLfloat h);
  
  void setColor(const Color4B& color);
};

#endif /* SHColorNode_hpp */

