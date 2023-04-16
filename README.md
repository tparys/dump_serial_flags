# Overview

The dump_serial_flags application is a simple console application useful for
exploring which serial port flags are used for various applications, without
having to look at the source code. For example, this is useful for developing
one's own applications using serial ports, or determining how a port should be
properly set up for a given feature, if another application already uses it
(such as minicom). This can also be useful for instrumenting closed source
applications, where the source is not known.

# Usage Example

For example, let's take a look at how minicom sets up a simple serial port:

```
 ~ $ minicom -D /dev/ttyUSB0 -b 115200
```

And run this in another shell:

```
~ $ dump_serial_flags /dev/ttyUSB0
Active serial flags for: /dev/ttyUSB0:

c_iflag: 0x00000500
 - 0x00000100 - ICRNL
 - 0x00000400 - IXON

c_oflag: 0x00000005
 - 0x00000001 - OPOST
 - 0x00000004 - ONLCR
 - 0x00000000 - NL0
 - 0x00000000 - CR0
 - 0x00000000 - TAB0
 - 0x00000000 - BS0
 - 0x00000000 - FF0
 - 0x00000000 - VT0

c_cflag: 0x00000CBD
 - 0x0000000D - B9600
 - 0x00000030 - CS8
 - 0x00000080 - CREAD
 - 0x00000400 - HUPCL
 - 0x00000800 - CLOCAL

c_lflag: 0x00008A3B
 - 0x00000001 - ISIG
 - 0x00000002 - ICANON
 - 0x00000008 - ECHO
 - 0x00000010 - ECHOE
 - 0x00000020 - ECHOK
 - 0x00000200 - ECHOCTL
 - 0x00000800 - ECHOKE
 - 0x00008000 - IEXTEN
```

Such settings can then be cross referenced against "man 3 termios" to determine
what each flag does.
