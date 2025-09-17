#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "disk.h"

// File operations
int file_create(DiskInterface* disk, uint64_t parent_inode, const char* name, uint64_t* new_inode);
int file_open(DiskInterface* disk, uint64_t inode_number, int mode);
int file_read(DiskInterface* disk, uint64_t inode_number, void* buffer, size_t size, size_t offset);
int file_write(DiskInterface* disk, uint64_t inode_number, const void* buffer, size_t size, size_t offset);
int file_truncate(DiskInterface* disk, uint64_t inode_number, size_t new_size);
int file_delete(DiskInterface* disk, uint64_t inode_number);

// Path resolution
int path_resolve(DiskInterface* disk, const char* path, uint64_t* inode_number);
int path_create(DiskInterface* disk, const char* path, FileType type, uint64_t* inode_number);

// ==================== FILESYSTEM HIGH-LEVEL API ====================

typedef struct Filesystem {
    DiskInterface* disk;
    Superblock superblock;
    uint64_t current_directory;
} Filesystem;

// Filesystem management
Filesystem* fs_mount(const char* disk_image);
int fs_unmount(Filesystem* fs);
int fs_format(const char* disk_image, const char* volume_name, uint64_t size);

// File operations (high level)
int fs_create_file(Filesystem* fs, const char* path);
int fs_create_directory(Filesystem* fs, const char* path);
int fs_read_file(Filesystem* fs, const char* path, void* buffer, size_t size, size_t offset);
int fs_write_file(Filesystem* fs, const char* path, const void* buffer, size_t size, size_t offset);
int fs_delete(Filesystem* fs, const char* path);
int fs_list_directory(Filesystem* fs, const char* path, DirEntry** entries, int* count);
int fs_get_attributes(Filesystem* fs, const char* path, Inode* inode);
int fs_set_attributes(Filesystem* fs, const char* path, const Inode* inode);

// ==================== UTILITY FUNCTIONS ====================

// Memory management
void* aligned_alloc(size_t alignment, size_t size);
void aligned_free(void* ptr);

// Debug and validation
void fs_check_consistency(Filesystem* fs);
void fs_dump_metadata(Filesystem* fs);
void fs_show_block_allocation(Filesystem* fs);

// Time utilities
uint64_t get_current_timestamp();
void timestamp_to_string(uint64_t timestamp, char* buffer, size_t size);

// Error codes
typedef enum {
    FS_SUCCESS = 0,
    FS_ERROR_NOT_FOUND,
    FS_ERROR_IO,
    FS_ERROR_NO_SPACE,
    FS_ERROR_EXISTS,
    FS_ERROR_INVALID,
    FS_ERROR_PERMISSION,
    FS_ERROR_NOT_DIRECTORY,
    FS_ERROR_NOT_FILE,
    FS_ERROR_BUSY,
    FS_ERROR_CORRUPT
} FSError;

const char* fs_error_string(FSError error);

// ==================== MAIN IMPLEMENTATION OUTLINE ====================

/*int main() {
    // Example usage outline
    Filesystem* fs = fs_mount("myfs.img");
    if (!fs) {
        printf("Mount failed or formatting required\n");
        fs_format("myfs.img", "MyVolume", 1024 * 1024 * 100); // 100MB
        fs = fs_mount("myfs.img");
    }
    
    // Create some files and directories
    fs_create_directory(fs, "/home");
    fs_create_directory(fs, "/home/user");
    fs_create_file(fs, "/home/user/test.txt");
    
    // Write to file
    const char* data = "Hello, B-tree Filesystem!";
    fs_write_file(fs, "/home/user/test.txt", data, strlen(data), 0);
    
    // List directory
    DirEntry* entries;
    int count;
    fs_list_directory(fs, "/home/user", &entries, &count);
    
    // Cleanup
    free(entries);
    fs_unmount(fs);
    
    return 0;
}*/
