#include "render.h"
#include "config.h"
#include "utils.h"

#include "piece.h"

void create_texture(Texture2D* t, PieceColour pColour, PieceType pType)
{
	char name[MAX_PATH_LENGTH];
	get_piece_path(name, pColour, pType);

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
			switch (type)
			{
			case PIECE_PAWN:
				bool canMove = move_valid_pawn(clicked, to, b->turn);
				bool canCapture = move_valid_pawn_capture(clicked, to, b->turn);

				if (!canMove && !canCapture) continue;
				if (!canCapture && board_blocked_pawn(b, clicked, to)) continue;
				if (!canMove && b->state[to.x][to.y] < 0) continue;
				break;
			case PIECE_ROOK:
				if (!move_valid_rook(clicked, to)) continue;
				if (board_blocked_rook(b, clicked, to)) continue;
				break;
			case PIECE_KNIGHT:
				if (!move_valid_knight(clicked, to)) continue;
				break;
			case PIECE_BISHOP:
				if (!move_valid_bishop(clicked, to)) continue;
				if (board_blocked_bishop(b, clicked, to)) continue;
				break;
			case PIECE_QUEEN:
				if (!move_valid_queen(clicked, to)) continue;
				if (board_blocked_queen(b, clicked, to)) continue;
				break;
			case PIECE_KING:
				if (!move_valid_king(clicked, to)) continue;
				break;
			}
			if (!board_can_capture(b, clicked, to)) continue;
			DrawCircle(
				BOARD_OFFSET_X + i * CELL_SIZE + CELL_SIZE / 2,
				SCREEN_H - BOARD_OFFSET_Y - j * CELL_SIZE - CELL_SIZE / 2,
				CELL_SIZE / 5, BROWN
			);
		}
	}
}

void piece_textures_load(PieceTextures* pt)
{
	for (PieceColour colour = 0; colour < 2; ++colour)
	{
		for (PieceType type = 0; type < 6; ++type)
		{
			create_texture(&pt->data[colour][type], colour, type);
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
