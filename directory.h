#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "config.h"
#include "disk.h"

// Directory entry structure
typedef struct DirEntry {
    uint64_t inode_number;           // Inode number of the entry
    char name[MAX_FILENAME_LENGTH];  // Name of the entry
    uint8_t name_length;             // Length of the name
    uint8_t entry_type;              // Type of entry (file, dir, etc.)
} DirEntry;

// Directory block structure
typedef struct DirectoryBlock {
    uint16_t entry_count;            // Number of entries in this block
    DirEntry entries[0];             // Flexible array of directory entries
} DirectoryBlock;

// Directory operations
int directory_create(DiskInterface* disk, uint64_t parent_inode, const char* name, uint64_t* new_inode);
int directory_lookup(DiskInterface* disk, uint64_t dir_inode, const char* name, uint64_t* found_inode);
int directory_add_entry(DiskInterface* disk, uint64_t dir_inode, const char* name, uint64_t target_inode, FileType type);
int directory_remove_entry(DiskInterface* disk, uint64_t dir_inode, const char* name);
int directory_list(DiskInterface* disk, uint64_t dir_inode, DirEntry** entries, int* count);

#endif

