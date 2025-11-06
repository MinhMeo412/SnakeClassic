#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "axmol.h"

class SplashScene : public ax::Scene
{
public:
    virtual bool init();
private:
    void goToMainScene(float dt);
};

#endif // __SPLASH_SCENE_H__
