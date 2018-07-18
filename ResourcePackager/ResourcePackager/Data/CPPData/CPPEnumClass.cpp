//
//  CPPEnumClass.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/18/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "CPPEnumClass.hpp"


CPPEnumClass::CPPEnumClass(const string &className, const string& type)
{
  p_className = className;
  p_type = type;
}


void CPPEnumClass::addVariable(const CPPVariable *var)
{
  p_variables.push_back(var);
}

string CPPEnumClass::getClassContentString() const
{
  string result = "enum class " + p_className;
  if (p_type != TYPE_INT) {
    result += " : " + p_type;
  }
  result += "\n{\n";
  for (int i = 0; i < p_variables.size(); ++i) {
    auto var = p_variables.at(i);
    result += "\t" + var->getVarString() + " = " + var->getInitialValue() +",\n";
  }
  result += "};\n\n";
  return result;
}
