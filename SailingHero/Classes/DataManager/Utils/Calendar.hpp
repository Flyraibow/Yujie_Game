//
//  Calendar.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/21/18.
//

#ifndef Calendar_hpp
#define Calendar_hpp

#include <stdio.h>
#include "GameData.hpp"

struct Date
{
  int year;
  int month;
  int day;
  Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
  }
};

bool isDateValid(int month, int day, int year = 1);

int howManyDaysInMonth(int month, int year = 1);

struct Date nextDay(int y, int m, int d);
struct Date nextNDays(int y, int m, int d, int n);


#endif /* Calendar_hpp */
