//
//  CPPVariable.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef CPPVariable_hpp
#define CPPVariable_hpp

#include <stdio.h>
#include <string>

using namespace std;

const static string TYPE_BOOL = "bool";
const static string TYPE_INT = "int";
const static string TYPE_FLOAT = "float";
const static string TYPE_LONG = "long";
const static string TYPE_DOUBLE = "double";
const static string TYPE_STRING = "string";
const static string TYPE_VECTOR(const string &subType) {return "vector<" + subType + ">";};
const static string TYPE_SET(const string &subType) {return "unordered_set<" + subType + ">";};
const static string TYPE_VOID = "void";

class CPPVariable
{
private:
    bool p_isStatic;
    bool p_isConst;
    string p_varType;
    string p_varName;
public:
    CPPVariable(const string &varType);
    CPPVariable(const string &varName, const string &varType);
    CPPVariable(const string &varName, const string &varType, bool isStatic);
    CPPVariable(const string &varName, const string &varType, bool isStatic, bool isConst);
    string getDefineStatement() const;
    string getVarString() const;
    string getTypeString() const;
};

#endif /* CPPVariable_hpp */
