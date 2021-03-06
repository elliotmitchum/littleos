// IO command port address.
#define FB_COMMAND_PORT 0x3D4

// IO data port address.
#define FB_DATA_PORT 0x3D5

// High byte signal.
#define FB_HIGH_BYTE_COMMAND 14

// Low byte signal.
#define FB_LOW_BYTE_COMMAND 15

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

// Frame structure.
struct Frame {
  char c;
  unsigned short fg;
  unsigned short bg;
};

// Initialise freame buffer pointer.
void fb_init();

// Create new frame.
struct Frame fb_frame_new(char c, unsigned short fg, unsigned short bg);

// Format frame for buffer.
unsigned short fb_frame_format(struct Frame frame);

// Write frame to buffer and advance cursor.
void fb_frame_write(struct Frame frame);

// Write string to frame buffer with format options, advancing cursor,
void fb_frame_writef_ln(char * message, unsigned short fb, unsigned short bg);

// Write string to frame buffer, advancing cursor.
void fb_frame_write_ln(char * message);

// Move cursor to buffer position.
void fb_move_cursor(unsigned short post);

