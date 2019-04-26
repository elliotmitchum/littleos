/**
 * Global Descriptor Table.
 *
 * @url https://en.wikipedia.org/wiki/Global_Descriptor_Table
 * @url https://wiki.osdev.org/Global_Descriptor_Table
 * @url http://www.osdever.net/bkerndev/Docs/gdt.htm
 */

/**
 * GDT:
 *
 * Global descriptor table. Describes memory segments.
 *
 * base: Segment memory address.
 * limit: Segment size.
 *
 * @url https://en.wikibooks.org/wiki/X86_Assembly/Global_Descriptor_Table
 */
struct Gdt {
  unsigned short limit;
  unsigned int base;
}__attribute__((packed));

/**
 * GdtDescriptor:
 *
 * Describes an 64 bit GDT descriptor.
 *
 * base_high (63-56): Base memory address, high 2 bytes. [8 bit]
 * granularity (55-54): Segment granularity. [2 bit]
 *   size: Granularity bit (0 = 1 byte, 1 = 4 byte / page).
 *   osize: Operand size bit (0 = 16 bit, 1 = 32 bit).
 * limit_high (51-48): Segment size. [4 bit]
 * access (47-40): Segment access rights. [8 bit]
 *   present: Present bit. [1 bit]
 *	 ring: Ring (0 to 3). [2 bit]
 *	 d_type: Descriptor type bit (0 = system, 1 = code/data). [1 bit]
 *	 type: Type (0 = data, 1 = code). [1 bit]
 *	 dc: Segment expansion direction / conforming bit. [1 bit]
 *	   Data: (0 = up, 1 = down).
 *	   Code: (0 = ring only, 1 = equal or lower).
 *	 rw: Permission bit [1 bit].
 *	   Data: (0 = read, 1 = read/write).
 *	   Code: (0 = execute, 1: execute/write).
 * base_low (39-16): Base memory address, low 2 bytes. [24 bit]
 * limit_high (15-0): Segment size. [16 bit]
 *
 * ------------------------------------------------------------------
 * -bbbbbbbbgg00llllaaaaaaa0bbbbbbbbbbbbbbbbbbbbbbbbllllllllllllllll-    
 * ------------------------------------------------------------------
 */
struct GdtDescriptor {
  unsigned short limit;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
}__attribute__((packed));

extern void lgdt_load(struct Gdt gdt);

// Initialise GDT.
void gdt_init();

// Load descriptor to GDT.
void gtd_descriptor_load(
  unsigned int idx,
  unsigned long base,
  unsigned long limit,
  unsigned char access,
  unsigned char granularity
);

