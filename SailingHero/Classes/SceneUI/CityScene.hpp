//
//  CityScene.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/16/18.
//

#ifndef CityScene_hpp
#define CityScene_hpp

#include "SHScene.hpp"
#include "CityDataFrame.hpp"

USING_NS_CC;

class CityScene : public SHScene
{
private:
  CityDataFrame p_cityDataFrame;
public:
  static cocos2d::Scene* createScene();

  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(CityScene);
};


#endif /* CityScene_hpp */
