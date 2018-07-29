//
//  MoneyFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/28/18.
//

#ifndef MoneyFrame_hpp
#define MoneyFrame_hpp

#include "cocos2d.h"
#include "GuildData.hpp"

USING_NS_CC;
using namespace std;

class MoneyFrame
{
private:
  Node* p_sprite;
  GuildData* p_guildData;
  Label* p_labMoney;
public:
  MoneyFrame();
  void setGuildDataId(int guildId);
  void setGuildData(GuildData *guildData);
  void refresh();
  Node* getSprite() const;
};



#endif /* MoneyFrame_hpp */
