#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <assert.h>
#include <string.h>

#include "disk.h"
#include "config.h"

// Disk operations
DiskInterface* disk_open(const char* filename)
{
	DiskInterface *disk = (DiskInterface*)malloc(sizeof(DiskInterface));
	
	if (stat(filename, &disk->fs_info) != 0) {
		fprintf(stderr, "Failed to stat filesystem!!");
		return NULL;
	}
	
	disk->disk_file = open(filename, O_RDWR, 0644);
	assert(disk->disk_file != -1);
	
	disk->disk_base = mmap(0, disk->fs_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, disk->disk_file, 0);
	assert(disk->disk_base != MAP_FAILED);
	
	return disk;
}

void disk_close(DiskInterface* disk)
{
	munmap(disk->disk_base, disk->fs_info.st_size);
	close(disk->disk_file);
	free(disk);
}

int disk_read_block(DiskInterface* disk, uint64_t block_num, void* buffer)
{
	int rv = -1;
	void *block = disk->disk_base + BLOCK_SIZE * block_num;
	
	if (memcpy(buffer, block, BLOCK_SIZE)) {
		rv = 0;
	}
	
	return rv;
}

int disk_write_block(DiskInterface* disk, uint64_t block_num, const void* buffer)
{
	int rv = -1;
	void *block = disk->disk_base + BLOCK_SIZE * block_num;
	
	if (memcpy(block, buffer, BLOCK_SIZE)) {
		rv = 0;
	}
	
	return rv;
}

int disk_format(DiskInterface* disk, const char* volume_name);
