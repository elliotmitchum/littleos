#include "fb.h"

void kmain() {
	 char message[] = "0x37";
	 fb_init();
	 fb_frame_write_ln(message);
}

