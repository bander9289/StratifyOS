/* Copyright 2011-2017 Tyler Gilbert;
 * This file is part of Stratify OS.
 *
 * Stratify OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stratify OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */
#ifndef _SYS_TERMIOS_H_
#define _SYS_TERMIOS_H_


#define _XCGETA (('x'<<8)|1)
#define _XCSETA (('x'<<8)|2)
#define _XCSETAW (('x'<<8)|3)
#define _XCSETAF (('x'<<8)|4)
#define _TCSBRK (('T'<<8)|5)
#define _TCFLSH (('T'<<8)|7)
#define _TCXONC (('T'<<8)|6)

#define TCOOFF	0
#define TCOON	1
#define TCIOFF	2
#define TCION	3

#define TCIFLUSH	0
#define TCOFLUSH	1
#define TCIOFLUSH	2

#define NCCS 13

#define TCSAFLUSH	_XCSETAF
#define TCSANOW	_XCSETA
#define TCSADRAIN	_XCSETAW
#define TCSADFLUSH	_XCSETAF

#define IGNBRK	000001
#define BRKINT	000002
#define IGNPAR	000004
#define INPCK	000020
#define ISTRIP	000040
#define INLCR	000100
#define IGNCR	000200
#define ICRNL	000400
#define IXON	002000
#define IXOFF	010000

#define OPOST	000001
#define OCRNL	000004
#define ONLCR	000010
#define ONOCR	000020
#define TAB3	014000

#define CLOCAL	004000
#define CREAD	000200
#define CSIZE	000060
#define CS5	0
#define CS6	020
#define CS7	040
#define CS8	060
#define CSTOPB	000100
#define HUPCL	002000
#define PARENB	000400
#define PARODD	001000

#define ECHO	0000010
#define ECHOE	0000020
#define ECHOK	0000040
#define ECHONL	0000100
#define ICANON	0000002
#define IEXTEN	0000400	/* anybody know *what* this does?! */
#define ISIG	0000001
#define NOFLSH	0000200
#define TOSTOP	0001000

#define VEOF	4	/* also VMIN -- thanks, AT&T */
#define VEOL	5	/* also VTIME -- thanks again */
#define VERASE	2
#define VINTR	0
#define VKILL	3
#define VMIN	4	/* also VEOF */
#define VQUIT	1
#define VSUSP	10
#define VTIME	5	/* also VEOL */
#define VSTART	11
#define VSTOP	12

#define B0	000000
#define B50	000001
#define B75	000002
#define B110	000003
#define B134	000004
#define B150	000005
#define B200	000006
#define B300	000007
#define B600	000010
#define B1200	000011
#define B1800	000012
#define B2400	000013
#define B4800	000014
#define B9600	000015
#define B19200	000016
#define B38400	000017
#define B57600	000020
#define B115200	000021
#define B230400	000022
#define B460800	000023
#define B921600 000024

#define IXOFF (1<<0)
#define IXON (1<<1)
#define IXANY (1<<2)

typedef unsigned char cc_t;
typedef unsigned short tcflag_t;
typedef char speed_t;

struct termios {
	tcflag_t	c_iflag;
	tcflag_t	c_oflag;
	tcflag_t	c_cflag;
	tcflag_t	c_lflag;
	char		c_line;
	cc_t		c_cc[NCCS];
	speed_t		c_ispeed;
	speed_t		c_ospeed;
};

# ifndef _NO_MACROS
#define cfgetospeed(tp)	((tp)->c_ospeed)
#define cfgetispeed(tp)	((tp)->c_ispeed)
#define cfsetospeed(tp,s)	(((tp)->c_ospeed = (s)), 0)
#define cfsetispeed(tp,s)	(((tp)->c_ispeed = (s)), 0)
#define tcdrain(fd)		ioctl (fd, _TCSBRK, 1)
# endif	/* _NO_MACROS */


int tcgetattr(int, struct termios*);
int tcsetattr(int, int, const struct termios*);



#endif /* _SYS_TERMIOS_H_ */
