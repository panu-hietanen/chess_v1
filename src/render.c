#include "render.h"
#include "config.h"
#include "utils.h"

#include "piece.h"

void create_texture(Texture2D* t, const Piece* p)
{
	char name[MAX_PATH_LENGTH];
	get_piece_path(name, p);

	Image im = LoadImage(name);
	ImageResize(&im, PIECE_W, PIECE_H);
	
	*t = LoadTextureFromImage(im);
	UnloadImage(im);
}

void board_draw()
{
	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		for (int j = 0; j < BOARD_CELLS; ++j)
		{
			Color c = ((i + j) % 2 == 0) ? BOARD_COLOUR_LIGHT : BOARD_COLOUR_DARK;
			DrawRectangle(
				BOARD_OFFSET_X + j * CELL_SIZE,
				BOARD_OFFSET_Y + i * CELL_SIZE,
				CELL_SIZE, CELL_SIZE,
				c
			);
		}
	}
}

void board_draw_piece(const Board* b, const PieceTextures* pt, const Point p)
{
	if (p.x < 0 || p.y < 0) return;
	int piece = b->state[p.x][p.y];
	if (piece < 0) return;

	const PieceColour colour = get_piece_colour(piece);
	const PieceType type = get_piece_type(piece);

	const int sx = BOARD_OFFSET_X + p.x * CELL_SIZE;
	const int sy = BOARD_OFFSET_Y + (BOARD_CELLS - 1 - p.y) * CELL_SIZE;
	DrawTexture(pt->data[colour][type], sx, sy, WHITE);
}

void board_state_draw(const Board* b, const PieceTextures* pt)
{
	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		for (int j = 0; j < BOARD_CELLS; ++j)
		{
			board_draw_piece(b, pt, (Point) { .x = i, .y = j });
		}
	}
}

void board_draw_clicked(const Board* b, const PieceTextures* pt)
{
	if (!board_click_valid(b)) return;
	int x = b->clicked.x;
	int y = b->clicked.y;
	DrawRectangle(
		BOARD_OFFSET_X + x * CELL_SIZE,
		SCREEN_H - BOARD_OFFSET_Y - (y + 1) * CELL_SIZE,
		CELL_SIZE, CELL_SIZE,
		MAROON
	);
	board_draw_piece(b, pt, b->clicked);
}

void piece_textures_load(PieceTextures* pt)
{
	for (int colour = 0; colour < 2; ++colour)
	{
		for (int type = 0; type < 6; ++type)
		{
			Piece p = { .colour = colour, .type = type };
			create_texture(&pt->data[colour][type], &p);
		}
	}
}

void piece_textures_unload(PieceTextures* pt)
{
	for (int colour = 0; colour < 2; ++colour)
	{
		for (int type = 0; type < 6; ++type)
		{
			UnloadTexture(pt->data[colour][type]);
		}
	}
}

void piece_array_draw(const PieceArray* arr, const PieceTextures* pt)
{
	for (int i = 0; i < arr->len; ++i)
	{
		Piece p = arr->data[i];
		if (!p.active) continue;

		int sx = BOARD_OFFSET_X + p.x * CELL_SIZE;
		int sy = BOARD_OFFSET_Y + (BOARD_CELLS - p.y) * CELL_SIZE;
		DrawTexture(pt->data[p.colour][p.type], sx, sy, WHITE);
	}
}
