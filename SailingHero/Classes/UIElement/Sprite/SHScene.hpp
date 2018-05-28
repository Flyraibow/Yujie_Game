//
//  SHScene.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/27/18.
//

#ifndef SHScene_hpp
#define SHScene_hpp

#include "cocos2d.h"

USING_NS_CC;

#define SCREEN_COVER_LAYER_HEIGHT 100
//#define COVER_DEBUG

class SHScene : public cocos2d::Scene
{
protected:
    /** Set a screen cover to make screen the same ratio of ratioSize
     *
     * @param ratioSize  The desired screen ratio, e.g. (4, 3), (16, 9);
     */
    void setScreenCover(Size ratioSize);
public:
    CREATE_FUNC(SHScene);
};

#endif /* SHScene_hpp */
