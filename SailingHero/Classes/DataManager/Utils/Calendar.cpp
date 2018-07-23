//
//  Calendar.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/21/18.
//

#include "Calendar.hpp"


bool isDateValid(int month, int day, int year)
{
  if (month < 1 || month > 12 || day < 1) {
    return false;
  }
  return howManyDaysInMonth(month, year) >= day;
}

int howManyDaysInMonth(int month, int year)
{
  switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      return 31;
    case 2:
      if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
        return 29;
      }
      return 28;
    default:
      return 30;
  }
}

struct Date nextDay(int y, int m, int d)
{
  if (++d > howManyDaysInMonth(m, y)) {
    d = 1;
    if (++m > 12) {
      m = 1;
      ++y;
    }
  }
  return Date(y, m, d);
}
