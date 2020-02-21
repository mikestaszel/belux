#include <stdint.h>
#include <string.h>
#include <drivers/initrd.h>

initrd_header_t* initrd_header;
initrd_file_header_t* file_headers;
fs_node_t* initrd_root;
fs_node_t* initrd_dev;
fs_node_t* root_nodes;
int nroot_nodes;

struct dirent dirent;

static uint32_t initrd_read(fs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer) {
	initrd_file_header_t header = file_headers[node->inode];
	if (offset > header.length) {
		return 0;
	}
	if (offset+size > header.length) {
		size = header.length-offset;
	}
	memcpy(buffer, (uint8_t*) (header.offset+offset), size);
	return size;
}
