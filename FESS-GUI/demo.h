#ifndef DEMO_H
#define DEMO_H

// Custom Libraries
#include "interface.h"

class Demo : public Interface
{
public:
    Demo();

    void sync();
};

#endif // DEMO_H
