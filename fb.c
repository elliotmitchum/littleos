#include "io.h"
#include "fb.h"

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
 * Write frames to buffer.
 *
 * @param buf Frame list.
 * @param length Write length.
 */
void fb_frame_write(struct Frame * buf, int length) {
	 unsigned short data;
	 unsigned short offset;
	 for (int i = 0; i < length; i++) {
		  // Convert struct to buffer friendly bits.
		  data = fb_frame_format(buf[i]);
		  offset = sizeof(data) * i;
		  // Call `out` instruction, write frame to buffer.
		  out(offset, data);
	 }
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

