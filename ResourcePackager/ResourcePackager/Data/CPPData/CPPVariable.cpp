//
//  CPPVariable.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "CPPVariable.hpp"
#include <string>
using namespace std;


CPPVariable::CPPVariable(const string &varType) : CPPVariable::CPPVariable("", varType) {};

CPPVariable::CPPVariable(const string &varName, const string &varType) : CPPVariable::CPPVariable(varName, varType, false, false){}

CPPVariable::CPPVariable(const string &varName, const string &varType, bool isStatic) : CPPVariable::CPPVariable(varName, varType, isStatic, false){}

CPPVariable::CPPVariable(const string &varName, const string &varType, bool isStatic, bool isConst)
{
  p_varName = varName;
  p_varType = varType;
  p_isConst = isConst;
  p_isStatic = isStatic;
}

string CPPVariable::getDefineStatement() const
{
  string statement = p_isConst ? "const " : "";
  statement += p_isStatic ? "static " : "";
  statement += p_varType + " " + p_varName;
  return statement;
}

string CPPVariable::getVarString() const
{
  return p_varName;
}

string CPPVariable::getTypeString() const
{
  return p_varType;
}

bool CPPVariable::isStatic() const
{
  return p_isStatic;
}

string CPPVariable::getInitialValue() const
{
  return p_initialValue;
}


void CPPVariable::setInitialValue(const string &val)
{
  p_initialValue = val;
}

