//
//  ProjectPackagerBase.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ProjectPackagerBase_hpp
#define ProjectPackagerBase_hpp

#include <stdio.h>
#include <string>

using namespace std;

class ProjectPackagerBase
{
protected:
    string s_dataSourcePath;
    string s_outputPath;
public:
    void set_dataSourcePath(const string &path);
    void set_outputResourcePath(const string &path);
    string get_dataSourcePath() const;
    string get_outputResourcePath() const;
    
    virtual void startPackage() = 0;
};

#endif /* ProjectPackagerBase_hpp */
