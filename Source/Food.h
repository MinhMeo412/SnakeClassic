
#ifndef __FOOD_H__
#define __FOOD_H__

#include "axmol.h"


class Food : public ax::Sprite
{
public:
    virtual bool init();
    
    CREATE_FUNC(Food);


private:

};

#endif // __FOOD_H__
