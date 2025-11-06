#ifndef __HIGH_SCORE_SCENE_H__
#define __HIGH_SCORE_SCENE_H__

#include "axmol.h"
#include "SceneBase.h"

using namespace ax;

class HighScoreScene : public SceneBase
{
public:
    virtual bool init() override;

private:
    ax::Vec2 visibleSize;
    ax::Vec2 origin;
    ax::Rect safeArea;
    ax::Vec2 safeOrigin;

    ax::MenuItemImage* backButton;

    void scoreReturnCallback(ax::Object* sender);
};




#endif // __HIGH_SCORE_SCENE_H__
