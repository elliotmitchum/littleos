#include "io.h"
#include "fb.h"

// frame_new().
// Create new frame.
struct Frame frame_new(char c, unsigned short fg, unsigned short bg) {
	 struct Frame frame;
	 frame.c = c;
	 frame.fg = fg;
	 frame.bg = bg;
	 return frame;
}

// frame_format().
// Format buffer frame formatter.
unsigned short frame_format(struct Frame frame) {
	 // Create 2 byte frame cell binary.
	 // @url https://ordoflammae.github.io/littleosbook/#the-framebuffer<Paste>.
	 unsigned short data;
	 data = (frame.bg << 4) | frame.fg;
	 data = data << 8 | frame.c;
	 return data;
}

// frame_format().
// Write formatted frame to buffer.
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

