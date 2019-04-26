#include "fb.h"
#include "gdt.h"

void kmain() {
	 char message[] = "0x37";
   gdt_init();
	 fb_init();
	 fb_frame_write_ln(message);
}

