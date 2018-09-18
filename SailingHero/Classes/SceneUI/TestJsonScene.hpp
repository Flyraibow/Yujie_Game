//
//  TestJsonScene.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/17/18.
//

#ifndef TestJsonScene_hpp
#define TestJsonScene_hpp

#include "SHScene.hpp"

class TestJsonScene : public SHScene
{
private:
public:
  static TestJsonScene* createScene();
  
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(TestJsonScene);
};

#endif /* TestJsonScene_hpp */
