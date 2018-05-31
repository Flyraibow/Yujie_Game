//
//  Utils.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "Utils.hpp"
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include <dirent.h>

using namespace std;

void utils::createFolderIfNotExist(const std::string &folderPath)
{
    int err = system(("mkdir -p " + folderPath).c_str());
    assert(err == 0);
}

void utils::writeBufferToFile(std::unique_ptr<bb::ByteBuffer> &buffer, const std::string &folderpath, const std::string filename)
{
    // write buffer
    cout<< "write buffer to file " << folderpath << " -> " << filename << endl;
    createFolderIfNotExist(folderpath);
    const string path = folderpath + "/" + filename;
    auto size = buffer->size();
    ofstream outfile (path);
    uint8_t* buf = new uint8_t[size];
    buffer->getBytes(buf, size);
    char *chrs = new char[size];
    memcpy(chrs, buf, size);
    outfile.write (chrs,size);
    outfile.close();
    delete [] buf;
    delete [] chrs;
}

void utils::writeStringToFile(const string &content, const std::string &folderpath, const std::string filename)
{
    // write buffer
    cout<< "write buffer to file " << folderpath << " -> " << filename << endl;
    createFolderIfNotExist(folderpath);
    const string path = folderpath + "/" + filename;
    ofstream outfile (path);
    outfile.write(content.c_str(),content.length());
    outfile.close();
}

vector<string> utils::getCSVFileList(const string &path) {
    vector<string> result;
    string postFix = CSV_EXTENSION;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            char *chr = ent->d_name;
            size_t len =strlen(chr);
            size_t postLen = postFix.length();
            if (len > postLen && strcmp(postFix.c_str(),chr + len - postLen) == 0) {
                string fullName = chr;
                result.push_back(fullName);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        cout<< " ERROR " << endl;
        return result;
    }
    return result;
}
