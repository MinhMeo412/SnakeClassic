#include "Food.h"

using namespace ax;


bool Food::init()
{
    if (!Sprite::initWithFile("apple.png"))
    {
        return false;
    }

    return true;
}
