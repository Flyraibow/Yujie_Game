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

class SHColorNode : public LayerColor
{
protected:
    EventListenerTouchOneByOne* s_touchListener;
public:
    static SHColorNode* create();
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
    void setTouchesEnabled(bool enabled);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
};

#endif /* SHColorNode_hpp */
