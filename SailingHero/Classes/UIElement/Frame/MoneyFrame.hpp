//
//  MoneyFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/28/18.
//

#ifndef MoneyFrame_hpp
#define MoneyFrame_hpp

#include "cocos2d.h"
#include "SHBaseFrame.hpp"
#include "GuildData.hpp"

USING_NS_CC;
using namespace std;

class MoneyFrame : public SHBaseFrame
{
private:
  GuildData* p_guildData;
  Label* p_labMoney;
protected:
  virtual Node* genSprite(double scale);
public:
  MoneyFrame();
  void setGuildDataId(int guildId);
  void setGuildData(GuildData *guildData);
  void refresh();
};



#endif /* MoneyFrame_hpp */
