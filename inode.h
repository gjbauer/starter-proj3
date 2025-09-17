#ifndef INODE_H
#define INODE_H

#include "disk.h"
#include "config.h"

// Inode structure (file metadata)
typedef struct Inode {
    uint64_t inode_number;           // Unique inode identifier
    FileType type;                   // File type
    uint64_t size;                   // File size in bytes
    uint64_t block_count;            // Number of blocks used
    uint64_t direct_blocks[12];      // Direct block pointers
    uint64_t indirect_block;         // Single indirect block pointer
    uint64_t double_indirect_block;  // Double indirect block pointer
    uint64_t creation_time;          // Creation timestamp
    uint64_t modification_time;      // Last modification timestamp
    uint64_t access_time;            // Last access timestamp
    uint64_t reference_count;        // Hard link count
    FilePermissions permissions;     // File permissions
    uint32_t owner_id;               // Owner user ID
    uint32_t group_id;               // Owner group ID
} Inode;

// Inode operations
int inode_read(DiskInterface* disk, uint64_t inode_number, Inode* inode);
int inode_write(DiskInterface* disk, const Inode* inode);
uint64_t inode_allocate(DiskInterface* disk, FileType type);
int inode_free(DiskInterface* disk, uint64_t inode_number);
int inode_get_block(DiskInterface* disk, Inode* inode, uint64_t block_index, uint64_t* physical_block);
int inode_set_block(DiskInterface* disk, Inode* inode, uint64_t block_index, uint64_t physical_block);

// Block allocation
uint64_t block_allocate(DiskInterface* disk);
int block_free(DiskInterface* disk, uint64_t block_num);
int block_read_data(DiskInterface* disk, uint64_t block_num, void* buffer, size_t offset, size_t length);
int block_write_data(DiskInterface* disk, uint64_t block_num, const void* buffer, size_t offset, size_t length);

#endif

