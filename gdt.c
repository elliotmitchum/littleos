#include "gdt.h"

// Global descriptor table.
static struct Gdt gdt;

// Descriptors.
static struct GdtDescriptor descriptors[3];

/**
 * gdt_descriptor_load:
 * 
 * Load descriptors into GDT.
 */
void gdt_descriptor_load(
  unsigned int idx,
  unsigned long base,
  unsigned long limit,
  unsigned char access,
  unsigned char granularity
){
  // Base.
  descriptors[idx].base_low = (base & 0xFFFF);
  descriptors[idx].base_middle = (base >> 16) & 0xFF;
  descriptors[idx].base_high = (base >> 24) & 0xFF;

  // Limit.
  // Limit hight bit is present in granularity section.
  descriptors[idx].limit = (limit & 0xFFFF);
  descriptors[idx].granularity = ((limit >> 16) & 0xF);

  // Granularity & access.
  descriptors[idx].granularity |= (granularity << 6 & 0xF0);
  descriptors[idx].access = access << 1;
}

/**
 * gdt_init:
 *
 * Initialise GDT.
 */
void gdt_init() {
  // Create 2 byte GDT table.
  gdt.base = (int) &descriptors;
  gdt.limit = (short) -1U;

  // Load null descriptor.
  gdt_descriptor_load(0, 0, 0, 0, 0);

  // Load code descriptor.
  gdt_descriptor_load(1, 0, (long) -1U, 0b10011010, 0b11001111);

  // Load data descriptor.
  gdt_descriptor_load(2, 0, (long) -1U, 0b01001001, 0b00000010);

  // Install new GDT.
  lgdt_load(gdt);
}

