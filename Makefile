CC=gcc
CFLAGS=-c
LDFLAGS=-lz

libsnbt.a: debug.o utils.o read.o write.o
	ar rvs $@ $^

install: libsnbt.a
	install -m 644 $< /usr/lib/
	install -m 644 nbt.h /usr/include/

read.o: read.c nbt.h
	$(CC) $(CFLAGS) $< -o $@

write.o: write.c nbt.h
	$(CC) $(CFLAGS) $< -o $@

nbtprint.o: nbtprint.c nbt.h
	$(CC) $(CFLAGS) $< -o $@

utils.o: utils.c nbt.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
