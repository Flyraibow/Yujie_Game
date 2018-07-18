//
//  CPPEnumClass.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/18/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef CPPEnumClass_hpp
#define CPPEnumClass_hpp

#include <stdio.h>
#include "CPPFunction.hpp"
#include "CPPVariable.hpp"
#include <vector>

using namespace std;

class CPPEnumClass
{
private:
  string p_className;
  string p_type;
  vector<const CPPVariable *> p_variables;
public:
  CPPEnumClass(const string &className, const string& type);
  void addVariable(const CPPVariable *var);
  string getClassContentString() const;
};


#endif /* CPPEnumClass_hpp */
