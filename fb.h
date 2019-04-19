// Colours.

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

// Frame.
struct Frame {
	 char c;
	 unsigned short fg;
	 unsigned short bg;
};

// frame_new.
struct Frame frame_new(char c, unsigned short fg, unsigned short bg);

// frame_format.
unsigned short frame_format(struct Frame frame);

// frame_write.
void frame_write(struct Frame * buf, int length);

