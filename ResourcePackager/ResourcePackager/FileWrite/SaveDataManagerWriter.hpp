//
//  SaveDataManagerWriter.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 6/27/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef SaveDataManagerWriter_hpp
#define SaveDataManagerWriter_hpp

#include <stdio.h>
#include "ExcelDataParserBase.hpp"
#include "CPPFile.hpp"

using namespace std;

class SaveDataManagerWriter
{
private:
  CPPFileComplete *p_file;
  CPPClass *p_mainClass;
  CPPFunction *p_saveFunc;
  CPPFunction *p_loadFunc;
  CPPFunction *p_clearFunc;
public:
  SaveDataManagerWriter(const string &fileName);
  void addExcel(const ExcelDataParserBase *excel);
  void writeToPath(const string &path);
};

#endif /* SaveDataManagerWriter_hpp */
