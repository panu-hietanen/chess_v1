#ifndef CONFIG_H__
#define CONFIG_H__

#define CELL_SIZE             80
#define BOARD_CELLS			  8
#define BOARD_PX		      (CELL_SIZE * BOARD_CELLS)
#define BOARD_COLOUR_LIGHT    GetColor(0xb58762ff)
#define BOARD_COLOUR_DARK     GetColor(0xefd9b5ff)

#define PIECE_W				  80
#define PIECE_H				  80
#define NUM_PIECE_TYPES		  6

#define SCREEN_W			  1280
#define SCREEN_H			  720

#define BOARD_OFFSET_X		  ((SCREEN_W - BOARD_PX) / 2)
#define BOARD_OFFSET_Y		  ((SCREEN_H - BOARD_PX) / 2)

#define RESOURCES_PATH		  "C:/Dev/C/chess_v1/resources/"
#define MAX_PATH_LENGTH		  48
#define MAX_PIECE_NAME_LENGTH 16


#endif //CONFIG_H__