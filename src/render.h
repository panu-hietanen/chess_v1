#ifndef RENDER_H__
#define RENDER_H__

#include "raylib.h"

#include "piece.h"

typedef struct {
	Texture2D data[2][6];
} PieceTextures;

void create_texture(Texture2D* t, const Piece* p);

void board_draw();

void piece_textures_load  (PieceTextures* pt);
void piece_textures_unload(PieceTextures* pt);

void piece_array_draw(const PieceArray* arr, const PieceTextures* pt);

#endif //RENDER_H__