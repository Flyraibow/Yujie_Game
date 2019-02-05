//
//  SailMapScene.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#ifndef SailMapScene_hpp
#define SailMapScene_hpp

#include "SHScene.hpp"
#include "SailMapFrame.hpp"

class SailMapScene : public SHScene
{
private:
  SailMapFrame p_sailMapFrame;
public:
  static SHScene* createScene();
  
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(SailMapScene);
};

#endif /* SailMapScene_hpp */
