//
//  StoryScene.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/13/18.
//

#ifndef StoryScene_hpp
#define StoryScene_hpp

#include "SHScene.hpp"

class StoryScene : public SHScene
{
private:
public:
  static StoryScene* createScene();
  
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(StoryScene);
};

#endif /* StoryScene_hpp */
