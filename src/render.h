#ifndef RENDER_H__
#define RENDER_H__

#include "raylib.h"

#include "piece.h"
#include "board.h"

typedef struct {
	Texture2D data[2][6];
} PieceTextures;

void create_texture(Texture2D* t, PieceColour pColour, PieceType pType);

void board_draw();
void board_draw_piece(const Board* b, const PieceTextures* pt, const Point p);
void board_state_draw(const Board* b, const PieceTextures* pt);
void board_draw_clicked(const Board* b, const PieceTextures* pt, Point clicked);
void board_draw_moves(const Board* b, Point clicked);

void ui_draw(const Board* b);

void piece_textures_load  (PieceTextures* pt);
void piece_textures_unload(PieceTextures* pt);

#endif //RENDER_H__