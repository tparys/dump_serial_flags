CC=gcc
CFLAGS=-Wall -Os

dump_serial_flags: dump_serial_flags.c
	$(CC) $(CFLAGS) -o dump_serial_flags dump_serial_flags.c

clean:
	rm -f dump_serial_flags
