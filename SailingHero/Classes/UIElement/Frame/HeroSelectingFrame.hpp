//
//  HeroSelectingFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/12/18.
//

#ifndef HeroSelectingFrame_hpp
#define HeroSelectingFrame_hpp


#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/** @class SHColorNode
 * @brief SHColorNode is a subclass of LayerColor that can swallow all touches
 
 */
class HeroSelectingFrame
{
public:
  static Sprite* createWithSelectHeroId(const string &selectHeroId);
  static Sprite* createBigPhotoWithSelectHeroId(const string &selectHeroId);
};

#endif /* HeroSelectingFrame_hpp */
