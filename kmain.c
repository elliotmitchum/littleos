#include "fb.h"
#include "io.h"

void kmain() {
	 int length = 4;
	 struct Frame buf[length];

	 // Assign frames.
	 buf[0] = frame_new('0', FB_WHITE, FB_BLACK);
	 buf[1] = frame_new('x', FB_WHITE, FB_BLACK);
	 buf[2] = frame_new('3', FB_WHITE, FB_BLACK);
	 buf[3] = frame_new('7', FB_WHITE, FB_BLACK);
	 buf[4] = frame_new('7', FB_WHITE, FB_BLACK);

	 // Write frames to buffer.
	 frame_write(buf, length + 1);

	 fb_move_cursor(20);
}

