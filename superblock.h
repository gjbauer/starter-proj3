#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include "disk.h"

// File system metadata (superblock)
typedef struct Superblock {
    uint64_t magic_number;           // File system identifier
    uint64_t block_size;             // Size of each block
    uint64_t total_blocks;           // Total blocks in filesystem
    uint64_t free_blocks;            // Number of free blocks
    uint64_t root_inode;             // Root directory inode number
    uint64_t btree_root;             // Root of B-tree index
    uint64_t next_free_block;        // Next free block for allocation
    uint64_t next_free_inode;        // Next available inode number
    char volume_name[32];            // Volume label
    uint64_t creation_time;          // Filesystem creation timestamp
    uint64_t last_mount_time;        // Last mount timestamp
} Superblock;

// Superblock operations
int superblock_read(DiskInterface* disk, Superblock* superblock);
int superblock_write(DiskInterface* disk, const Superblock* superblock);
int superblock_initialize(DiskInterface* disk, const char* volume_name);

#endif

