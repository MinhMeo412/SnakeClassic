#ifndef __UTILS_H__
#define __UTILS_H__

#include "axmol.h"

#define DISPLAY_TIME_HELLO_SCENE 0.5
#define TRANSITION_TIME          0.5

enum Direction
{
    UP    = 0,
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3,
    NONE  = -1
};


namespace Utils
{
// Print useful error message instead of segfaulting when files are not there.
void problemLoading(const char* filename);

// Create menu items
ax::MenuItemImage* createMenuItem(ax::Sprite* normalImage,
                                         ax::Sprite* selectedImage,
                                         const ax::ccMenuCallback& callback,
                                         const ax::Vec2& position);

// Create menu items
ax::MenuItemImage* createMenuItem(std::string normalImage,
                                  std::string selectedImage,
                                  const ax::ccMenuCallback& callback,
                                  const ax::Vec2& position);
}  // namespace Utils

#endif  // __UTILS_H__
