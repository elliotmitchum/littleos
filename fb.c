#include "io.h"
#include "fb.h"

// Frame buffer.
static char * fb = 0;

// Cursor position.
static unsigned short pos = 0;

/**
 * Initialise frame buffer pointer.
 *
 * Points internal `fb` variable to frame buffer memory mapped address
 * `0x000B800`.
 */
void fb_init() {
  fb = (char *) 0x000B8000;
}

/**
 * fb_frame_new:
 *
 * Create new Frame.
 *
 * @param char ASCII character code.
 * @param fg Foreground colour.
 * @param bg Background colour.
 *
 * @return Frame Constructed frame.
 */
struct Frame fb_frame_new(char c, unsigned short fg, unsigned short bg) {
  struct Frame frame;
  frame.c = c;
  frame.fg = fg;
  frame.bg = bg;
  return frame;
}

/**
 * fb_frame_format:
 *
 * Format frame for buffer.
 *
 * @param frame Frame.
 * 
 * @return 1 byte buffer friendly frame.
 */
unsigned short fb_frame_format(struct Frame frame) {
  // Create 2 byte frame cell binary.
  // @url https://ordoflammae.github.io/littleosbook/#the-framebuffer
  unsigned short data;
  data = (frame.bg << 4) | frame.fg;
  data = data << 8 | frame.c;
  return data;
}

/**
 * fb_frame_write:
 *
 * Write frame to buffer and advance cursor.
 *
 * @param frame Frame.
 */
void fb_frame_write(struct Frame frame) {
  unsigned short data = fb_frame_format(frame);

  // Frame byte size.
  unsigned short size = sizeof(data);

  // Write frame to buffer with frame byte offset.
  fb[pos * size] = data;

  // Advance cursor.
  pos = pos + 1;
  fb_move_cursor(pos);
}

/**
 * fb_frame_writef_ln:
 *
 * Write string to frame buffer with format options, advancing cursor.
 *
 * Note: Frame buffer must first be initialised with fb_init().
 *
 * @param message Message string.
 * @param fg Foreground colour.
 * @param bg Background colour.
 */
void fb_frame_writef_ln(char * message, unsigned short fg, unsigned short bg) {
  struct Frame frame;
  unsigned short i = 0;
  while (message[i] != '\0') {
    frame = fb_frame_new(message[i], fg, bg);
    fb_frame_write(frame);
    i++;
  }
}

/**
 * fb_frame_write_ln:
 *
 * Write string to frame buffer, advancing cursor.
 *
 * Implements fb_frame_writef_ln with default colours.
 *
 * @see fb_frame_writef_ln
 * @param message Message string.
 */
void fb_frame_write_ln(char * message) {
  fb_frame_writef_ln(message, FB_WHITE, FB_BLACK);
}

/**
 * fb_move_cursor:
 *
 * Move cursor to buffer position.
 *
 * A position is represented in 16 bits, however the `out` argument is 8 bits,
 * therefore the position must be written twice. Command port is used to
 * determine if the high or low byte is send.
 *
 * @url https://ordoflammae.github.io/littleosbook/#moving-the-cursor
 * @param pos Cursor position.
 */
void fb_move_cursor(unsigned short pos) {
  // Single byte number with all bits set to 1.
  unsigned char root = 0x00FF;

  // Signal and write high byte.
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & root));

  // Signal and write low byte.
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & root);
}

