#ifndef CONFIG_H
#define CONFIG_H

// ==================== CONSTANTS AND CONFIGURATION ====================
#define BLOCK_SIZE 4096          // Size of each disk block in bytes
#define MAX_KEYS 255             // Maximum keys per node (adjust based on key size)
#define MIN_KEYS (MAX_KEYS / 2)  // Minimum keys per node
#define MAX_FILENAME_LENGTH 256
#define MAX_PATH_LENGTH 1024

// File types
typedef enum {
    FILE_TYPE_REGULAR,
    FILE_TYPE_DIRECTORY,
    FILE_TYPE_SYMLINK
} FileType;

// File permissions
typedef struct {
    uint16_t owner_read : 1;
    uint16_t owner_write : 1;
    uint16_t owner_execute : 1;
    uint16_t group_read : 1;
    uint16_t group_write : 1;
    uint16_t group_execute : 1;
    uint16_t other_read : 1;
    uint16_t other_write : 1;
    uint16_t other_execute : 1;
} FilePermissions;

#endif

