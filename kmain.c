#include "fb.h"

void kmain() {
	 int length = 4;
	 char message[] = "0x37";
	 struct Frame frame;
	 
	 fb_init();
	 for (int i = 0; i < length; i++) {
		  frame = fb_frame_new(message[i], FB_WHITE, FB_BLACK);
		  fb_frame_write(frame);
	 }
}

