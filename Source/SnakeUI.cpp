#include "SnakeUI.h"
#include "Utils.h"
#include <iostream>

using namespace ax;

SnakeUI* SnakeUI::create(SnakeModel* logic)
{
    SnakeUI* ret = new (std::nothrow) SnakeUI();
    if (ret && ret->init(logic))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool SnakeUI::init(SnakeModel* logic)
{
    if (!Node::init())
    {
        return false;
    }
    
    this->snakeLogic = logic;

    createBodySprites();

    return true;
}



void SnakeUI::createBodySprites()
{
    if (!snakeLogic) return;

    const auto& bodyPositions = snakeLogic->getBodyPositions();

    // Xóa các sprite cũ nếu có
    for (auto sprite : bodySprites)
    {
        if (sprite)
        {
            this->removeChild(sprite);
            sprite->removeFromParent();
        }
    }
    bodySprites.clear();

    bodySprites.reserve(bodyPositions.size());

    // Tạo sprite cho mỗi phần thân rắn
    for (size_t i = 0; i < snakeLogic->getBodyPositions().size(); ++i)
    {
        Vec2 position = bodyPositions[i];
        Sprite* sprite = nullptr;

        if (i == 0) // Đầu rắn
        {
            Direction dir = snakeLogic->getDirections();
            if (dir == NONE) 
            {
                sprite = Sprite::create("head_up.png");
            }
            else 
            {
                sprite = Sprite::create(headSpriteFiles[static_cast<int>(dir)]);
            }
        }
        else if (i == bodyPositions.size() - 1) // Đuôi rắn
        {
            const auto& bodyPositions = snakeLogic->getBodyPositions();
            if (bodyPositions.size() >= 2)
            {
                Vec2 tailPosition = bodyPositions[i];
                Vec2 previousPartPosition = bodyPositions[i - 1];

                // Xác định hướng đuôi dựa trên vị trí trước đó
                if (tailPosition.x == previousPartPosition.x) {
                    // Nếu tọa độ x giống nhau, thì nó đang di chuyển theo chiều dọc
                    if (tailPosition.y < previousPartPosition.y) {
                        sprite = Sprite::create("tail_down.png"); // Đuôi đang hướng xuống
                    }
                    else {
                        sprite = Sprite::create("tail_up.png"); // Đuôi đang hướng lên
                    }
                }
                else {
                    // Nếu tọa độ y giống nhau, thì nó đang di chuyển theo chiều ngang
                    if (tailPosition.x < previousPartPosition.x) {
                        sprite = Sprite::create("tail_left.png"); // Đuôi đang hướng trái
                    }
                    else {
                        sprite = Sprite::create("tail_right.png"); // Đuôi đang hướng phải
                    }
                }
            }
            else {
                // Nếu không có phần nào khác, sử dụng mặc định hoặc một hình ảnh nào đó
                AXLOG("Tail snake error!!");
            }
        }
        else // Thân rắn
        {
            // Kiểm tra hướng giữa các phần
            Vec2 first = bodyPositions[i - 1];
            Vec2 second = bodyPositions[i];
            Vec2 third = (i < bodyPositions.size() - 1) ? bodyPositions[i + 1] : second; // Tránh lỗi truy cập ra ngoài

            // Xác định hướng di chuyển của từng đoạn
            int dx1 = second.x - first.x;
            int dy1 = second.y - first.y;
            int dx2 = third.x - second.x;
            int dy2 = third.y - second.y;

            // Kiểm tra góc trước
 
                if (dx1 > 0 && dy2 > 0) {
                    sprite = Sprite::create(bodyCornerSprites[2]); // Rẽ phải lên
                }
                else if (dx1 > 0 && dy2 < 0) {
                    sprite = Sprite::create(bodyCornerSprites[0]); // Rẽ phải xuống
                }
                else if (dx1 < 0 && dy2 > 0) {
                    sprite = Sprite::create(bodyCornerSprites[3]); // Rẽ trái lên
                }
                else if (dx1 < 0 && dy2 < 0) {
                    sprite = Sprite::create(bodyCornerSprites[1]); // Rẽ trái xuống
                }
                else if (dy1 > 0 && dx2 < 0) {
                    sprite = Sprite::create(bodyCornerSprites[0]); // Rẽ lên trái
                }
                else if (dy1 < 0 && dx2 > 0) {
                    sprite = Sprite::create(bodyCornerSprites[3]); // Rẽ xuống phải
                }
                else if (dy1 < 0 && dx2 < 0) {
                    sprite = Sprite::create(bodyCornerSprites[2]); // Rẽ xuống trái
                }
                else if (dy1 > 0 && dx2 > 0) {
                    sprite = Sprite::create(bodyCornerSprites[1]); // Rẽ lên phải
                }
            // Kiểm tra thân thẳng
            else if (dx1 == 0 && dx2 == 0)
            {
                sprite = Sprite::create(bodyVerticalSprite); // Thân thẳng đứng
            }
            else if (dy1 == 0 && dy2 == 0)
            {
                sprite = Sprite::create(bodyHorizontalSprite); // Thân nằm ngang
            }
            else
            {
                AXLOG("Body snake error!!");
            }
        }

        if (sprite)
        {
            sprite->setPosition(position);
            this->addChild(sprite);
            bodySprites.push_back(sprite);
        }
        else { AXLOG("Null sprite"); }
    }
}


void SnakeUI::updateUI()
{
    // Xóa các sprite cũ nếu có
    for (auto sprite : bodySprites)
    {
        this->removeChild(sprite);
    }
    bodySprites.clear();

    createBodySprites();
}


