
// fat.c

#include "fat.h"
#include "sd.h"
#include "rprintf.h"
#include "gpio.h"
#include "serial.h"

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

// Initializes the FAT filesystem driver by reading the superblock (aka boot sector) and FAT into memory
int fatInit() { 
  bs = (struct boot_sector*)bootSector; // Point boot_sector struct to the boot sector so we can read field
  sd_init(); // Initialize the SD card
  sd_readblock(0, (char*)bootSector, 1); // Read sector 0 from disk drive into bootSector array

  // Print out some of the elements of the BIOS information block using rprintf...
  putc('\n'); // init putc
  esp_printf(putc, "Number of bites per sector: %d\n", bs->bytes_per_sector);
  esp_printf(putc, "Number of sectors per cluster: %d\n", bs->num_sectors_per_cluster);
  esp_printf(putc, "Number of reserved clusters: %d\n", bs->num_reserved_sectors);
  esp_printf(putc, "Number of FAT tables: %d\n", bs->num_fat_tables);
  esp_printf(putc, "Number of root directory entries: %d\n", bs->num_root_dir_entries);

  // Validate the boot signature = 0xaa55
  if (bs->boot_signature == 0xaa55) {
    esp_printf(putc, "Boot Signature Validated\n");
  } else {
    esp_printf(putc, "Boot Signature Invalid. Expected 0xaa55, got %x\n", bs->boot_signature);
  }
  
  // Validate fs_type = "FAT16" using strcmp
  if (strcmp("FAT16", bs->fs_type) == 0) {
    esp_printf(putc, "File System Type Validated\n");
  } else {
    esp_printf(putc, "File System Type Invalid. Expected FAT16, got %s\n", bs->fs_type);
  }

  // Read FAT table from the SD card into array fat_table
  sd_readblock(bs->num_reserved_sectors, fat_table, bs->num_sectors_per_fat);
  
  // Compute root_sector as:
  // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
  root_sector = bs->num_fat_tables + bs->num_sectors_per_fat + bs->num_reserved_sectors + bs->num_hidden_sectors;
  esp_printf(putc, "Root Sector: %d\n", root_sector);
  return 1;
}

// Opens a file in a FAT filesystem on disk
struct file *fatOpen(char *file_name, char *file_ext) {
  struct root_directory_entry *rde;
  struct file *file = NULL;
  char root_dir[bs->num_root_dir_entries * sizeof(struct root_directory_entry)];

  rde = (struct root_directory_entry*)root_dir;

  // Read the root directory sector
  sd_readblock(root_sector, root_dir, 1);

  // Search for the file in the root directory
    // loop through block root_dir
    // check for match 
    // parse filename for name and extension with buffer array
    // strcmp
  esp_printf(putc, "Searching for file %s.%s ...\n", file_name, file_ext);
  for (int i = 0; i < bs->num_root_dir_entries; i++) {
    esp_printf(putc, "File %d: %s.%s\n", i, rde->file_name, rde->file_extension);
    if (strcmp(rde->file_name, file_name) == 0) {
      file = (struct file*)rde;
      break;
    }
    rde++;
  }

  return file;
}

// Reads data from a file into a buffer
// fatRead(char *buf, int n, struct rde *r) { 

// }