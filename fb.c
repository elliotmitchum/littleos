#include "io.h"
#include "fb.h"

/**
 * frame_new:
 *
 * Create new Frame.
 *
 * @param char ASCII character code.
 * @param fg Foreground colour.
 * @param bg Background colour.
 *
 * @return Frame Constructed frame.
 */
struct Frame frame_new(char c, unsigned short fg, unsigned short bg) {
	 struct Frame frame;
	 frame.c = c;
	 frame.fg = fg;
	 frame.bg = bg;
	 return frame;
}

/**
 * frame_format:
 *
 * Format frame for buffer.
 *
 * @param frame Frame.
 * 
 * @return 2 byte buffer friendly frame.
 */
unsigned short frame_format(struct Frame frame) {
	 // Create 2 byte frame cell binary.
	 // @url https://ordoflammae.github.io/littleosbook/#the-framebuffer
	 unsigned short data;
	 data = (frame.bg << 4) | frame.fg;
	 data = data << 8 | frame.c;
	 return data;
}

/**
 * frame_write:
 *
 * Write frames to buffer.
 *
 * @param buf Frame list.
 * @param length Write length.
 */
void frame_write(struct Frame * buf, int length) {
	 unsigned short data;
	 unsigned short offset;
	 for (int i = 0; i < length; i++) {
		  // Convert struct to buffer friendly bits.
		  data = frame_format(buf[i]);
		  offset = sizeof(data) * i;
		  // Call `out` instruction, write frame to buffer.
		  out(offset, data);
	 }
}

