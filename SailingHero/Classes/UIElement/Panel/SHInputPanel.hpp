//
//  SHInputPanel.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/27/18.
//

#ifndef SHInputPanel_hpp
#define SHInputPanel_hpp

#include "SHPanel.hpp"

class SHInputPanel : public SHPanel
{
public:
  SHInputPanel();
  static SHPanel* createPanel();
  void process();
};

#endif /* SHInputPanel_hpp */
