//
//  CPPClass.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef CPPClass_hpp
#define CPPClass_hpp

#include <stdio.h>
#include "CPPFunction.hpp"
#include "CPPVariable.hpp"
#include <vector>

using namespace std;

class CPPClass
{
private:
  string p_className;
  vector<const CPPVariable *> p_privateVariables;
  vector<const CPPVariable *> p_publicVariables;
  vector<const CPPFunction *> p_privateFunctions;
  vector<const CPPFunction *> p_publicFunctions;
  string p_fatherClassName;
public:
  ~CPPClass();
  CPPClass(const string &className);
  void addVariable(const string &varName, const string &varType, bool isPrivate);
  void addVariable(CPPVariable *variable, bool isPrivate);
  void addFunction(const CPPFunction* func, bool isPrivate);
  void setFatherClass(const string &fatherClass);
  string getClassName() const;
  string getClassHeaderString() const;
  string getClassContentString() const;
};


#endif /* CPPClass_hpp */

