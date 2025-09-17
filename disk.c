#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <assert.h>

#include "disk.h"

// Disk operations
DiskInterface* disk_open(const char* filename)
{
	DiskInterface *disk = (DiskInterface*)malloc(sizeof(DiskInterface));
	struct stat fs_info;
	
	if (stat(filename, &fs_info) != 0) {
		fprintf(stderr, "Failed to stat filesystem!!");
	}
	
	disk->disk_file = open(filename, O_RDWR, 0644);
	assert(disk->disk_file != -1);
	
	disk->disk_base = mmap(0, fs_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, disk->disk_file, 0);
	
	return disk;
}

void disk_close(DiskInterface* disk)
{
	munmap(disk->disk_base);
	close(disk->disk_file);
	free(disk);
}

int disk_read_block(DiskInterface* disk, uint64_t block_num, void* buffer);
int disk_write_block(DiskInterface* disk, uint64_t block_num, const void* buffer);
int disk_format(DiskInterface* disk, const char* volume_name);
