#include "io.h"

#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_GREY_LIGHT 7
#define FB_GREY_DARK 8
#define FB_BLUE_LIGHT 9
#define FB_GREEN_LIGHT 10
#define FB_CYAN_LIGHT 11
#define FB_RED_LIGHT 12
#define FB_MAGENTA_LIGHT 13
#define FB_BROWN_LIGHT 14
#define FB_WHITE 15

struct Cell {
	 char c;
	 unsigned short fg;
	 unsigned short bg;
};

struct Cell cell_new(char c, unsigned short fg, unsigned short bg) {
	 struct Cell cell;
	 cell.c = c;
	 cell.fg = fg;
	 cell.bg = bg;
	 return cell;
}

unsigned short cell_format(struct Cell cell) {
	 unsigned short data;
	 data = (cell.bg << 4) | cell.fg;
	 data = data << 8 | cell.c;
	 return data;
}

void cell_write(struct Cell * buf, int length) {
	 unsigned short data;
	 unsigned short offset;
	 for (int i = 0; i < length; i++) {
		  data = cell_format(buf[i]);
		  offset = sizeof(data) * i;
		  out(offset, data);
	 }
}

void kmain() {
	 struct Cell buf[] = {
		  cell_new('0', FB_WHITE, FB_BLACK),
		  cell_new('x', FB_WHITE, FB_BLACK),
		  cell_new('3', FB_WHITE, FB_BLACK),
		  cell_new('7', FB_WHITE, FB_BLACK)
	 };

	 cell_write(buf, 4);
}

