#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "axmol.h"
#include "SceneBase.h"


class MainScene : public SceneBase
{
public:
    bool init() override;

    void update(float delta) override;

private:
    void createMainSceneItems();

    void onMouseMove(ax::Event* event) override;

    void menuPlayGameCallback(ax::Object* sender);
    void menuHighScoreCallback(ax::Object* sender);
    void menuCloseCallback(ax::Object* sender);
    
    ax::MenuItemImage* playItem;
    ax::MenuItemImage* scoreItem;
    ax::MenuItemImage* exitItem;
    ax::Sprite* borderSprite;

    ax::Vec2 visibleSize;
    ax::Vec2 origin;
    ax::Rect safeArea;
    ax::Vec2 safeOrigin;
};

#endif  // __MAIN_SCENE_H__
