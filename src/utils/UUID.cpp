#include "utils/UUID.h"

namespace Utils
{
    unsigned long long UuidGenerator::s_uuidCounter = 0;
    UUID UuidGenerator::generate()
    {
        ++s_uuidCounter;
        return s_uuidCounter;
    }
}