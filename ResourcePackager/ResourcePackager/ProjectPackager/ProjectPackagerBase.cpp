//
//  ProjectPackagerBase.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ProjectPackagerBase.hpp"

void ProjectPackagerBase::set_dataSourcePath(const string &path)
{
    s_dataSourcePath = path;
}

void ProjectPackagerBase::set_outputResourcePath(const string &path)
{
    s_outputPath = path;
}

string ProjectPackagerBase::get_dataSourcePath() const
{
    return s_dataSourcePath;
}

string ProjectPackagerBase::get_outputResourcePath() const
{
    return s_outputPath;
}
