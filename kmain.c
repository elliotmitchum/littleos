#include "fb.h"
#include "io.h"

void kmain() {
	 int length = 4;
	 struct Frame buf[length];

	 // Assign frames.
	 buf[0] = fb_frame_new('0', FB_WHITE, FB_BLACK);
	 buf[1] = fb_frame_new('x', FB_WHITE, FB_BLACK);
	 buf[2] = fb_frame_new('3', FB_WHITE, FB_BLACK);
	 buf[3] = fb_frame_new('7', FB_WHITE, FB_BLACK);
	 buf[4] = fb_frame_new('7', FB_WHITE, FB_BLACK);

	 // Write frames to buffer.
	 fb_frame_write(buf, length + 1);

	 fb_move_cursor(20);
}

