//
//  Utils.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include "ByteBuffer.hpp"
#include <string>

namespace write {
    void createFolderIfNotExist(const std::string &folderPath);
    void writeBufferToFile(std::unique_ptr<bb::ByteBuffer> &buffer, const std::string &folderpath, const std::string filename);
}

#endif /* Utils_hpp */
