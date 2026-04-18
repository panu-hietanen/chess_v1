#include "render.h"
#include "config.h"
#include "utils.h"

#include "piece.h"

void create_texture(Texture2D* t, PieceColour pColour, PieceType pType, int w, int h)
{
	char name[MAX_PATH_LENGTH];
	get_piece_path(name, pColour, pType);

	Image im = LoadImage(name);
	ImageResize(&im, w, h);
	
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

void board_draw_clicked(const Board* b, const PieceTextures* pt, Point clicked)
{
	if (!board_select_valid(b, clicked)) return;
	int x = clicked.x;
	int y = clicked.y;
	DrawRectangle(
		BOARD_OFFSET_X + x * CELL_SIZE,
		SCREEN_H - BOARD_OFFSET_Y - (y + 1) * CELL_SIZE,
		CELL_SIZE, CELL_SIZE,
		MAROON
	);
	board_draw_piece(b, pt, clicked);
}

void board_draw_moves(const Board* b, Point clicked)
{
	int piece = b->state[clicked.x][clicked.y];

	PieceType type = get_piece_type(piece);
	for (int i = 0; i < BOARD_CELLS; ++i)
	{
		for (int j = 0; j < BOARD_CELLS; ++j)
		{
			Point to = { .x = i, .y = j };

			if (!board_move_valid(b, clicked, to)) continue;

			DrawCircle(
				BOARD_OFFSET_X + i * CELL_SIZE + CELL_SIZE / 2,
				SCREEN_H - BOARD_OFFSET_Y - j * CELL_SIZE - CELL_SIZE / 2,
				CELL_SIZE / 5, BROWN
			);
		}
	}
}

void ui_draw(const Board* b)
{
	const double recSide = 80;
	Color turnColour = (b->turn == PIECE_WHITE) ? WHITE : BLACK;
	DrawRectangle((BOARD_OFFSET_X - recSide) / 2, SCREEN_H / 2, recSide, recSide, turnColour);
	DrawText("Turn:", (BOARD_OFFSET_X - 3 * recSide / 4) / 2, SCREEN_H / 2 - 26, 19, BLACK);


	DrawRectangleLines(RESTART_OFFSET_X, RESTART_OFFSET_Y, 200, 80, WHITE);
	DrawText("RESTART", RESTART_OFFSET_X + 27, RESTART_OFFSET_Y + 25, 30, BLACK);
}

void piece_textures_load(PieceTextures* pt, int w, int h)
{
	for (PieceColour colour = 0; colour < 2; ++colour)
	{
		for (PieceType type = 0; type < 6; ++type)
		{
			create_texture(&pt->data[colour][type], colour, type, w, h);
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
