#include "SHDirector.h"

namespace SailingHeroAPI {

SHDirector SHDirector::instance;

SailingHeroAPI::SHDirector * SHDirector::getInstance()
{
    return &instance;
}

}
