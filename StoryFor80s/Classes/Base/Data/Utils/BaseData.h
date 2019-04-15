//
//  BaseData.h
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#ifndef BaseData_h
#define BaseData_h

#include <set>
#include <stdio.h>

using namespace std;
//using std::string;
//template <class T>
//using vector = std::vector<T>;
//template <class T>
//using set = std::set<T>;
//template <class K, class T>
//using map = std::map<K, T>;
//template <class T1, class T2>
//using pair = std::pair<T1, T2>;

class BaseData
{
public:
  virtual string getId() const {return "";};
  virtual string description() const = 0;
  virtual string getFieldValue(const string & fieldName) const = 0;
  virtual string getMapFieldValueWithKey(const string & fieldName, const string & key) const {return "";};
  virtual BaseData *getDataByField(const string &fieldName) const { return nullptr; };
  virtual void setFieldValue(const string & fieldName, const string & value) {};
  virtual vector<BaseData *> getFieldDataList(const string & fieldName) const = 0;
};

template<typename T>
std::set<BaseData *> fromData(std::set<T> realSet)
{
  std::set<BaseData *> baseSet;
  for (auto data : realSet) baseSet.insert(data);
  return baseSet;
}


#endif /* BaseData_h */
