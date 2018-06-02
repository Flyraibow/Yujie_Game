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
    string m_name;
    string m_typeString;
    DataType m_type;
    string m_subType;
public:
    string getName() const;
    DataType getType() const;
    string getSubtype() const;
    
    DataSchema(const string &name, const string &type, const string &subType);
};


#endif /* ObjectData_hpp */
