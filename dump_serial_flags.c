/*
 * Copyright (c) 2023 Tim Parys
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: 
 
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software. 
 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CHECK_BIT(x, y) if ((x) & (y)) printf(" - 0x%08X - %s\n", (y), #y)
#define CHECK_BITS(x, y, z) if (((x) & (y)) == (z)) printf(" - 0x%08X - %s\n", (z), #z)

int main(int argc, char **argv)
{
    // Check args
    if (argc < 2)
    {
	fprintf(stderr, "Usage: dump_serial_flags /dev/ttyX\n");
	exit(1);
    }

    // Open device
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
	perror("Cannot open serial device");
	exit(1);
    }

    // Query current serial parameters
    struct termios attr = {};
    if (tcgetattr(fd, &attr))
    {
	perror("Cannot query serial settings");
	exit(1);
    }

    printf("Active serial flags for: %s:\n", argv[1]);

    // Dump input modes
    printf("\nc_iflag: 0x%08X\n", attr.c_iflag);
    CHECK_BIT(attr.c_iflag, IGNBRK);
    CHECK_BIT(attr.c_iflag, BRKINT);
    CHECK_BIT(attr.c_iflag, IGNPAR);
    CHECK_BIT(attr.c_iflag, PARMRK);
    CHECK_BIT(attr.c_iflag, INPCK);
    CHECK_BIT(attr.c_iflag, ISTRIP);
    CHECK_BIT(attr.c_iflag, INLCR);
    CHECK_BIT(attr.c_iflag, IGNCR);
    CHECK_BIT(attr.c_iflag, ICRNL);
    CHECK_BIT(attr.c_iflag, IUCLC);
    CHECK_BIT(attr.c_iflag, IXON);
    CHECK_BIT(attr.c_iflag, IXANY);
    CHECK_BIT(attr.c_iflag, IXANY);
    CHECK_BIT(attr.c_iflag, IMAXBEL);
    CHECK_BIT(attr.c_iflag, IUTF8);

    // Dump output modes
    printf("\nc_oflag: 0x%08X\n", attr.c_oflag);
    CHECK_BIT(attr.c_oflag, OPOST);
    CHECK_BIT(attr.c_oflag, OLCUC);
    CHECK_BIT(attr.c_oflag, ONLCR);
    CHECK_BIT(attr.c_oflag, OCRNL);
    CHECK_BIT(attr.c_oflag, INPCK);
    CHECK_BIT(attr.c_oflag, ONOCR);
    CHECK_BIT(attr.c_oflag, ONLRET);
    CHECK_BIT(attr.c_oflag, OFILL);
    CHECK_BIT(attr.c_oflag, OFDEL);
    #if defined __USE_MISC || defined __USE_XOPEN
    CHECK_BITS(attr.c_oflag, NLDLY, NL0);
    CHECK_BITS(attr.c_oflag, NLDLY, NL1);
    CHECK_BITS(attr.c_oflag, CRDLY, CR0);
    CHECK_BITS(attr.c_oflag, CRDLY, CR1);
    CHECK_BITS(attr.c_oflag, CRDLY, CR2);
    CHECK_BITS(attr.c_oflag, CRDLY, CR3);
    CHECK_BITS(attr.c_oflag, TABDLY, TAB0);
    CHECK_BITS(attr.c_oflag, TABDLY, TAB1);
    CHECK_BITS(attr.c_oflag, TABDLY, TAB2);
    CHECK_BITS(attr.c_oflag, TABDLY, TAB3);
    CHECK_BITS(attr.c_oflag, BSDLY, BS0);
    CHECK_BITS(attr.c_oflag, BSDLY, BS1);
    CHECK_BITS(attr.c_oflag, FFDLY, FF0);
    CHECK_BITS(attr.c_oflag, FFDLY, FF1);
    #endif
    CHECK_BITS(attr.c_oflag, VTDLY, VT0);
    CHECK_BITS(attr.c_oflag, VTDLY, VT1);
    #ifdef __USE_MISC
    CHECK_BIT(attr.c_oflag, XTABS);
    #endif

    // Dump control modes
    printf("\nc_cflag: 0x%08X\n", attr.c_cflag);
    CHECK_BITS(attr.c_cflag, CBAUD, B0);
    CHECK_BITS(attr.c_cflag, CBAUD, B50);
    CHECK_BITS(attr.c_cflag, CBAUD, B75);
    CHECK_BITS(attr.c_cflag, CBAUD, B110);
    CHECK_BITS(attr.c_cflag, CBAUD, B134);
    CHECK_BITS(attr.c_cflag, CBAUD, B150);
    CHECK_BITS(attr.c_cflag, CBAUD, B200);
    CHECK_BITS(attr.c_cflag, CBAUD, B300);
    CHECK_BITS(attr.c_cflag, CBAUD, B600);
    CHECK_BITS(attr.c_cflag, CBAUD, B1200);
    CHECK_BITS(attr.c_cflag, CBAUD, B1800);
    CHECK_BITS(attr.c_cflag, CBAUD, B2400);
    CHECK_BITS(attr.c_cflag, CBAUD, B4800);
    CHECK_BITS(attr.c_cflag, CBAUD, B9600);
    CHECK_BITS(attr.c_cflag, CBAUD, B19200);
    CHECK_BITS(attr.c_cflag, CBAUD, B38400);
    CHECK_BITS(attr.c_cflag, CBAUD, B57600);
    CHECK_BITS(attr.c_cflag, CBAUD, B115200);
    CHECK_BITS(attr.c_cflag, CBAUD, B230400);
    CHECK_BITS(attr.c_cflag, CBAUD, B460800);
    CHECK_BITS(attr.c_cflag, CBAUD, B500000);
    CHECK_BITS(attr.c_cflag, CBAUD, B576000);
    CHECK_BITS(attr.c_cflag, CBAUD, B921600);
    CHECK_BITS(attr.c_cflag, CBAUD, B1000000);
    CHECK_BITS(attr.c_cflag, CBAUD, B1152000);
    CHECK_BITS(attr.c_cflag, CBAUD, B1500000);
    CHECK_BITS(attr.c_cflag, CBAUD, B2000000);
    CHECK_BITS(attr.c_cflag, CBAUD, B2500000);
    CHECK_BITS(attr.c_cflag, CBAUD, B3000000);
    CHECK_BITS(attr.c_cflag, CBAUD, B3500000);
    CHECK_BITS(attr.c_cflag, CBAUD, B4000000);
    CHECK_BITS(attr.c_cflag, CSIZE, CS6);
    CHECK_BITS(attr.c_cflag, CSIZE, CS7);
    CHECK_BITS(attr.c_cflag, CSIZE, CS8);
    CHECK_BIT(attr.c_cflag, CSTOPB);
    CHECK_BIT(attr.c_cflag, CREAD);
    CHECK_BIT(attr.c_cflag, PARENB);
    CHECK_BIT(attr.c_cflag, PARODD);
    CHECK_BIT(attr.c_cflag, HUPCL);
    CHECK_BIT(attr.c_cflag, CLOCAL);

    // Dump local modes
    printf("\nc_lflag: 0x%08X\n", attr.c_lflag);
    CHECK_BIT(attr.c_lflag, ISIG);
    CHECK_BIT(attr.c_lflag, ICANON);
    #if defined __USE_MISC || defined __USE_XOPEN
    CHECK_BIT(attr.c_lflag, XCASE);
    #endif
    CHECK_BIT(attr.c_lflag, ECHO);
    CHECK_BIT(attr.c_lflag, ECHOE);
    CHECK_BIT(attr.c_lflag, ECHOK);
    CHECK_BIT(attr.c_lflag, ECHONL);
    CHECK_BIT(attr.c_lflag, NOFLSH);
    CHECK_BIT(attr.c_lflag, TOSTOP);
    #if defined __USE_MISC
    CHECK_BIT(attr.c_lflag, ECHOCTL);
    CHECK_BIT(attr.c_lflag, ECHOPRT);
    CHECK_BIT(attr.c_lflag, ECHOKE);
    CHECK_BIT(attr.c_lflag, FLUSHO);
    CHECK_BIT(attr.c_lflag, PENDIN);
    #endif
    CHECK_BIT(attr.c_lflag, IEXTEN);
    #if defined __USE_MISC
    CHECK_BIT(attr.c_lflag, EXTPROC);
    #endif

    close(fd);
    return 0;
    
}
