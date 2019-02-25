//
//  BaseColorNode.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#ifndef BaseColorNode_hpp
#define BaseColorNode_hpp

#include "cocos2d.h"

USING_NS_CC;

/** @class BaseColorNode
 * @brief BaseColorNode is a subclass of LayerColor that can swallow all touches
 
 */
class BaseColorNode : public LayerColor
{
private:
  void commonInit();
  Color4B p_color;
public:
  CREATE_FUNC(BaseColorNode);
  /** Creates a Layer with color, width and height in Points.
   *
   * @param color The color of layer.
   * @param width The width of layer.
   * @param height The height of layer.
   * @return An autoreleased LayerColor object.
   */
  static BaseColorNode * create(const Color4B& color, GLfloat width, GLfloat height);
  /** Creates a Layer with color. Width and height are the window size.
   *
   * @param color The color of layer.
   * @return An autoreleased LayerColor object.
   */
  static BaseColorNode * create(const Color4B& color);
  
  bool init() override;
  bool initWithColor(const Color4B& color);
  bool initWithColor(const Color4B& color, GLfloat w, GLfloat h);
};

#endif /* BaseColorNode_hpp */
