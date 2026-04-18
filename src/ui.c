#include "ui.h"

bool restart_mouse_over(float x, float y)
{
	if (x > RESTART_OFFSET_X && x < RESTART_OFFSET_X + RESTART_W &&
		y > RESTART_OFFSET_Y && y < RESTART_OFFSET_Y + RESTART_H)
	{
		return true;
	}
	return false;
}
