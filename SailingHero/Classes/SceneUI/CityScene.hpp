//
//  CityScene.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/16/18.
//

#ifndef CityScene_hpp
#define CityScene_hpp

#include "SHScene.hpp"
#include "CitySceneFrame.hpp"

USING_NS_CC;

class CityScene : public SHScene
{
private:
  CitySceneFrame p_citySceneFrame;
public:
  static CityScene* createScene();

  virtual bool init();
  
  void setCityDataId(int cityDataId);
  
  // implement the "static create()" method manually
  CREATE_FUNC(CityScene);
};


#endif /* CityScene_hpp */
