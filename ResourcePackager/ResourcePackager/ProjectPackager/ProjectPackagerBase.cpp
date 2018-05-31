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
    p_dataSourcePath = path;
}

void ProjectPackagerBase::set_outputResourcePath(const string &path)
{
    p_outputPath = path;
}

void ProjectPackagerBase::set_outputCodeFolderPath(const string &path)
{
    p_outputCodePath = path;
}

string ProjectPackagerBase::get_dataSourcePath() const
{
    return p_dataSourcePath;
}

string ProjectPackagerBase::get_outputResourcePath() const
{
    return p_outputPath;
}

string ProjectPackagerBase::get_outputCodeFolderPath() const
{
    return p_outputCodePath;
}
