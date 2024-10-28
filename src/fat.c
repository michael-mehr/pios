
// fat.c

#include "fat.h"
#include "sd.h"
#include "rprintf.h"
#include <string.h>

struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector; // Read sector 0 from disk drive into bootSector array

int fatInit() { // "Initializes the FAT filesystem driver by reading the superblock (aka boot sector) and FAT into memory."
  sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
  bs = (struct bootSector*)bootSector; // Point boot_sector struct to the boot sector so we can read field

  // Print out some of the elements of the BIOS information block using rprintf...

  // TODO: Validate the boot signature = 0xaa55
  // TODO: Validate fs_type = "FAT12" using strcmp
  // TODO: Read FAT table from the SD card into array fat_table
  // TODO: Compute root_sector as:
  // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors

}

fatOpen() { // "Opens a file in a FAT filesystem on disk."

}

fatRead() { // "Reads data from a file into a buffer."

}