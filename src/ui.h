#ifndef UI_H__
#define UI_H__

#include <stdbool.h>

#include "board.h"

bool restart_mouse_over(float x, float y);

bool promote_mouse_over(float x, float y);
PieceType promote_mouse_selection(float x, float y);

#endif //UI_H__