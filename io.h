// Send a byte to frame buffer.
void out(unsigned short offset, unsigned short data);

// Send a byte to IO port.
void outb(unsigned short port, unsigned char data);

// Receive a byte from IO port.
unsigned char inb(unsigned short port);

