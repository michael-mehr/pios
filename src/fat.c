
// fat.c

#include "fat.h"
#include "sd.h"
#include "rprintf.h"
#include "gpio.h"
#include "serial.h"
// #include <string.h>

struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector; 

int strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int fatInit() { // "Initializes the FAT filesystem driver by reading the superblock (aka boot sector) and FAT into memory."
  bs = (struct boot_sector*)bootSector; // Point boot_sector struct to the boot sector so we can read field
  sd_init(); // Initialize the SD card
  sd_readblock(0, (char*)bootSector, 1); // Read sector 0 from disk drive into bootSector array

  // Print out some of the elements of the BIOS information block using rprintf...
  putc('\n'); // init putc
  esp_printf(putc, "Number of bites per sector: %d\n", bs->bytes_per_sector);
  esp_printf(putc, "Number of sectors per cluster: %d\n", bs->num_sectors_per_cluster);
  esp_printf(putc, "Number of reserved clusters: %d\n", bs->num_reserved_sectors);
  esp_printf(putc, "Number of FAT tables: %d\n", bs->num_fat_tables);

  // TODO: Validate the boot signature = 0xaa55
  if (bs->boot_signature == 0xaa55) {
    esp_printf(putc, "Boot Signature Validated\n");
  } else {
    esp_printf(putc, "Boot Signature Invalid. Expected 0xaa55, got %x\n", bs->boot_signature);
  }
  
  // TODO: Validate fs_type = "FAT12" using strcmp
  if (strcmp(bs->fs_type, "FAT12") == 0) {
    esp_printf(putc, "File System Type Validated\n");
  } else {
    esp_printf(putc, "File System Type Invalid. Expected FAT12, got %c\n", bs->fs_type);
  }

  // TODO: Read FAT table from the SD card into array fat_table
  sd_readblock(bs->num_reserved_sectors, fat_table, bs->num_sectors_per_fat);
  
  // TODO: Compute root_sector as:
  // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
  root_sector = bs->num_fat_tables + bs->num_sectors_per_fat + bs->num_reserved_sectors + bs->num_hidden_sectors;
  esp_printf(putc, "Root Sector: %d\n", root_sector);
  return 1;
}

struct file *fatOpen(char filename) { // "Opens a file in a FAT filesystem on disk."
  
}

// fatRead(char *buf, int n, struct rde *r) { // "Reads data from a file into a buffer."

// }