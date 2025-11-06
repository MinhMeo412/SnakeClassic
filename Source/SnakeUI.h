#ifndef __SNAKE_UI_H__
#define __SNAKE_UI_H__

#include "axmol.h"
#include "Utils.h"
#include "SnakeModel.h"

#include <deque>
#include <vector>


class SnakeModel;

class SnakeUI : public ax::Node
{
public:
    static SnakeUI* create(SnakeModel* logic);

    virtual bool init(SnakeModel* logic);


    
    void updateUI();


    
private: 
    SnakeModel* snakeLogic;
    std::vector<ax::Sprite*> bodySprites;

    std::string headSpriteFiles[4] = { "head_up.png", "head_down.png", "head_left.png", "head_right.png" };
    std::string tailSpriteFiles[4] = { "tail_up.png", "tail_down.png", "tail_left.png", "tail_right.png" };
    std::string bodyVerticalSprite = "body_vertical.png";
    std::string bodyHorizontalSprite = "body_horizontal.png";
    std::string bodyCornerSprites[4] = { "body_bottomleft.png", "body_bottomright.png", "body_topleft.png", "body_topright.png" };

    void createBodySprites();
};

#endif // __SNAKE_UI_H__
