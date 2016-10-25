#include "conversions.h"

float bytesToFloat(std::vector<uint8_t> buffer)
{
    uint8_t val[] = {buffer[0], buffer[1], buffer[2], buffer[3]};
    return *reinterpret_cast<float*>(&val);
}

