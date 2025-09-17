
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
HDRS := $(wildcard *.h)

CFLAGS := -g `pkg-config fuse --cflags`
LDLIBS := `pkg-config fuse --libs`

nbtrfs: $(OBJS)
	clang $(CLFAGS) -o $@ $^ $(LDLIBS)

%.o: %.c $(HDRS)
	clang $(CFLAGS) -c -o $@ $<

clean: unmount
	rm -f nbtrfs *.o test.log data.nbtrfs
	rmdir mnt || true

mount: nufs
	mkdir -p mnt || true
	./nbtrfs -s -f mnt data.nbtrfs

unmount:
	fusermount -u mnt || true

test: nufs
	perl test.pl

gdb: nufs
	mkdir -p mnt || true
	lldb --args ./nbtrfs -s -f mnt data.nbtrfs

.PHONY: clean mount unmount gdb

