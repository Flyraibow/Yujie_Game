//
//  GoodsData.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef GoodsData_hpp
#define GoodsData_hpp

#include <stdio.h>

using namespace std;

class GoodsData
{
private:
  string p_id;
  string p_name;
  int p_price;
public:
  GoodsData(const string &id);
  string getId() const {return p_id;};
  string getName() const {return p_name;};
  int getPrice() const {return p_price;};
};

#endif /* GoodsData_hpp */
