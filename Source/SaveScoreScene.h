#ifndef __SAVE_SCORE_SCENE_H__
#define __SAVE_SCORE_SCENE_H__

#include "axmol.h"
#include "SceneBase.h"
#include "ui/UITextField.h"
#include <vector>
#include <string>

using namespace ax;


class SaveScoreScene : public SceneBase
{
public:
    static ax::Scene* createScene(int score);

    virtual bool init() override;

    CREATE_FUNC(SaveScoreScene);

private:
    ax::Vec2 visibleSize;
    ax::Vec2 origin;
    ax::Rect safeArea;
    ax::Vec2 safeOrigin;

    ax::MenuItemImage* saveButton;
    ax::ui::TextField* textField;

    static int highScore;
};

#endif // __SAVE_SCORE_SCENE_H__
