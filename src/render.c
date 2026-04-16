#include "render.h"
#include "config.h"
#include "utils.h"

void create_texture(const Texture2D* t, const Piece* p)
{
	char name[MAX_PATH_LENGTH];
	get_piece_path(name, &p);

	Image im = LoadImage(name);
	ImageResize(&im, PIECE_W, PIECE_H);
	
	*t = LoadTextureFromImage(im);
	UnloadImage(im);
}
