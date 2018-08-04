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
#include "ByteBuffer.hpp"

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
  FRIEND_ID_SET, // 引用集合
  FRIEND_ID_VECTOR, // 引用数组
  ENUM,       // 枚举
  FRIEND_ID_MAP, // 哈希表
};

const static unordered_map<string, DataType> s_subtype_map({
  {"bool", BOOL},
  {"int", INT},
  {"long", LONG},
  {"float", FLOAT},
  {"double", DOUBLE},
  {"string", STRING},
});

class DataSchema
{
private:
  string p_name;
  string p_typeString;
  DataType p_type;
  string p_subType;
  bool p_isWritable;
  bool p_isWeak;
public:
  string getName() const;
  DataType getType() const;
  string getSubtype() const;
  bool isWritable() const;
  bool isWeak() const;
  
  void addValueIntoBuffer(std::unique_ptr<bb::ByteBuffer> &buffer, const string& value);
  
  DataSchema(const string &name, const string &type, const string &subType, bool isWritable);
};


#endif /* ObjectData_hpp */

