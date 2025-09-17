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
