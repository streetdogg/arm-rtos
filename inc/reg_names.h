
#ifndef __REG_NAMES__
#define __REG_NAMES__

#define PORTF_DATA (*((volatile unsigned long *)0x400253FC))
#define PORTF_DIR  (*((volatile unsigned long *)0x40025400))
#define PORTF_PUR  (*((volatile unsigned long *)0x40025510))
#define PORTF_DEN  (*((volatile unsigned long *)0x4002551C))
#define RCGC2      (*((volatile unsigned long *)0x400FE108))

#endif
