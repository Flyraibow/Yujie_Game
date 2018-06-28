//
//  ObjectData.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ObjectData_hpp
#define ObjectData_hpp

#include <stdio.h>
#include <string>

using namespace std;

enum DataType {
  ID = 1,
  BOOL,
  INT,
  FLOAT,
  LONG,
  DOUBLE,
  STRING,
  VECTOR,
  ICON,
  LANGUAGE,
  MUSIC,
  EFFECT,     // 音效
  COMMENT,    // 评论
  FRIEND_ID,  // 友元
  SET,
};

class DataSchema
{
private:
  string p_name;
  string p_typeString;
  DataType p_type;
  string p_subType;
  bool p_isWritable;
public:
  string getName() const;
  DataType getType() const;
  string getSubtype() const;
  bool isWritable() const;
  
  DataSchema(const string &name, const string &type, const string &subType, bool isWritable);
};


#endif /* ObjectData_hpp */

