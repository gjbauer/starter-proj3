#ifndef DISK_H
#define DISK_H
// ==================== DISK INTERFACE ====================

typedef struct DiskInterface {
    FILE* disk_file;                 // File handle for the disk image
    uint64_t total_blocks;           // Total blocks available
    bool is_mounted;                 // Whether filesystem is mounted
} DiskInterface;

// Disk operations
DiskInterface* disk_open(const char* filename, uint64_t size);
void disk_close(DiskInterface* disk);
int disk_read_block(DiskInterface* disk, uint64_t block_num, void* buffer);
int disk_write_block(DiskInterface* disk, uint64_t block_num, const void* buffer);
int disk_format(DiskInterface* disk, const char* volume_name);

#endif

